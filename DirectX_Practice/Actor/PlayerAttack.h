#pragma once

#include "Actor.h"
#include "../Utility/Math.h"

class PlayerActor;
class CircleCollisionComponent;
class DamageComponent;
class PlayerAttackComponent;
class SpriteComponent;

class PlayerAttack : public Actor {
public:
    PlayerAttack(PlayerActor* player, const Vector2& pos, const char* tag = "PlayerAttack");
    ~PlayerAttack();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    DamageComponent* mDamage;
    PlayerAttackComponent* mAttack;
    SpriteComponent* mSprite;
};