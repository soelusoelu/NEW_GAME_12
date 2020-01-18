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
    auto pivot = mOwner->transform()->getPivot() * mOwner->transform()->getWorldScale();
    auto radius = Math::Max<float>(pivot.x, pivot.y);
    mCircle = std::make_shared<Circle>(mOwner->transform()->getWorldPosition(), radius);
}

void CircleCollisionComponent::updateCollider() {
}

void CircleCollisionComponent::onUpdateWorldTransformCollider() {
    if (!mIsAutoUpdate) {
        return;
    }

    auto pivot = mOwner->transform()->getPivot() * mOwner->transform()->getWorldScale();
    auto radius = Math::Max<float>(pivot.x, pivot.y);

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
