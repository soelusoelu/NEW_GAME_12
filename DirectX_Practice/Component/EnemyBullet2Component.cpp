#include "EnemyBullet2Component.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"

EnemyBullet2Component::EnemyBullet2Component(Actor* owner, Sprite* enemySprite, float rotation, float rate) :
    Component(owner),
    mSprite(nullptr),
    mEnemySprite(enemySprite),
    mVelocity(Vector2::zero),
    mWaitingTimer(std::make_unique<Time>(1.f * rate)),
    ROTATION(rotation),
    BULLET_SPEED(7.f) {
    auto x = Math::cos(ROTATION * Math::deg2Rad);
    auto y = Math::sin(ROTATION * Math::deg2Rad);
    mVelocity = Vector2(x, y);
}

EnemyBullet2Component::~EnemyBullet2Component() = default;

void EnemyBullet2Component::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setPosition(mEnemySprite->getPosition() + mEnemySprite->getPivot() * mEnemySprite->getScale());
    mSprite->translate(mVelocity * mSprite->getScreenTextureSize() * 1.5f);
    mSprite->setScale(0.f);
}

void EnemyBullet2Component::update() {
    mSprite->setScale(mSprite->getScale().x + 0.05f);
    if (mSprite->getScale().x > 1.f) {
        mSprite->setScale(1.f);
    }
    mSprite->rotate(5.f);

    mWaitingTimer->update();
    if (!mWaitingTimer->isTime()) {
        return;
    }
    mSprite->translate(mVelocity * BULLET_SPEED * AvoidancePlayerActor::slow());
    destroy();
}

void EnemyBullet2Component::destroy() {
    auto lengthX = Math::abs(mSprite->getPosition().x);
    auto lengthY = Math::abs(mSprite->getPosition().y);
    if (lengthX > Game::WINDOW_WIDTH + 100 || lengthY > Game::WINDOW_HEIGHT + 100) {
        Actor::destroy(mOwner);
    }
}
