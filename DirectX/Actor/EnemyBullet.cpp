#include "EnemyBullet.h"
#include "../Component/Enemy/EnemyBulletComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

EnemyBullet::EnemyBullet(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(renderer, tag),
    mCircle(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, "fire.png")),
    mBullet(new EnemyBulletComponent(this)) {
    mSprite->setActive(false);
}

EnemyBullet::~EnemyBullet() = default;

void EnemyBullet::updateActor() {
}

void EnemyBullet::shot() {
    mBullet->shot();
}

bool EnemyBullet::isReady() const {
    return mBullet->isReady();
}
