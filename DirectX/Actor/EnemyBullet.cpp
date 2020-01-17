#include "EnemyBullet.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/EnemyBulletComponent.h"

EnemyBullet::EnemyBullet(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "fire.png", 0.4f)),
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
