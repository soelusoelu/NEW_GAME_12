#include "EnemyActor.h"
#include "../Component/Enemy/EnemyComponent.h"
#include "../Component/Enemy/ShotEnemyComponent.h"
#include "../Component/Enemy/TackleEnemyComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SpriteComponent.h"

EnemyActor::EnemyActor(std::shared_ptr<Renderer> renderer, EnemyType type, const std::string& scale, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, renderer, "player.png", 0.6f)),
    mHP(new HitPointComponent(this, 1)), //HP‚Í‰¼
    mEnemy(new EnemyComponent(this)) {
    if (type == EnemyType::NORMAL) {
        //‚È‚µ
    } else if (type == EnemyType::SHOT) {
        new ShotEnemyComponent(this, renderer);
    } else if (type == EnemyType::TACKLE) {
        new TackleEnemyComponent(this);
    }

    if (scale == "Small") {
        mHP->setHP(2);
    } else if (scale == "Middle") {
        mHP->setHP(10);
    } else if (scale == "Large") {
        mHP->setHP(30);
    }
}

EnemyActor::~EnemyActor() = default;

void EnemyActor::updateActor() {
}
