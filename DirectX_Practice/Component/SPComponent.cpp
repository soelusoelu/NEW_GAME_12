#include "SPComponent.h"
#include "../Utility/Math.h"

SPComponent::SPComponent(Actor* onwer) :
    Component(onwer),
    mSP(0),
    mCurrentGaugeCount(0),
    ONE_GAUGE(100),
    MAX_GAUGE_COUNT(3),
    MAX_SP(ONE_GAUGE * MAX_GAUGE_COUNT) {
}

SPComponent::~SPComponent() = default;

void SPComponent::update() {
    mCurrentGaugeCount = mSP / ONE_GAUGE;
}

void SPComponent::set(int sp) {
    mSP = sp;
}

bool SPComponent::use(int sp) {
    mSP -= sp;
    mSP = Math::Max(mSP, 0);
    return true;
}

void SPComponent::heal(int sp) {
    mSP += sp;
    mSP = Math::Min<int>(mSP, MAX_SP);
}

int SPComponent::sp() const {
    return mSP;
}

const int SPComponent::maxSP() const {
    return MAX_SP;
}

const int SPComponent::getOneGauge() const {
    return ONE_GAUGE;
}

int SPComponent::getCurrentGaugeCount() const {
    return mCurrentGaugeCount;
}

int SPComponent::getMaxGaugeCount() const {
    return MAX_GAUGE_COUNT;
}

int SPComponent::computeGaugeCount(int sp) {
    sp = Math::Max(sp, 0);
    return sp / ONE_GAUGE;
}

float SPComponent::spRate() const {
    return static_cast<float>(mSP) / static_cast<float>(ONE_GAUGE);
}
