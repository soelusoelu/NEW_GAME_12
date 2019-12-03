#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Sprite;
class Time;

class EnemyBullet1Component : public Component {
public:
    EnemyBullet1Component(Actor* onwer, Sprite* enemySprite, Sprite* playerSprite, float rate);
    ~EnemyBullet1Component();
    virtual void start() override;
    virtual void update() override;

private:
    void move();
    void destroy();

private:
    Sprite* mSprite;
    Sprite* mEnemySprite;
    Sprite* mPlayerSprite;
    Vector2 mE2P;
    std::unique_ptr<Time> mWaitingTimer;
    const float BULLET_SPEED;
    const float MAX_SCALE;
    const float MIN_SCALE;
    const float ROTATE_SPEED;
    const float SCALING_SPEED;
    int mScaleCounter;
};

