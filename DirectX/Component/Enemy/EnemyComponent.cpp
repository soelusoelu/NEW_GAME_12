#include "EnemyComponent.h"
#include "../CircleCollisionComponent.h"
#include "../ComponentManager.h"
#include "../HitPointComponent.h"
#include "../PlayerMoveComponent.h"
#include "../../Actor/Actor.h"
#include "../../Actor/Transform2D.h"
#include "../../Device/Time.h"

EnemyComponent::EnemyComponent(Actor* owner) :
    Component(owner),
    mCollider(nullptr),
    mHittedTimer(std::make_unique<Time>(2.f)),
    mDeadTimer(nullptr),
    mHitDir(Vector2::zero),
    mState(EnemyState::NORMAL) {
}

EnemyComponent::~EnemyComponent() = default;

void EnemyComponent::start() {
    mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
    mHP = mOwner->componentManager()->getComponent<HitPointComponent>();
}

void EnemyComponent::update() {
    move();
    hit();
    dead();
    deadMove();
}

void EnemyComponent::move() {
    if (mState != EnemyState::HIT) {
        return;
    }
    mHittedTimer->update();
    if (mHittedTimer->isTime()) {
        mHittedTimer->reset();
        mState = EnemyState::NORMAL;
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
            if (pmc) {
                mHitDir = pmc->getMoveDirection();
                mHP->takeDamage(pmc->getSpeedRate());
            }

            mState = EnemyState::HIT;
        }
    }

    for (auto&& c : mCollider->onCollisionStay()) {
        if (c->getOwner()->tag() == "Player") {
            auto p = c->getOwner()->transform();
            auto e = mOwner->transform();

            //‚ß‚èž‚Ü‚È‚¢ˆ—
            auto d = Vector2::distance(p->getPosition(), e->getPosition());
            auto r = (p->getSize().x * p->getScale().x / 2.f) + (e->getSize().x * e->getScale().x / 2.f);

            e->translate(Vector2::normalize(mHitDir) * (r - d));
        }
    }
}

void EnemyComponent::dead() {
    if (mState == EnemyState::DEAD) {
        return;
    }
    if (mHP->hp() <= 0) {
        mDeadTimer = std::make_unique<Time>(1.f);
        mState = EnemyState::DEAD;
    }
}

void EnemyComponent::deadMove() {
    if (mState != EnemyState::DEAD || !mDeadTimer) {
        return;
    }
    mDeadTimer->update();
    if (mDeadTimer->isTime()) {
        Actor::destroy(mOwner);
    }
    mOwner->transform()->translate(mHitDir * 50.f * Time::deltaTime);
}
