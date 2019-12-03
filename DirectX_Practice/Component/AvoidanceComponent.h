#pragma once

#include "../Component/Component.h"
#include <memory>

class Actor;
class CircleCollisionComponent;
class PlayerActor;
class Time;

class AvoidanceComponent : public Component {
public:
    AvoidanceComponent(Actor* onwer, PlayerActor* player);
    ~AvoidanceComponent();
    virtual void start() override;
    virtual void update() override;

private:
    std::shared_ptr<CircleCollisionComponent> mCircle;
    std::unique_ptr<Time> mDestroyTimer;
    PlayerActor* mPlayer;
    const int SP_HEAL_POINT;
    bool mAlreadyHeal;
};
