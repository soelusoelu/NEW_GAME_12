#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

enum class State {
    NORMAL,
    HIT
};

class Actor;
class CircleCollisionComponent;
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

private:
    std::shared_ptr<CircleCollisionComponent> mCollider;
    std::unique_ptr<Time> mHittedTimer;
    Vector2 mHitDir;
    State mState;
};

