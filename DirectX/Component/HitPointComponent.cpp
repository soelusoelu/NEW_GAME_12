#include "HitPointComponent.h"
#include "../Actor/Actor.h"
#include "../Utility/Math.h"

HitPointComponent::HitPointComponent(Actor* onwer, int hp) :
    Component(onwer),
    mHP(hp),
    mMaxHP(hp) {
}

HitPointComponent::~HitPointComponent() = default;

void HitPointComponent::start() {
}

void HitPointComponent::update() {
}

void HitPointComponent::takeDamage(int damage) {
    mHP -= damage;
    mHP = Math::Max<int>(mHP, 0);
}

void HitPointComponent::takeHeal(int heal) {
    mHP += heal;
    mHP = Math::Min<int>(mHP, mMaxHP);
}

void HitPointComponent::setHP(int hp, bool isChangeMax) {
    mHP = hp;
    if (isChangeMax) {
        mMaxHP = hp;
    } else {
        mHP = Math::Min<int>(mHP, mMaxHP);
    }
}

int HitPointComponent::hp() const {
    return mHP;
}

float HitPointComponent::hpRate() const {
    return static_cast<float>(mHP) / static_cast<float>(mMaxHP);
}
