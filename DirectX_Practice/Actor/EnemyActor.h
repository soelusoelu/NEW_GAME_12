#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class EnemyMoveComponent;
class HitPointComponent;
class SpriteComponent;
class PlayerActor;

class EnemyActor : public Actor {
public:
    EnemyActor(PlayerActor* player, const char* tag = "Enemy");
    ~EnemyActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    EnemyMoveComponent* mEnemyMove;
    HitPointComponent* mHP;
    SpriteComponent* mSprite;
};

