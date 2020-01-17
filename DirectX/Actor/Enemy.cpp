#include "Enemy.h"
#include "EnemyActor.h"
#include "Transform2D.h"
#include "../Device/Random.h"

Enemy::Enemy(std::shared_ptr<Renderer> renderer) :
    mRenderer(renderer) {
}

Enemy::~Enemy() = default;

void Enemy::create(EnemyScale scale, EnemyType type) {
    auto e = new EnemyActor(mRenderer, type);
    auto s = 1.f;
    auto pos = Vector2::zero;
    if (scale == EnemyScale::SMALL) {
        s = 0.3f;
        pos = Random::randomRange(Vector2::one * 200.f, Vector2::one * 600.f);
    } else if (scale == EnemyScale::MIDDLE) {
        s = 0.5f;
        pos = Random::randomRange(Vector2::one * 200.f, Vector2::one * 600.f);
    } else if (scale == EnemyScale::BIG) {
        s = 0.8f;
        pos = Random::randomRange(Vector2::one * 200.f, Vector2::one * 600.f);
    }
    e->transform()->setScale(s);
    e->transform()->setPosition(pos);
}

