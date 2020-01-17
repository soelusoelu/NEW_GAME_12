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
    mCollider(nullptr),
    mSprite(nullptr),
    mEndTimer(std::make_unique<Time>(5.f)),
    mBulletDir(Vector2::zero),
    mState(BulletState::READY) {
}

EnemyBulletComponent::~EnemyBulletComponent() = default;

void EnemyBulletComponent::start() {
    mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
    mCollider->disabled();
    mSprite = mOwner->componentManager()->getComponent<SpriteComponent>();
    mSprite->setActive(false);
}

void EnemyBulletComponent::update() {
    if (mState != BulletState::UPDATING) {
        return;
    }
    mOwner->transform()->translate(mBulletDir * BULLET_SPEED * Time::deltaTime);

    mEndTimer->update();
    if (mEndTimer->isTime()) {
        end();
    }

    for (auto&& c : mCollider->onCollisionEnter()) {
        if (c->getOwner()->tag() == "Player") {
            end();
        }
    }
}

void EnemyBulletComponent::shot() {
    auto player = mOwner->getActorManager()->getPlayer();
    auto toPlayer = player->transform()->getPosition() - mOwner->transform()->parent()->getPosition();
    mBulletDir = Vector2::normalize(toPlayer);

    mState = BulletState::UPDATING;
    mCollider->enabled();
    mSprite->setActive(true);
    mOwner->transform()->setPosition(Vector2::zero);
}

bool EnemyBulletComponent::isReady() const {
    return mState == BulletState::READY;
}

void EnemyBulletComponent::end() {
    mState = BulletState::READY;
    mCollider->disabled();
    mSprite->setActive(false);
    mEndTimer->reset();
}

const float EnemyBulletComponent::BULLET_SPEED = 600.f;
