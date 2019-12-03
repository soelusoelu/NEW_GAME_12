#include "CircleCollisionComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Physics.h"
#include "../UI/Sprite.h"
#include <algorithm>
#include <cassert>

CircleCollisionComponent::CircleCollisionComponent(Actor* onwer) :
    Component(onwer, 1000),
    mCircle(nullptr),
    mSprite(nullptr),
    mEnable(true) {
}

CircleCollisionComponent::~CircleCollisionComponent() {
    Physics::remove(this);
}

void CircleCollisionComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    assert(mSprite);

    mCircle = std::make_shared<Circle>(
        mSprite->getPosition() + mSprite->getPivot(),
        mSprite->getScreenTextureSize().x - mSprite->getPivot().x
        );

    Physics::add(this);
}

void CircleCollisionComponent::update() {
    mCircle->set(
        mSprite->getPosition() + mSprite->getPivot(),
        mSprite->getScreenTextureSize().x - mSprite->getPivot().x
    );

    mPreviousCircles.resize(mCurrentCircles.size());
    std::copy(mCurrentCircles.begin(), mCurrentCircles.end(), mPreviousCircles.begin());
    mCurrentCircles.clear();
}

std::shared_ptr<Circle> CircleCollisionComponent::getCircle() const {
    return mCircle;
}

void CircleCollisionComponent::enabled() {
    mEnable = true;
}

void CircleCollisionComponent::disabled() {
    mEnable = false;
}

bool CircleCollisionComponent::getEnable() const {
    return mEnable;
}

void CircleCollisionComponent::addHitCircle(CircleCollisionComponent* hit) {
    mCurrentCircles.emplace_back(hit);
}

std::list<CircleCollisionComponent*> CircleCollisionComponent::onCollisionEnter() {
    std::list<CircleCollisionComponent*> temp;
    for (auto&& c : mCurrentCircles) {
        auto itr = std::find(mPreviousCircles.begin(), mPreviousCircles.end(), c);
        if (itr == mPreviousCircles.end()) {
            temp.emplace_back(c);
        }
    }

    return temp;
}

std::list<CircleCollisionComponent*> CircleCollisionComponent::onCollisionStay() {
    std::list<CircleCollisionComponent*> temp;
    for (auto&& c : mCurrentCircles) {
        auto itr = std::find(mPreviousCircles.begin(), mPreviousCircles.end(), c);
        if (itr != mPreviousCircles.end()) {
            temp.emplace_back(c);
        }
    }

    return temp;
}

std::list<CircleCollisionComponent*> CircleCollisionComponent::onCollisionExit() {
    std::list<CircleCollisionComponent*> temp;
    for (auto&& c : mPreviousCircles) {
        auto itr = std::find(mCurrentCircles.begin(), mCurrentCircles.end(), c);
        if (itr == mCurrentCircles.end()) {
            temp.emplace_back(c);
        }
    }

    return temp;
}
