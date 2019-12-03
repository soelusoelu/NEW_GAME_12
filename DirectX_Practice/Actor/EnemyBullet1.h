#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class DamageComponent;
class EnemyBullet1Component;
class Sprite;
class SpriteComponent;

class EnemyBullet1 : public Actor {
public:
    EnemyBullet1(Sprite* enemySprite, Sprite* playerSprite, float rate, const char* tag = "EnemyBullet");
    ~EnemyBullet1();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    DamageComponent* mDamage;
    EnemyBullet1Component* mEnemyBullet;
    SpriteComponent* mSprite;

    static int mExistCount;
};