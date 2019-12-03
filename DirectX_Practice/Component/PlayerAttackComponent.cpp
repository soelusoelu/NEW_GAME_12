#include "PlayerAttackComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Time.h"

PlayerAttackComponent::PlayerAttackComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mPlayer(player),
    mCircle(nullptr),
    mTimer(std::make_unique<Time>(0.16f)),
    SP_HEAL_POINT(5),
    mAlreadyHeal(false) {
}

PlayerAttackComponent::~PlayerAttackComponent() = default;

void PlayerAttackComponent::start() {
    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
}

void PlayerAttackComponent::update() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (mAlreadyHeal) {
            break;
        }
        if (c->getOwner()->getTag() != "Enemy") {
            continue;
        }

        auto spComp = mPlayer->getComponentManager()->getComponent<SPComponent>();
        auto sp = spComp->sp();
        auto gauge = spComp->getCurrentGaugeCount();
        const int oneGauge = spComp->getOneGauge();
        if (sp > 0 && sp % oneGauge == 0) {
            return;
        } else {
            auto max = gauge * oneGauge + oneGauge;
            spComp->set(Math::Min<int>(max, sp + SP_HEAL_POINT));
        }

        mAlreadyHeal = true;
    }

    mTimer->update();
    if (mTimer->isTime()) {
        Actor::destroy(mOwner);
    }
}
