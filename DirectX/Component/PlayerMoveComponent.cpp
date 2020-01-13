#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AnchorActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer, int updateOrder) :
    Component(owner, updateOrder),
    mAnchor(new AnchorActor(renderer, mOwner->transform())),
    mRenderer(renderer),
    mSpriteComp(nullptr),
    mAcceleration(Vector2(30.f, 0.f)),
    mAccelerationSpeed(120.f),
    mAccelerationRange(100.f),
    mAnchorAccelerationTimes(5.f),
    mAnchorAccelerationRange(300.f),
    mDecelerationSpeed(10.f),
    mDestroyRange(3.f),
    mAnchorKey(KeyCode::Q),
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
    anchorInjection();
    anchorUpdate();
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
    auto h = Input::horizontal();
    auto v = Input::vertical();
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        mLastInput.set(h, -v);
        auto fh = h * mAccelerationSpeed * Time::deltaTime;
        auto fv = v * mAccelerationSpeed * Time::deltaTime;

        auto a = Vector2(fh, -fv);
        if (mAnchor->isHit()) {
            a *= mAnchorAccelerationTimes;
        }
        mAcceleration += a;
    }

    //最大最小加速度
    auto range = (mAnchor->isHit()) ? mAnchorAccelerationRange : mAccelerationRange;
    mAcceleration.clamp(Vector2(-range, -range), Vector2(range, range));

    //現在の加速度で移動
    mOwner->transform()->translate(mAcceleration * Time::deltaTime);
}

void PlayerMoveComponent::deceleration() {
    if (mAnchor->isHit()) {
        return;
    }
    Vector2 d;
    d.x = (mAcceleration.x > 0.f) ? -mDecelerationSpeed : mDecelerationSpeed;
    d.y = (mAcceleration.y > 0.f) ? -mDecelerationSpeed : mDecelerationSpeed;
    mAcceleration += d * Time::deltaTime;
}

void PlayerMoveComponent::anchorInjection() {
    if (!Input::getKeyDown(mAnchorKey) || !mAnchor->canShot()) {
        return;
    }
    mAnchor->shot(mLastInput);
}

void PlayerMoveComponent::anchorUpdate() {
    mAnchor->transform()->setPosition(mOwner->transform()->getPosition() + mOwner->transform()->getPivot());
}

void PlayerMoveComponent::dead() {
    if (Math::abs(mAcceleration.x) < mDestroyRange &&
        Math::abs(mAcceleration.y) < mDestroyRange) {
        //Actor::destroy(mOwner);
    }
}
