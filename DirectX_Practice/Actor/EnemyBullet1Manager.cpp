#include "EnemyBullet1Manager.h"
#include "EnemyBullet1.h"
#include "../Device/Time.h"

EnemyBullet1Manager::EnemyBullet1Manager(Sprite* enemySprite, Sprite* playerSprite, bool* completedAttack, int shotCount, float rate) :
    Actor(),
    mCompletedAttack(completedAttack),
    mEnemySprite(enemySprite),
    mPlayerSprite(playerSprite),
    mShotCount(shotCount),
    mCurrentShotCount(0),
    mRate(rate),
    mNextShotTimer(std::make_unique<Time>(0.5f)),
    mDestroyTimer(std::make_unique<Time>(4.f)) {
    new EnemyBullet1(enemySprite, playerSprite, mRate);
    mCurrentShotCount++;
}

EnemyBullet1Manager::~EnemyBullet1Manager() {
    *mCompletedAttack = true;
}

void EnemyBullet1Manager::updateActor() {
    if (mCurrentShotCount < mShotCount) {
        mNextShotTimer->update();
        if (mNextShotTimer->isTime()) {
            mNextShotTimer->reset();
            new EnemyBullet1(mEnemySprite, mPlayerSprite, mRate);
            mCurrentShotCount++;
        }
    }

    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(this);
    }
}

void EnemyBullet1Manager::drawActor() const {
}
