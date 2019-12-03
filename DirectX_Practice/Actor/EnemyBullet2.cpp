#include "EnemyBullet2.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/EnemyBullet2Component.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

EnemyBullet2::EnemyBullet2(Sprite* enemySprite, float rotation, float rate, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, 50)),
    mEnemyBullet(new EnemyBullet2Component(this, enemySprite, rotation, rate)),
    mSprite(new SpriteComponent(this, "fire.png", Vector2(64.f, 64.f), 0.2f - mExistCount / 300.f)) {
    mExistCount++;
}

EnemyBullet2::~EnemyBullet2() {
    mExistCount--;
}

void EnemyBullet2::updateActor() {
}

void EnemyBullet2::drawActor() const {
}

int EnemyBullet2::mExistCount = 0;
