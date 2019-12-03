#include "SpecialAttackComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"
#include "../UI/Sprite.h"

SpecialAttackComponent::SpecialAttackComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mSprite(nullptr),
    mPlayer(player->getComponentManager()->getComponent<SpriteComponent>()->getSprite()),
    ROTATE_SPEED(30.f),
    mDestroyTimer(std::make_unique<Time>(1.f)) {
}

SpecialAttackComponent::~SpecialAttackComponent() = default;

void SpecialAttackComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setScale(3.f, true);
}

void SpecialAttackComponent::update() {
    mSprite->rotate(ROTATE_SPEED);
    mSprite->setPosition(mPlayer->getPosition() - Vector2(85.f, 85.f) * mSprite->getScale());

    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(mOwner);
    }
}
