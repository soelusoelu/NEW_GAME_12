#include "TackleEnemyComponent.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/ActorManager.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"

TackleEnemyComponent::TackleEnemyComponent(Actor* owner) :
    Component(owner),
    mPlayer(),
    mThinkTimer(std::make_unique<Time>(3.f)),
    mTackleTimer(std::make_unique<Time>(3.f)),
    mPreviousPos(Vector2::zero),
    mToPlayer(Vector2::zero),
    mState(TackleState::THINK) {
}

TackleEnemyComponent::~TackleEnemyComponent() = default;

void TackleEnemyComponent::start() {
    mPlayer = mOwner->getActorManager()->getPlayer();
    mSprite = mOwner->componentManager()->getComponent<SpriteComponent>();
}

void TackleEnemyComponent::update() {
    mPreviousPos = mOwner->transform()->getPosition();

    if (mState == TackleState::THINK) {
        mThinkTimer->update();
        if (mThinkTimer->isTime()) {
            mThinkTimer->reset();
            toPlayer();
            mState = TackleState::TACKLE;
        }
    } else if (mState == TackleState::TACKLE) {
        tackle();
    }
    changeColor();
}

Vector2 TackleEnemyComponent::moveDirection() const {
    return mOwner->transform()->getPosition() - mPreviousPos;
}

void TackleEnemyComponent::tackle() {
    mOwner->transform()->translate(mToPlayer * TACKLE_SPEED * Time::deltaTime);

    mTackleTimer->update();
    if (mTackleTimer->isTime()) {
        mTackleTimer->reset();
        mState = TackleState::THINK;
    }
}

void TackleEnemyComponent::toPlayer() {
    if (auto p = mPlayer.lock()) {
        mToPlayer = p->transform()->getPosition() - mOwner->transform()->getPosition();
        mToPlayer.normalize();
    }
}

void TackleEnemyComponent::changeColor() {
    if (mState == TackleState::THINK) {
        mSprite->setColor(mThinkTimer->currentTime() / mThinkTimer->limitTime(), 0.f, 0.f);
    } else if (mState == TackleState::TACKLE) {
        mSprite->setColor(1 - mTackleTimer->currentTime() / mTackleTimer->limitTime(), 0.f, 0.f);
    }
}

const float TackleEnemyComponent::TACKLE_SPEED = 1200.f;
