#include "EnemyBullet1.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/EnemyBullet1Component.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

EnemyBullet1::EnemyBullet1(Sprite* enemySprite, Sprite* playerSprite, float rate, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, 200)),
    mEnemyBullet(new EnemyBullet1Component(this, enemySprite, playerSprite, rate)),
    mSprite(new SpriteComponent(this, "BigFire.png", Vector2(64.f, 64.f), 0.19f - mExistCount / 180.f)) {
    mExistCount++;
}

EnemyBullet1::~EnemyBullet1() {
    mExistCount--;
}

void EnemyBullet1::updateActor() {
}

void EnemyBullet1::drawActor() const {
}

int EnemyBullet1::mExistCount = 0;
