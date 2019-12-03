#pragma once

#include "Component.h"
#include <memory>

class Actor;
class PlayerActor;
class Sprite;
class Time;

class SpecialAttackComponent : public Component {
public:
    SpecialAttackComponent(Actor* onwer, PlayerActor* player);
    ~SpecialAttackComponent();
    virtual void start() override;
    virtual void update() override;

private:
    Sprite* mSprite;
    Sprite* mPlayer;
    float ROTATE_SPEED;
    std::unique_ptr<Time> mDestroyTimer;
};

