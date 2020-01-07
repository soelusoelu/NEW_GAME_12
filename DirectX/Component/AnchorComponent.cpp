#include "AnchorComponent.h"
#include "Collider.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"

AnchorComponent::AnchorComponent(Actor* owner,  Actor* player, const Vector2& anchorDirection) :
    Component(owner),
    mPlayer(player),
    mSpriteComp(nullptr),
    mCollide(nullptr),
    mCurrentAnchorLength(0.f)
{
    mOwner->getTransform()->setRotation(Math::toDegrees(Math::atan2(-anchorDirection.x, -anchorDirection.y)));
    mOwner->getTransform()->setPosition(mPlayer->getTransform()->getPosition() + mPlayer->getTransform()->getPivot());
}

AnchorComponent::~AnchorComponent() = default;

void AnchorComponent::start() {
    mSpriteComp = mOwner->getComponentManager()->getComponent<SpriteComponent>();
    mCollide = mOwner->getComponentManager()->getComponent<Collider>();
}

void AnchorComponent::update() {
    mCurrentAnchorLength += 600.f * Time::deltaTime;
    mOwner->getTransform()->setScale(Vector2(1.f, mCurrentAnchorLength), mSpriteComp->getTextureSize());
    mOwner->getTransform()->setPosition(mPlayer->getTransform()->getPosition() + mPlayer->getTransform()->getPivot());

    if (mCurrentAnchorLength >= MAX_LENGTH) {
        Actor::destroy(mOwner);
    }
}

const float AnchorComponent::MAX_LENGTH = 400.f;
