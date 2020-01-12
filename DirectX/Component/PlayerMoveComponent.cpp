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
    mAccelerationRange(Vector2(-300.f, 300.f)),
    mAnchorAccelerationRange(Vector2(-500.f, 500.f)),
    mDeceleration(Vector2::one),
    mDecelerationSpeed(10.f),
    mDestroySpeed(3.f),
    mAnchorKey(KeyCode::Q),
    mLastInput(Vector2::right) {
}

PlayerMoveComponent::~PlayerMoveComponent() = default;

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

void PlayerMoveComponent::move() {
    auto h = Input::horizontal();
    auto v = Input::vertical();
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        mLastInput.set(h, -v);
        h *= mAccelerationSpeed * Time::deltaTime;
        v *= mAccelerationSpeed * Time::deltaTime;

        auto a = Vector2(h, -v);
        if (mAnchor->isHit()) {
            a *= 5.f;
        }
        mAcceleration += a;
    }

    //Å‘åÅ¬‰Á‘¬“x
    auto range = (mAnchor->isHit()) ? mAnchorAccelerationRange : mAccelerationRange;
    mAcceleration.clamp(Vector2(range.x, range.x), Vector2(range.y, range.y));

    //Œ»Ý‚Ì‰Á‘¬“x‚ÅˆÚ“®
    mOwner->transform()->translate(mAcceleration * Time::deltaTime);
}

void PlayerMoveComponent::deceleration() {
    if (mAnchor->isHit()) {
        return;
    }
    mDeceleration.x = (mAcceleration.x > 0) ? -mDecelerationSpeed : mDecelerationSpeed;
    mDeceleration.y = (mAcceleration.y > 0) ? -mDecelerationSpeed : mDecelerationSpeed;
    mAcceleration += mDeceleration * Time::deltaTime;
}

void PlayerMoveComponent::anchorInjection() {
    if (!Input::getKeyDown(mAnchorKey)) {
        return;
    }
    mAnchor->initialize(mLastInput);
}

void PlayerMoveComponent::anchorUpdate() {
    mAnchor->transform()->setPosition(mOwner->transform()->getPosition() + mOwner->transform()->getPivot());
}

void PlayerMoveComponent::dead() {
    if (Math::abs(mAcceleration.x) < mDestroySpeed &&
        Math::abs(mAcceleration.y) < mDestroySpeed) {
        Actor::destroy(mOwner);
    }
}
