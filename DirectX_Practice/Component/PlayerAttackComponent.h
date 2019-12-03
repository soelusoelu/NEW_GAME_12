#pragma once

#include "Component.h"
#include <memory>

class Actor;
class PlayerActor;
class CircleCollisionComponent;
class Time;

class PlayerAttackComponent : public Component {
public:
    PlayerAttackComponent(Actor* onwer, PlayerActor* player);
    ~PlayerAttackComponent();
    virtual void start() override;
    virtual void update() override;

private:
    PlayerActor* mPlayer;
    std::shared_ptr<CircleCollisionComponent> mCircle;
    std::unique_ptr<Time> mTimer;
    const int SP_HEAL_POINT;
    bool mAlreadyHeal;
};

