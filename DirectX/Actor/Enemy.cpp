#include "Enemy.h"
#include "Transform2D.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/EnemyComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Random.h"

Enemy::Enemy(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "player.png", 0.6f)),
    mEnemy(new EnemyComponent(this)) {
    transform()->setScale(Random::randomRange(0.3f, 1.f));
    transform()->setPosition(Random::randomRange(Vector2::one * 200.f, Vector2::one * 600.f));
}

Enemy::~Enemy() = default;

void Enemy::updateActor() {
}

