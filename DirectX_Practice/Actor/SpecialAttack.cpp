#include "SpecialAttack.h"
#include "PlayerActor.h"
#include "ComponentManagementOfActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/SPComponent.h"
#include "../Component/SpecialAttackComponent.h"
#include "../Component/SpriteComponent.h"

SpecialAttack::SpecialAttack(PlayerActor* player, const char * tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, 0)),
    mSpecialAttack(new SpecialAttackComponent(this, player)),
    mSprite(new SpriteComponent(this, "sowrdEffect.png", Vector2(192.f, 192.f), 0.25f)) {
    auto spComp = player->getComponentManager()->getComponent<SPComponent>();
    mDamage->setDamageOfPlayerSpecialAttack(spComp->getCurrentGaugeCount());
}

SpecialAttack::~SpecialAttack() = default;

void SpecialAttack::updateActor() {
}

void SpecialAttack::drawActor() const {
}
