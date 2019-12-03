#pragma once

#include "Actor.h"
#include <memory>

class Sprite;
class Time;

class EnemyBullet1Manager : public Actor {
public:
    EnemyBullet1Manager(Sprite* enemySprite, Sprite* playerSprite, bool* completedAttack, int shotCount, float rate);
    ~EnemyBullet1Manager();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    bool* mCompletedAttack;
    Sprite* mEnemySprite;
    Sprite* mPlayerSprite;
    int mShotCount;
    int mCurrentShotCount;
    float mRate;
    std::unique_ptr<Time> mNextShotTimer;
    std::unique_ptr<Time> mDestroyTimer;
};

