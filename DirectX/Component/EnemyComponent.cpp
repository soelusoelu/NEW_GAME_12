#include "EnemyComponent.h"
#include "CircleCollisionComponent.h"
#include "ComponentManager.h"
#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Random.h"
#include "../Device/Time.h"

EnemyComponent::EnemyComponent(Actor* owner) :
    Component(owner),
    mCollider(nullptr),
    mHittedTimer(std::make_unique<Time>(2.f)),
    mHitDir(Vector2::zero),
    mState(State::NORMAL) {
}

EnemyComponent::~EnemyComponent() = default;

void EnemyComponent::start() {
    mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();

    mOwner->transform()->setScale(Random::randomRange(0.3f, 1.f));
    mOwner->transform()->setPosition(Random::randomRange(Vector2::one * 200.f, Vector2::one * 600.f));
}

void EnemyComponent::update() {
    move();
    hit();
}

void EnemyComponent::move() {
    if (mState != State::HIT) {
        return;
    }
    mHittedTimer->update();
    if (mHittedTimer->isTime()) {
        mHittedTimer->reset();
        mState = State::NORMAL;
    } else {
        auto s = mOwner->transform()->getScale();
        auto rate = Vector2::one - s;
        rate.clamp(Vector2(0.1f, 0.1f), Vector2::one);

        mOwner->transform()->translate(mHitDir * rate * 200.f * Time::deltaTime);
    }
}

void EnemyComponent::hit() {
    for (auto&& c : mCollider->onCollisionEnter()) {
        if (c->getOwner()->tag() == "Player") {
            auto pmc = c->getOwner()->componentManager()->getComponent<PlayerMoveComponent>();
            if (!pmc) {
                return;
            }
            mHitDir = pmc->getMoveDirection();

            mState = State::HIT;
        }
    }

    for (auto&& c : mCollider->onCollisionStay()) {
        if (c->getOwner()->tag() == "Player") {
        }
    }
}
