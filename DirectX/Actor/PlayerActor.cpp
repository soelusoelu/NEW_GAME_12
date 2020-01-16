#include "PlayerActor.h"
#include "Transform2D.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SpriteComponent.h"

PlayerActor::PlayerActor(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "circleP.png", 0.5f)),
    mMove(new PlayerMoveComponent(this, renderer)) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

void PlayerActor::anchorReleaseAcceleration() {
    mMove->anchorReleaseAcceleration();
}

Vector2 PlayerActor::getAnchorDirection() const {
    return mMove->getAnchorDirection();
}

bool PlayerActor::isHitAnchor() const {
    return mMove->isHitAnchor();
}

const float PlayerActor::anchorMaxLength() const {
    return mMove->anchorMaxLength();
}

void PlayerActor::rotateDirection() {
    mMove->rotateDirection();
}
