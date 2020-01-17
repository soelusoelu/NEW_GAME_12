#include "EnemyActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/EnemyComponent.h"
#include "../Component/ShotEnemyComponent.h"
#include "../Component/SpriteComponent.h"

EnemyActor::EnemyActor(std::shared_ptr<Renderer> renderer, EnemyType type, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "player.png", 0.6f)),
    mEnemy(new EnemyComponent(this)) {
    if (type == EnemyType::NORMAL) {

    } else if (type == EnemyType::SHOT) {
        new ShotEnemyComponent(renderer, this);
    } else if (type == EnemyType::TACKLE) {

    }
}

EnemyActor::~EnemyActor() = default;

void EnemyActor::updateActor() {
}
