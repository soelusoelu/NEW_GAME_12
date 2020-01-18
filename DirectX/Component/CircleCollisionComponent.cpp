#include "CircleCollisionComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) :
    Collider(owner),
    mCircle(nullptr),
    mIsAutoUpdate(true) {
}

CircleCollisionComponent::~CircleCollisionComponent() = default;

void CircleCollisionComponent::startCollider() {
    auto size = mOwner->transform()->getTextureSize() * 0.5f * mOwner->transform()->getWorldScale();
    auto radius = Math::Max<float>(size.x, size.y);
    mCircle = std::make_shared<Circle>(mOwner->transform()->getWorldPosition(), radius);
}

void CircleCollisionComponent::updateCollider() {
}

void CircleCollisionComponent::onUpdateWorldTransformCollider() {
    if (!mIsAutoUpdate) {
        return;
    }

    auto size = mOwner->transform()->getTextureSize() * 0.5f * mOwner->transform()->getWorldScale();
    auto radius = Math::Max<float>(size.x, size.y);

    mCircle->set(mOwner->transform()->getWorldPosition(), radius);
}

void CircleCollisionComponent::set(const Vector2 & center, float radius) {
    mCircle->set(center, radius);
    if (mIsAutoUpdate) {
        mIsAutoUpdate = false;
    }
}

std::shared_ptr<Circle> CircleCollisionComponent::getCircle() const {
    return mCircle;
}

void CircleCollisionComponent::automation() {
    if (!mIsAutoUpdate) {
        mIsAutoUpdate = true;
    }
}
