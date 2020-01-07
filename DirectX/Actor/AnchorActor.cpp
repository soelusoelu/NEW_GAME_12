#include "AnchorActor.h"
#include "Transform2D.h"
#include "../Component/AnchorComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

AnchorActor::AnchorActor(
    std::shared_ptr<Renderer> renderer,
    Actor* player,
    const Vector2& anchorDirection,
    const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "black.png", 0.55f)),
    mAnchor(new AnchorComponent(this, player, anchorDirection)) {
}

AnchorActor::~AnchorActor() = default;

void AnchorActor::updateActor() {
}
