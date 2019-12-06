﻿#include "Sprite.h"
#include "SpriteManager.h"
#include "Texture.h"
#include "../Device/Renderer.h"
#include "../Shader/Shader.h"
#include "../System/TextureDesc.h"
#include <cassert>

Sprite::Sprite(const char* fileName, float z) :
    mDefaultSize(Vector2::zero),
    mCurrentSize(Vector2::zero),
    mPosition(Vector2::zero, z),
    mRotation(Quaternion::identity),
    mScale(Vector2::one),
    mColor(ColorPalette::white, 1.f),
    mUV(0.f, 0.f, 1.f, 1.f),
    mPivot(mCurrentSize / 2.f),
    mWorld(Matrix4::identity),
    mState(SpriteState::Active),
    mTexture(Renderer::getTexture(fileName)),
    mShader(std::make_shared<Shader>()),
    mFileName(fileName),
    mWorldUpdateFlag(true) {

    auto desc = mTexture->desc();
    mDefaultSize = Vector2(desc.width, desc.height);
    mCurrentSize = mDefaultSize;

    mShader->createVertexShader("Texture.hlsl", "VS");
    mShader->createPixelShader("Texture.hlsl", "PS");
    mTexture->createVertexLayout(mShader->getCompiledShader());

    SpriteManager::add(this);
}

Sprite::~Sprite() = default;

Sprite::Sprite(const Sprite & sprite) :
    mDefaultSize(sprite.mDefaultSize),
    mCurrentSize(sprite.mCurrentSize),
    mPosition(sprite.mPosition),
    mRotation(sprite.mRotation),
    mScale(sprite.mScale),
    mColor(sprite.mColor),
    mUV(sprite.mUV),
    mPivot(sprite.mPivot),
    mWorld(sprite.mWorld),
    mState(SpriteState::Active),
    mTexture(sprite.mTexture),
    mShader(sprite.mShader),
    mFileName(sprite.mFileName),
    mWorldUpdateFlag(true) {
}

void Sprite::update() {
    updateWorld();
}

Sprite* Sprite::draw() const {
    auto s = new Sprite(*this);
    SpriteManager::add(s);
    s->mState = SpriteState::Once;
    return s;
}

void Sprite::setPosition(const Vector2 & pos) {
    mPosition.x = pos.x;
    mPosition.y = pos.y;
    mWorldUpdateFlag = true;
}

void Sprite::setPrimary(float z) {
    mPosition.z = z;
    mWorldUpdateFlag = true;
    mZSortFlag = true;
}

Vector2 Sprite::getPosition() const {
    return Vector2(mPosition.x, mPosition.y);
}

float Sprite::getDepth() const {
    return mPosition.z;
}

void Sprite::translate(const Vector2 & translation) {
    mPosition.x += translation.x;
    mPosition.y += translation.y;
    mWorldUpdateFlag = true;
}

void Sprite::setRotation(float angle) {
    angle *= 0.5f * Math::deg2Rad;
    float sinAngle = Math::sin(angle);

    mRotation.z *= sinAngle;
    mRotation.w = Math::cos(angle);

    mWorldUpdateFlag = true;
}

Quaternion Sprite::getRotation() const {
    return mRotation;
}

void Sprite::rotate(float angle) {
    angle *= 0.5f * Math::deg2Rad;
    float sinAngle = Math::sin(angle);

    Quaternion inc;
    inc.z = sinAngle;
    inc.w = Math::cos(angle);

    mRotation = Quaternion::concatenate(mRotation, inc);

    mWorldUpdateFlag = true;
}

void Sprite::setScale(const Vector2 & scale, bool isCenterShift) {
    bool isBigger = mScale.x < scale.x;

    if (isCenterShift) {
        centerShift(scale);
    }

    mScale = scale;

    //ピボット修正
    mPivot = mCurrentSize / 2.f;
    mPivot.x *= mScale.x;
    mPivot.y *= mScale.y;

    mWorldUpdateFlag = true;
}

void Sprite::setScale(float scale, bool isCenterShift) {
    if (isCenterShift) {
        centerShift(Vector2(scale, scale));
    }

    mScale.x = scale;
    mScale.y = scale;

    //ピボット修正
    mPivot = mCurrentSize / 2.f;
    mPivot.x *= mScale.x;
    mPivot.y *= mScale.y;

    mWorldUpdateFlag = true;
}

Vector2 Sprite::getScale() const {
    return mScale;
}

void Sprite::setColor(const Vector3 & color) {
    mColor.x = color.x;
    mColor.y = color.y;
    mColor.z = color.z;
    mWorldUpdateFlag = true;
}

void Sprite::setColor(float r, float g, float b) {
    mColor.x = r;
    mColor.y = g;
    mColor.z = b;
    mWorldUpdateFlag = true;
}

void Sprite::setAlpha(float alpha) {
    mColor.w = alpha;
    mWorldUpdateFlag = true;
}

Vector4 Sprite::getColor() const {
    return mColor;
}

void Sprite::setUV(float l, float t, float r, float b) {
    assert(0.f <= l || l <= 1.f);
    assert(0.f <= t || t <= 1.f);
    assert(l <= r || r <= 1.f);
    assert(t <= b || b <= 1.f);

    mUV.x = l;
    mUV.y = t;
    mUV.z = r;
    mUV.w = b;

    //サイズ修正
    mCurrentSize.x = mDefaultSize.x * (r - l);
    mCurrentSize.y = mDefaultSize.y * (b - t);

    //ピボット修正
    mPivot = mCurrentSize / 2.f;
    mPivot.x *= mScale.x;
    mPivot.y *= mScale.y;

    mWorldUpdateFlag = true;
}

Vector4 Sprite::getUV() const {
    return mUV;
}

void Sprite::setPivot(const Vector2 & pivot) {
    mPivot = pivot;
    mWorldUpdateFlag = true;
}

Vector2 Sprite::getPivot() const {
    return mPivot;
}

Vector2 Sprite::getTextureSize() const {
    return mDefaultSize;
}

Vector2 Sprite::getScreenTextureSize() const {
    return mCurrentSize * mScale;
}

void Sprite::destroy(Sprite * sprite) {
    sprite->mState = SpriteState::Dead;
}

void Sprite::destroy(std::shared_ptr<Sprite> sprite) {
    sprite->mState = SpriteState::Dead;
}

SpriteState Sprite::getState() const {
    return mState;
}

Matrix4 Sprite::getWorld() const {
    return mWorld;
}

void Sprite::setTexture(const char* fileName) {
    mPivot = mCurrentSize / 2.f;
    mTexture = Renderer::getTexture(fileName);
    mFileName = fileName;

    auto desc = mTexture->desc();
    mDefaultSize = Vector2(desc.width, desc.height);
    mCurrentSize = mDefaultSize;

    mTexture->createVertexLayout(mShader->getCompiledShader());
}

std::shared_ptr<Texture> Sprite::texture() const {
    return mTexture;
}

std::shared_ptr<Shader> Sprite::shader() const {
    return mShader;
}

const char* Sprite::fileName() const {
    return mFileName;
}

bool Sprite::getWorldUpdateFlag() const {
    return mWorldUpdateFlag;
}

void Sprite::onceToDead() {
    if (mState == SpriteState::Once) {
        mState = SpriteState::Dead;
    }
}

void Sprite::updateWorld() {
    //ワールド行列に変更が生じたら
    if (!mWorldUpdateFlag) {
        return;
    }
    mWorldUpdateFlag = false;

    //mWorld = Matrix4::createScale(mCurrentSize.x * mScale.x, mCurrentSize.y * mScale.y, 1.f);
    mWorld = Matrix4::createScale(Vector3(getScreenTextureSize(), 1.f));
    mWorld *= Matrix4::createTranslation(Vector3(-mPivot, 0.f));
    mWorld *= Matrix4::createFromQuaternion(mRotation);
    mWorld *= Matrix4::createTranslation(mPosition + Vector3(mPivot, 0.f));
}

void Sprite::centerShift(const Vector2 & nextScale) {
    auto PreviosSize = getScreenTextureSize();
    auto nextSize = mCurrentSize * nextScale;
    auto shift = (PreviosSize - nextSize) / 2.f;

    translate(shift);
}

bool Sprite::mZSortFlag = false;
