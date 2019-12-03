#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class DamageComponent;
class EnemyBullet2Component;
class Sprite;
class SpriteComponent;

class EnemyBullet2 : public Actor {
public:
    EnemyBullet2(Sprite* enemySprite, float rotation, float rate, const char* tag = "EnemyBullet");
    ~EnemyBullet2();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    DamageComponent* mDamage;
    EnemyBullet2Component* mEnemyBullet;
    SpriteComponent* mSprite;

    static int mExistCount;
};
