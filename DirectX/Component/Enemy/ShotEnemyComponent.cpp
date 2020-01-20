#include "ShotEnemyComponent.h"
#include "../ComponentManager.h"
#include "../../Actor/Actor.h"
#include "../../Actor/EnemyBullet.h"
#include "../../Actor/Transform2D.h"
#include "../../Device/Time.h"

ShotEnemyComponent::ShotEnemyComponent(Actor* owner) :
    Component(owner),
    mShotTimer(std::make_unique<Time>(2.f)),
    mEnemyBulletList(0) {
}

ShotEnemyComponent::~ShotEnemyComponent() = default;

void ShotEnemyComponent::start() {
    for (size_t i = 0; i < MAX_BULLET_COUNT; i++) {
        auto e = new EnemyBullet(mOwner->renderer());
        mEnemyBulletList.emplace_back(e);
        mOwner->transform()->addChild(e->transform());
    }
}

void ShotEnemyComponent::update() {
    mShotTimer->update();
    if (mShotTimer->isTime()) {
        mShotTimer->reset();
        shot();
    }
}

void ShotEnemyComponent::shot() {
    for (auto&& b : mEnemyBulletList) {
        if (b->isReady()) {
            b->shot();
            break;
        }
    }
}

const int ShotEnemyComponent::MAX_BULLET_COUNT = 5;
