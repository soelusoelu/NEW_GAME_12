#include "PlayerAttack.h"
#include "PlayerActor.h"
#include "ComponentManagementOfActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/PlayerAttackComponent.h"
#include "../Component/SPComponent.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

PlayerAttack::PlayerAttack(PlayerActor* player, const Vector2& pos, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, 0)),
    mAttack(new PlayerAttackComponent(this, player)),
    mSprite(new SpriteComponent(this, "sowrdEffect3.png", Vector2(155.f, 155.f), 0.3f)) {
    auto spComp = player->getComponentManager()->getComponent<SPComponent>();
    auto sp = spComp->sp();
    mDamage->setDamageOfPlayerAttack(spComp->computeGaugeCount(sp - 1));
    auto sprite = mSprite->getSprite();
    sprite->setPosition(pos);
}

PlayerAttack::~PlayerAttack() = default;

void PlayerAttack::updateActor() {
}

void PlayerAttack::drawActor() const {
}
