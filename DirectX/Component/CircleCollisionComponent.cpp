#include "CircleCollisionComponent.h"
#include "ComponentManager.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) :
    Collider(owner),
    mCircle(nullptr),
    mIsAutoUpdate(true)
{
}

CircleCollisionComponent::~CircleCollisionComponent() = default;

void CircleCollisionComponent::startCollider() {
    mCircle = std::make_shared<Circle>(
        mOwner->transform()->getPosition() + mOwner->transform()->getPivot(),
        mOwner->transform()->getPivot().x
    );
}

void CircleCollisionComponent::updateCollider() {
}

void CircleCollisionComponent::onUpdateWorldTransformCollider() {
    if (!mIsAutoUpdate) {
        return;
    }
    mCircle->set(
        mOwner->transform()->getPosition() + mOwner->transform()->getPivot(),
        mOwner->transform()->getPivot().x
    );
}

void CircleCollisionComponent::set(const Vector2& center, float radius) {
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
