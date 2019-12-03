#include "AvoidanceComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Sound.h"
#include "../Device/Time.h"

AvoidanceComponent::AvoidanceComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mCircle(nullptr),
    mDestroyTimer(std::make_unique<Time>(0.1f)),
    mPlayer(player),
    SP_HEAL_POINT(15),
    mAlreadyHeal(false) {
}

AvoidanceComponent::~AvoidanceComponent() = default;

void AvoidanceComponent::start() {
    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
}

void AvoidanceComponent::update() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() == "EnemyBullet") {
            AvoidancePlayerActor::mSuccessedAvoidance = true;
            AvoidancePlayerActor::mSlowTimer->reset();

            if (mAlreadyHeal) {
                break;
            }
            auto spComp = mPlayer->getComponentManager()->getComponent<SPComponent>();
            auto sp = spComp->sp();

            int gauge = sp / spComp->getOneGauge();
            int currentMaxSP = gauge * spComp->getOneGauge() + spComp->getOneGauge();

            spComp->heal(SP_HEAL_POINT);
            if (spComp->sp() > currentMaxSP) {
                spComp->set(currentMaxSP);
            }
            mAlreadyHeal = true;

            Sound::play("heartbeats.wav");
        }
    }

    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(mOwner);
    }
}
