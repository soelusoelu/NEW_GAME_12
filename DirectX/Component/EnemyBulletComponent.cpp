#include "EnemyBulletComponent.h"
#include "CircleCollisionComponent.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorManager.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"

EnemyBulletComponent::EnemyBulletComponent(Actor* owner) :
    Component(owner),
    mPlayer(),
    mCollider(nullptr),
    mBulletSpeed(600.f),
    mBulletDir(Vector2::zero) {
}

EnemyBulletComponent::~EnemyBulletComponent() = default;

void EnemyBulletComponent::start() {
    mPlayer = mOwner->getActorManager()->getPlayer();
    mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
    mOwner->componentManager()->getComponent<SpriteComponent>()->setActive(true);

    if (auto p = mPlayer.lock()) {
        auto toPlayer = p->transform()->getPosition() - mOwner->transform()->parent()->getPosition();
        mBulletDir = Vector2::normalize(toPlayer);
    }
}

void EnemyBulletComponent::update() {
    mOwner->transform()->translate(mBulletDir * mBulletSpeed * Time::deltaTime);

    for (auto&& c : mCollider->onCollisionEnter()) {
        if (c->getOwner()->tag() == "Player") {
            Actor::destroy(mOwner);
        }
    }
}
