#pragma once

#include "../Component.h"
#include "../../Utility/Math.h"
#include <memory>

enum class EnemyState {
    NORMAL,
    HIT,
    DEAD
};

class Actor;
class CircleCollisionComponent;
class HitPointComponent;
class Time;

class EnemyComponent : public Component {
public:
    EnemyComponent(Actor* owner);
    ~EnemyComponent();
    virtual void start() override;
    virtual void update() override;

private:
    void move();
    void hit();
    void dead();
    void deadMove();

private:
    std::shared_ptr<CircleCollisionComponent> mCollider;
    std::shared_ptr<HitPointComponent> mHP;
    std::unique_ptr<Time> mHittedTimer;
    std::unique_ptr<Time> mDeadTimer;
    Vector2 mHitDir;
    EnemyState mState;
};

