#include "HitPointComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Utility/Math.h"

HitPointComponent::HitPointComponent(Actor* onwer, int hp) :
    Component(onwer),
    mHP(hp),
    MAX_HP(hp) {
}

HitPointComponent::~HitPointComponent() = default;

void HitPointComponent::update() {
}

void HitPointComponent::takeDamage(int damage) {
    mHP -= damage;
    mHP = Math::Max<int>(mHP, 0);
}

void HitPointComponent::takeHeal(int heal) {
    mHP += heal;
    mHP = Math::Min<int>(mHP, MAX_HP);
}

int HitPointComponent::hp() const {
    return mHP;
}

float HitPointComponent::hpRate() const {
    return static_cast<float>(mHP) / static_cast<float>(MAX_HP);
}
