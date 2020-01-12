#include "AnchorActor.h"
#include "Transform2D.h"
#include "../Component/AnchorComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

AnchorActor::AnchorActor(std::shared_ptr<Renderer> renderer, std::shared_ptr<Transform2D> player, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "black.png", 0.55f)),
    mAnchor(new AnchorComponent(this, player)) {
}

AnchorActor::~AnchorActor() = default;

void AnchorActor::updateActor() {
}

void AnchorActor::initialize(const Vector2& direction) {
    mAnchor->initialize(direction);
}

bool AnchorActor::isHit() const {
    return mAnchor->isHit();
}
