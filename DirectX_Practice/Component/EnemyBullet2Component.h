#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Sprite;
class Time;

class EnemyBullet2Component : public Component {
public:
    EnemyBullet2Component(Actor* owner, Sprite* enemySprite, float rotation, float rate);
    ~EnemyBullet2Component();
    virtual void start() override;
    virtual void update() override;

private:
    void destroy();

private:
    Sprite* mSprite;
    Sprite* mEnemySprite;
    Vector2 mVelocity;
    std::unique_ptr<Time> mWaitingTimer;
    float ROTATION;
    float BULLET_SPEED;
};

