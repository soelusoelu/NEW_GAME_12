#include "EnemyBullet1Component.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Sound.h"
#include "../Device/Time.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"

EnemyBullet1Component::EnemyBullet1Component(Actor* onwer, Sprite* enemySprite, Sprite* playerSprite, float rate) :
    Component(onwer),
    mSprite(nullptr),
    mEnemySprite(enemySprite),
    mPlayerSprite(playerSprite),
    mE2P(Vector2::zero),
    mWaitingTimer(std::make_unique<Time>(2.5f * rate)),
    BULLET_SPEED(5.f),
    MAX_SCALE(3.f),
    MIN_SCALE(1.5f),
    ROTATE_SPEED(13.f),
    SCALING_SPEED(0.03f),
    mScaleCounter(0) {
}

EnemyBullet1Component::~EnemyBullet1Component() = default;

void EnemyBullet1Component::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setPosition(mEnemySprite->getPosition());

    mE2P = mPlayerSprite->getPosition() - mSprite->getPosition();
    mE2P.normalize();

    auto right = mE2P.x > 0 ? mSprite->getScreenTextureSize().x : 0.f;
    mSprite->translate(Vector2(mE2P.x * 100.f + right, 0.f));
}

void EnemyBullet1Component::update() {
    move();
    destroy();
}

void EnemyBullet1Component::move() {
    mSprite->rotate(ROTATE_SPEED * AvoidancePlayerActor::slow());

    mScaleCounter += SCALING_SPEED * 100 * AvoidancePlayerActor::slow();
    mSprite->setScale(Math::sin(mScaleCounter * Math::deg2Rad) * MAX_SCALE, true);
    if (mScaleCounter >= 165) {
        mScaleCounter = 15;
    }

    mWaitingTimer->update();
    if (!mWaitingTimer->isTime()) {
        return;
    }
    static bool first = true;
    if (first) {
        first = false;
        Sound::play("boss_attak2.wav");
    }

    mSprite->translate(mE2P * BULLET_SPEED * AvoidancePlayerActor::slow());
}

void EnemyBullet1Component::destroy() {
    auto lengthX = Math::abs(mSprite->getPosition().x);
    auto lengthY = Math::abs(mSprite->getPosition().y);
    if (lengthX > Game::WINDOW_WIDTH + 100 || lengthY > Game::WINDOW_HEIGHT + 100) {
        Actor::destroy(mOwner);
    }
}
