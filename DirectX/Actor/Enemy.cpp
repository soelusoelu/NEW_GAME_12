#include "Enemy.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/EnemyComponent.h"
#include "../Component/SpriteComponent.h"

Enemy::Enemy(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "player.png", 0.6f)),
    mEnemy(new EnemyComponent(this)) {
}

Enemy::~Enemy() = default;

void Enemy::updateActor() {
}

