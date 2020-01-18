#include "Sprite.h"
#include "SpriteManager.h"
#include "Texture.h"
#include "../Actor/Transform2D.h"
#include "../Device/Renderer.h"
#include "../Shader/Shader.h"
#include "../System/Buffer.h"
#include "../System/TextureDesc.h"
#include "../System/VertexStreamDesc.h"
#include <cassert>

Sprite::Sprite(std::shared_ptr<Renderer> renderer, const char* fileName, float z, SpriteUsage usage, bool updateMyself) :
    mRenderer(renderer),
    mTransform(std::make_unique<Transform2D>()),
    mTexture(mRenderer->createTexture(fileName)),
    mShader(mRenderer->createShader("Texture.hlsl", "VS", "PS")),
    mDefaultSize(Vector2::zero),
    mCurrentSize(Vector2::zero),
    mColor(ColorPalette::white, 1.f),
    mUV(0.f, 0.f, 1.f, 1.f),
    mState(SpriteState::ACTIVE),
    mUsage(usage),
    mFileName(fileName),
    mUpdateMyself(updateMyself) {

    mTransform->setPrimary(z);

    auto desc = mTexture->desc();
    mDefaultSize = Vector2(desc.width, desc.height);
    mCurrentSize = mDefaultSize;

    mTexture->createInputLayout(mRenderer, mShader->getCompiledShader());

    if (mSpriteManager) {
        mSpriteManager->add(this);
    }
}

Sprite::~Sprite() = default;

Sprite::Sprite(const Sprite & sprite) :
    mTransform(sprite.mTransform),
    mDefaultSize(sprite.mDefaultSize),
    mCurrentSize(sprite.mCurrentSize),
    mTexture(sprite.mTexture),
    mShader(sprite.mShader),
    mColor(sprite.mColor),
    mUV(sprite.mUV),
    mState(SpriteState::ACTIVE),
    mUsage(sprite.mUsage),
    mFileName(sprite.mFileName),
    mUpdateMyself(sprite.mUpdateMyself) {
}

void Sprite::update() {
    if (mUpdateMyself && mState == SpriteState::ACTIVE) {
        mTransform->computeWorldTransform();
    }
}

void Sprite::draw(const Matrix4 & proj) {
    if (mState != SpriteState::ACTIVE) {
        return;
    }

    //バーテックスバッファーをセット
    VertexStreamDesc stream;
    stream.buffer = mTexture->getVertexBuffer();
    stream.offset = 0;
    stream.stride = sizeof(TextureVertex);
    mRenderer->setVertexBuffer(&stream);
    //自身を使用するシェーダーとして登録
    mShader->setVSShader();
    mShader->setPSShader();
    //コンスタントバッファーを使うシェーダーの登録
    mShader->setVSConstantBuffers();
    mShader->setPSConstantBuffers();
    //頂点レイアウトをセット
    mRenderer->setInputLayout(mTexture->getVertexlayout());

    //シェーダーのコンスタントバッファーに各種データを渡す
    D3D11_MAPPED_SUBRESOURCE pData;
    if (SUCCEEDED(mRenderer->deviceContext()->Map(mShader->getConstantBuffer()->buffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
        TextureShaderConstantBuffer cb;
        //ワールド、カメラ、射影行列を渡す
        cb.mWorld = mTransform->getWorldTransform();
        cb.mWorld.transpose();
        cb.mProjection = proj;
        cb.mProjection.transpose();
        cb.mColor = mColor;
        cb.mUV = mUV;
        memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
        mRenderer->deviceContext()->Unmap(mShader->getConstantBuffer()->buffer(), 0);
    }
    //テクスチャーをシェーダーに渡す
    mShader->setPSTextures(mTexture);
    //サンプラーのセット
    auto sample = mTexture->getSampler();
    mRenderer->deviceContext()->PSSetSamplers(0, 1, &sample);
    //プリミティブをレンダリング
    mRenderer->drawIndexed(6);
}

std::shared_ptr<Sprite> Sprite::copy() const {
    auto s = std::make_shared<Sprite>(*this);
    mSpriteManager->add(s);
    return s;
}

std::shared_ptr<Transform2D> Sprite::transform() const {
    return mTransform;
}

void Sprite::setColor(const Vector3 & color) {
    mColor.x = color.x;
    mColor.y = color.y;
    mColor.z = color.z;
}

void Sprite::setColor(float r, float g, float b) {
    mColor.x = r;
    mColor.y = g;
    mColor.z = b;
}

void Sprite::setAlpha(float alpha) {
    mColor.w = alpha;
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

    //バーテックスバッファを作り直す(ボトルネック)
    mTexture->createVertexBuffer(mRenderer, mCurrentSize);

    //mWorldUpdateFlag = true;
}

Vector4 Sprite::getUV() const {
    return mUV;
}

Vector2 Sprite::getTextureSize() const {
    return mDefaultSize;
}

Vector2 Sprite::getCurrentTextureSize() const {
    return mCurrentSize;
}

Vector2 Sprite::getOnScreenTextureSize() const {
    return mCurrentSize.x * mTransform->getScale();
}

void Sprite::destroy(Sprite * sprite) {
    sprite->mState = SpriteState::DEAD;
}

void Sprite::destroy(std::shared_ptr<Sprite> sprite) {
    sprite->mState = SpriteState::DEAD;
}

void Sprite::setActive(bool value) {
    mState = (value) ? SpriteState::ACTIVE : SpriteState::NON_ACTIVE;
}

bool Sprite::getActive() const {
    return mState == SpriteState::ACTIVE;
}

SpriteState Sprite::getState() const {
    return mState;
}

bool Sprite::isUI() const {
    return mUsage == SpriteUsage::UI;
}

void Sprite::setWorld(const Matrix4 & world) {
    mTransform->setWorldTransform(world);
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

void Sprite::setSpriteManager(SpriteManager * manager) {
    mSpriteManager = manager;
}

bool Sprite::ZSortFlag = false;
SpriteManager* Sprite::mSpriteManager = nullptr;
