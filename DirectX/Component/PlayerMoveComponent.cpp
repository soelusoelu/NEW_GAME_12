﻿#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AnchorActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"
#include "../System/Game.h"
#include <iostream>

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer, int updateOrder) :
    Component(owner, updateOrder),
    mAnchor(new AnchorActor(renderer)),
    mRenderer(renderer),
    mSpriteComp(nullptr),
    mAcceleration(Vector2(30.f, 0.f)),
    mAccelerationSpeed(120.f),
    mAccelerationRange(200.f),
    mAnchorAccelerationTimes(5.f),
    mAnchorAccelerationRange(400.f),
    mDecelerationSpeed(30.f),
    mDestroyRange(3.f),
    mRotateCount(0.f),
    mPreviousPos(Vector2::zero),
    mAnchorKey(KeyCode::Q),
    mAnchorJoy(JoyCode::RightButton),
    mLastInput(Vector2::right) {
}

PlayerMoveComponent::~PlayerMoveComponent() {
    Actor::destroy(mAnchor);
}

void PlayerMoveComponent::start() {
    mSpriteComp = mOwner->componentManager()->getComponent<SpriteComponent>();
}

void PlayerMoveComponent::update() {
    move();
    deceleration();
    anchorUpdate();
    anchorInjection();
    clamp();
    dead();
}

Vector2 PlayerMoveComponent::getLastInput() const {
    return mLastInput;
}

bool PlayerMoveComponent::isHitAnchor() const {
    return mAnchor->isHit();
}

const float PlayerMoveComponent::anchorMaxLength() const {
    return mAnchor->maxLength();
}

void PlayerMoveComponent::move() {
    //1フレーム前の座標を記憶
    mPreviousPos = centerPosition();

    auto h = Input::horizontal();
    auto v = Input::vertical();
    //auto h = Input::joyHorizontal();
    //auto v = Input::joyVertical();
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        auto fh = h * mAccelerationSpeed * Time::deltaTime;
        auto fv = v * mAccelerationSpeed * Time::deltaTime;

        auto a = Vector2(fh, -fv);
        mAcceleration += (isHitAnchor()) ? a * mAnchorAccelerationTimes : a;
    }

    //最大最小加速度
    auto range = (isHitAnchor()) ? mAnchorAccelerationRange : mAccelerationRange;
    mAcceleration.clamp(Vector2(-range, -range), Vector2(range, range));

    //現在の加速度で移動
    if (isHitAnchor()) {
        auto rate = (Math::abs(mAcceleration.x) + Math::abs(mAcceleration.y)) / 2.f;
        mRotateCount += Time::deltaTime * rate;
        auto angle = mAnchor->hitAngle() + mRotateCount;
        mOwner->transform()->setPosition(
            mAnchor->hitEnemy()->transform()->getPosition() + Vector2(Math::cos(angle), Math::sin(angle)) * mAnchor->currentLength()
        );

        mAcceleration += moveDirection() * 50.f;
    } else {
        mOwner->transform()->translate(mAcceleration * Time::deltaTime);
    }
}

void PlayerMoveComponent::deceleration() {
    if (isHitAnchor()) {
        return;
    }
    Vector2 d;
    d.x = (mAcceleration.x > 0.f) ? -mDecelerationSpeed : mDecelerationSpeed;
    d.y = (mAcceleration.y > 0.f) ? -mDecelerationSpeed : mDecelerationSpeed;
    mAcceleration += d * Time::deltaTime;
}

void PlayerMoveComponent::anchorInjection() {
    if ((!Input::getKeyDown(mAnchorKey) && !Input::getJoyDown(mAnchorJoy)) || !mAnchor->canShot()) {
        return;
    }
    mAnchor->shot(mLastInput);
    mRotateCount = 0.f;
}

void PlayerMoveComponent::anchorUpdate() {
    //アンカーの位置をプレイヤーの中心に
    mAnchor->transform()->setPosition(centerPosition());

    //アンカーを指す位置
    auto h = Input::joyRhorizontal();
    auto v = Input::joyRvertical();
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        auto dir = Vector2::normalize(Vector2(h, -v));
        mLastInput.set(dir.x, dir.y);
        //mLastInput.set(h, -v);
    }
}

void PlayerMoveComponent::clamp() {
    auto t = mOwner->transform();
    t->setPosition(Vector2::clamp(
        t->getPosition(),
        Vector2::zero,
        Vector2(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT) - Vector2(mSpriteComp->getScreenTextureSize().x, mSpriteComp->getScreenTextureSize().y)
    ));
}

void PlayerMoveComponent::dead() {
    if (Math::abs(mAcceleration.x) < mDestroyRange &&
        Math::abs(mAcceleration.y) < mDestroyRange) {
        //Actor::destroy(mOwner);
    }
}

Vector2 PlayerMoveComponent::centerPosition() const {
    return mOwner->transform()->getCenter();
}

Vector2 PlayerMoveComponent::moveDirection() const {
    return Vector2::normalize(centerPosition() - mPreviousPos);
}
