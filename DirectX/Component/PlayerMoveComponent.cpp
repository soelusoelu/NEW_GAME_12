#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AnchorActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer) :
    Component(owner),
    mRenderer(renderer),
    mSpriteComp(nullptr),
    mAcceleration(Vector2(30.f, 0.f)),
    mAccelerationSpeed(120.f),
    mAccelerationRange(Vector2(-300.f, 300.f)),
    mDeceleration(Vector2::one),
    mDecelerationSpeed(10.f),
    mDestroyRange(Vector2(-3.f, 3.f)),
    mAnchorKey(KeyCode::Q),
    mAnchorLength(400.f) {
}

PlayerMoveComponent::~PlayerMoveComponent() = default;

void PlayerMoveComponent::start() {
    mSpriteComp = mOwner->getComponentManager()->getComponent<SpriteComponent>();
}

void PlayerMoveComponent::update() {
    move();
    deceleration();
    anchor();
    dead();
}

void PlayerMoveComponent::move() {
    auto h = Input::horizontal() * mAccelerationSpeed * Time::deltaTime;
    auto v = Input::vertical() * mAccelerationSpeed * Time::deltaTime;
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        mAcceleration += Vector2(h, -v);
    }

    //Å‘åÅ¬‰Á‘¬“x
    mAcceleration.clamp(
        Vector2(mAccelerationRange.x, mAccelerationRange.x),
        Vector2(mAccelerationRange.y, mAccelerationRange.y)
    );

    //Œ»Ý‚Ì‰Á‘¬“x‚ÅˆÚ“®
    mOwner->getTransform()->translate(mAcceleration * Time::deltaTime);
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
    auto pos = mOwner->getTransform()->getPosition();
    auto sizeDiv2 = mSpriteComp->getScreenTextureSize() / 2.f;

    new AnchorActor(mRenderer, Vector2(pos.x + sizeDiv2.x, pos.y + sizeDiv2.y), Vector2::up, mAnchorLength);
}

void PlayerMoveComponent::dead() {
    if (mDestroyRange.x < mAcceleration.x && mAcceleration.x < mDestroyRange.y &&
        mDestroyRange.x < mAcceleration.y && mAcceleration.y < mDestroyRange.y) {
        Actor::destroy(mOwner);
    }
}
