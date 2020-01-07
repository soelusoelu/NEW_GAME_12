#include "AnchorActor.h"
#include "Transform2D.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

AnchorActor::AnchorActor(
    std::shared_ptr<Renderer> renderer,
    const Vector2& playerCenterPosition,
    const Vector2& anchorDirection,
    float length,
    const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "black.png", 0.55f)) {
    getTransform()->setScale(Vector2(1.f, length / 2.f), mSprite->getTextureSize());
    getTransform()->setRotation(Math::toDegrees(Math::atan2(-anchorDirection.x, -anchorDirection.y)));
    getTransform()->setPosition(Vector2(playerCenterPosition.x, playerCenterPosition.y));
}

AnchorActor::~AnchorActor() = default;

void AnchorActor::updateActor() {
}
