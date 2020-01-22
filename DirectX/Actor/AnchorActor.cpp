#include "AnchorActor.h"
#include "Transform2D.h"
#include "../Component/AnchorComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

AnchorActor::AnchorActor(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(renderer, tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, "black.png")),
    mAnchor(new AnchorComponent(this)) {
}

AnchorActor::~AnchorActor() = default;

void AnchorActor::updateActor() {
}

void AnchorActor::shot(const Vector2& direction) {
    mAnchor->shot(direction);
}

bool AnchorActor::isHit() const {
    return mAnchor->isHit();
}

bool AnchorActor::canShot() const {
    return mAnchor->canShot();
}

const float AnchorActor::maxLength() const {
    return mAnchor->maxLength();
}

float AnchorActor::currentLength() const {
    return mAnchor->currentLength();
}

void AnchorActor::setCurrentLength(float length) {
    mAnchor->setCurrentLength(length);
}

Actor* AnchorActor::hitActor() const {
    return mAnchor->hitActor();
}

float AnchorActor::hitAngle() const {
    return mAnchor->hitAngle();
}
