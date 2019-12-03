#pragma once

#include "Actor.h"
#include "../Utility/Math.h"

class PlayerActor;
class CircleCollisionComponent;
class DamageComponent;
class SpecialAttackComponent;
class SpriteComponent;

class SpecialAttack : public Actor {
public:
    SpecialAttack(PlayerActor* player, const char* tag = "PlayerAttack");
    ~SpecialAttack();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    DamageComponent* mDamage;
    SpecialAttackComponent* mSpecialAttack;
    SpriteComponent* mSprite;
};

