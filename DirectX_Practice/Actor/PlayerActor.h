#pragma once

#include "Actor.h"

class AnimationComponent;
class CircleCollisionComponent;
class HitPointComponent;
class PlayerMoveComponent;
class SPComponent;
class SpriteComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    AnimationComponent* mAnimation;
    CircleCollisionComponent* mCircle;
    HitPointComponent* mHP;
    PlayerMoveComponent* mPlayerMove;
    SPComponent* mSP;
    SpriteComponent* mSprite;
};

