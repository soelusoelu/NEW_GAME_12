#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AnchorActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer, int updateOrder) :
    Component(owner, updateOrder),
    mRenderer(renderer),
    mSpriteComp(nullptr),
    mAcceleration(Vector2(30.f, 0.f)),
    mAccelerationSpeed(120.f),
    mAccelerationRange(Vector2(-300.f, 300.f)),
    mAnchorAccelerationRange(Vector2(-500.f, 500.f)),
    mDeceleration(Vector2::one),
    mDecelerationSpeed(10.f),
    mDestroySpeed(3.f),
    mIsDecelerated(true),
    mAnchorKey(KeyCode::Q) {
}

PlayerMoveComponent::~PlayerMoveComponent() = default;

void PlayerMoveComponent::start() {
    mSpriteComp = mOwner->componentManager()->getComponent<SpriteComponent>();
}

void PlayerMoveComponent::update() {
    move();
    deceleration();
    anchor();
    dead();
}

int PlayerMoveComponent::getAccelerate() const {
    auto x = Math::abs(mAcceleration.x);
    auto y = Math::abs(mAcceleration.y);
    if (0.f <= x && x < 100.f) {
        return 1;
    } else if (100.f <= x && x < 200.f) {
        return 2;
    } else {
        return 3;
    }
}

void PlayerMoveComponent::setAccelerate(const Vector2 & acceleration) {
    mAcceleration = acceleration;
}

void PlayerMoveComponent::reSetAccelerate() {
    mAcceleration = Vector2::zero;
}

void PlayerMoveComponent::setDecelerate(bool flag) {
    mIsDecelerated = flag;
}

void PlayerMoveComponent::move() {
    auto h = Input::horizontal() * mAccelerationSpeed * Time::deltaTime;
    auto v = Input::vertical() * mAccelerationSpeed * Time::deltaTime;
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        if (!mIsDecelerated) {
            mAcceleration += Vector2(h, -v) * 5.f;
        } else {
            mAcceleration += Vector2(h, -v);
        }
    }

    //Å‘åÅ¬‰Á‘¬“x
    if (!mIsDecelerated) {
        mAcceleration.clamp(
            Vector2(mAnchorAccelerationRange.x, mAnchorAccelerationRange.x),
            Vector2(mAnchorAccelerationRange.y, mAnchorAccelerationRange.y)
        );
    } else {
        mAcceleration.clamp(
            Vector2(mAccelerationRange.x, mAccelerationRange.x),
            Vector2(mAccelerationRange.y, mAccelerationRange.y)
        );
    }

    //Œ»Ý‚Ì‰Á‘¬“x‚ÅˆÚ“®
    mOwner->transform()->translate(mAcceleration * Time::deltaTime);
}

void PlayerMoveComponent::deceleration() {
    mDeceleration.x = (mAcceleration.x > 0) ? -mDecelerationSpeed : mDecelerationSpeed;
    mDeceleration.y = (mAcceleration.y > 0) ? -mDecelerationSpeed : mDecelerationSpeed;
    mAcceleration += mDeceleration * Time::deltaTime;
}

void PlayerMoveComponent::anchor() {
    if (!Input::getKeyDown(mAnchorKey)) {
        return;
    }
    new AnchorActor(mRenderer, mOwner, Vector2::right);
}

void PlayerMoveComponent::dead() {
    if (Math::abs(mAcceleration.x) < mDestroySpeed &&
        Math::abs(mAcceleration.y) < mDestroySpeed) {
        //Actor::destroy(mOwner);
    }
}
