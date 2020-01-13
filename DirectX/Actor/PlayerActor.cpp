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
    transform()->setPosition(Vector2(100.f, 100.f));
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

Vector2 PlayerActor::getLastInput() const {
    return mMove->getLastInput();
}

bool PlayerActor::isHitAnchor() const {
    return mMove->isHitAnchor();
}

const float PlayerActor::anchorMaxLength() const {
    return mMove->anchorMaxLength();
}
