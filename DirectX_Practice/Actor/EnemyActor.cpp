#include "EnemyActor.h"
#include "PlayerActor.h"
#include "ComponentManagementOfActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/EnemyMoveComponent.h"
#include "../Component/SPComponent.h"
#include "../Component/SpriteComponent.h"

EnemyActor::EnemyActor(PlayerActor* player, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mHP(new HitPointComponent(this, 10000)),
    mEnemyMove(new EnemyMoveComponent(this, player)),
    mSprite(new SpriteComponent(this, "boss_anime.png", Vector2(512.f, 512.f), 0.6f)) {
}

EnemyActor::~EnemyActor() = default;

void EnemyActor::updateActor() {
}

void EnemyActor::drawActor() const {
}
