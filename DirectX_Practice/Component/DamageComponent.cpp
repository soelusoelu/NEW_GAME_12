#include "DamageComponent.h"

DamageComponent::DamageComponent(Actor* onwer, int damage) :
    Component(onwer),
    mDamage(damage) {
}

DamageComponent::~DamageComponent() = default;

void DamageComponent::update() {
}

int DamageComponent::damage() const {
    return mDamage;
}

void DamageComponent::setDamage(int set) {
    mDamage = set;
}

void DamageComponent::setDamageOfPlayerAttack(int spGauge) {
    static const int damage[] = {
        100, 120, 135
    };
    mDamage = damage[spGauge];
}

void DamageComponent::setDamageOfPlayerSpecialAttack(int spGauge) {
    static const int damage[] = {
        0, 100, 150, 200 //ç≈èâÇÃ0ÇÕÉ_É~Å[
    };
    mDamage = damage[spGauge];
}
