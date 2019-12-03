#pragma once

#include "Actor.h"
#include <memory>

class Sprite;
class Time;

class EnemyBullet2Manager : public Actor {
public:
    EnemyBullet2Manager(Sprite* enemySprite, bool* completedAttack, int shotCount, float rate);
    ~EnemyBullet2Manager();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    bool* mCompletedAttack;
    std::unique_ptr<Time> mDestroyTimer;
};

