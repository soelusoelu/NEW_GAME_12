#include "ShotEnemyComponent.h"
#include "ComponentManager.h"
#include "../Actor/Actor.h"
#include "../Actor/EnemyBullet.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"

ShotEnemyComponent::ShotEnemyComponent(std::shared_ptr<Renderer> renderer, Actor* owner) :
    Component(owner),
    mRenderer(renderer),
    mShotTimer(std::make_unique<Time>(2.f)) {
}

ShotEnemyComponent::~ShotEnemyComponent() = default;

void ShotEnemyComponent::start() {
}

void ShotEnemyComponent::update() {
    mShotTimer->update();
    if (mShotTimer->isTime()) {
        mShotTimer->reset();
        auto e = new EnemyBullet(mRenderer);
        mOwner->transform()->addChild(e->transform());
    }
}
