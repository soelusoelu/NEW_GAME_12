#include "AnchorComponent.h"
#include "CircleCollisionComponent.h"
#include "Collider.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"
#include "../Utility/Input.h"

AnchorComponent::AnchorComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mSpriteComp(nullptr),
    mCollide(nullptr),
    MAX_LENGTH(300.f),
    ANCHOR_INCREASE(1600.f),
    mCurrentAnchorLength(0.f),
    mThick(2.f),
    mTargetPoint(Vector2::zero),
    mHitActor(nullptr),
    mHitAngle(0.f),
    mReleaseKey(KeyCode::Q),
    mReleaseJoy(JoyCode::RightButton),
    mState(AnchorState::STOP) {
}

AnchorComponent::~AnchorComponent() = default;

void AnchorComponent::start() {
    mSpriteComp = mOwner->componentManager()->getComponent<SpriteComponent>();
    mSpriteComp->setActive(false);
    mCollide = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
    mCollide->disabled();

    mOwner->transform()->setPivot(Vector2(-mOwner->transform()->getSize().x * 0.5f, 0.f));
    mOwner->transform()->setPrimary(5);
}

void AnchorComponent::update() {
    if (mState == AnchorState::STOP) {
        return;
    }
    rotate();
    extend();
    shrink();
    updateCollider();
    hit();
    changeState();
}

void AnchorComponent::shot(const Vector2 & direction) {
    mTargetPoint = worldPosition() + direction * MAX_LENGTH;
    mHitActor = nullptr;
    mCurrentAnchorLength = 0.f;
    mState = AnchorState::EXTEND;
    mSpriteComp->setActive(true);
    mCollide->enabled();
}

bool AnchorComponent::isHit() const {
    return mState == AnchorState::HIT;
}

bool AnchorComponent::canShot() const {
    return mState == AnchorState::STOP;
}

const float AnchorComponent::maxLength() const {
    return MAX_LENGTH;
}

float AnchorComponent::currentLength() const {
    return mCurrentAnchorLength;
}

void AnchorComponent::setCurrentLength(float length) {
    mCurrentAnchorLength = length;
    computeScale();
}

Actor* AnchorComponent::hitActor() const {
    return mHitActor;
}

float AnchorComponent::hitAngle() const {
    return mHitAngle;
}

void AnchorComponent::rotate() {
    if (mState != AnchorState::EXTEND || mState != AnchorState::HIT) {
        auto other = (isHit()) ? enemyPosition(): mTargetPoint;
        auto dir = other - worldPosition();
        auto rot = Math::toDegrees(Math::atan2(dir.y, dir.x));
        mOwner->transform()->setRotation(rot);
    }
}

void AnchorComponent::extend() {
    if (mState != AnchorState::EXTEND) {
        return;
    }
    mCurrentAnchorLength += ANCHOR_INCREASE * Time::deltaTime;
    computeScale();
}

void AnchorComponent::shrink() {
    if (mState != AnchorState::SHRINK) {
        return;
    }
    mCurrentAnchorLength -= ANCHOR_INCREASE * Time::deltaTime;
    computeScale();
}

void AnchorComponent::updateCollider() {
    if (mState != AnchorState::EXTEND) {
        return;
    }
    //アンカーの先端にだけ当たり判定
    auto dir = mTargetPoint - worldPosition();
    dir.normalize();
    auto pos = worldPosition();
    mCollide->set(worldPosition() + dir * mCurrentAnchorLength, 3.f);
}

void AnchorComponent::hit() {
    if (mState != AnchorState::EXTEND) {
        return;
    }
    for (auto&& hit : mCollide->onCollisionEnter()) {
        if (hit->getOwner()->tag() == "Enemy" || hit->getOwner()->tag() == "Pillar") {
            if (auto enemy = dynamic_cast<EnemyActor*>(hit->getOwner())) {
                if (enemy->isDead()) {
                    return;
                }
            }

            //ヒットしたエネミーの登録
            mHitActor = hit->getOwner();

            //プレイヤーとエネミーとの角度計算
            auto dir = enemyPosition() - worldPosition();
            mHitAngle = Math::toDegrees(Math::atan2(-dir.y, -dir.x));

            auto actor = mOwner->transform()->parent()->getOwner();
            if (actor) {
                auto player = dynamic_cast<PlayerActor*>(actor);
                player->rotateDirection();
            }

            mState = AnchorState::HIT;
            mCollide->disabled();
            break;
        }
    }
}

void AnchorComponent::changeState() {
    if (mState == AnchorState::EXTEND) {
        if (mCurrentAnchorLength >= MAX_LENGTH) {
            mState = AnchorState::SHRINK;
        }
    } else if (mState == AnchorState::HIT) {
        if (Input::getKeyDown(mReleaseKey) || Input::getJoyDown(mReleaseJoy)) {
            auto actor = mOwner->transform()->parent()->getOwner();
            if (actor) {
                auto player = dynamic_cast<PlayerActor*>(actor);
                player->anchorReleaseAcceleration();
            }
            mState = AnchorState::SHRINK;
        }
    } else if (mState == AnchorState::SHRINK) {
        if (mCurrentAnchorLength <= 0.f) {
            mState = AnchorState::STOP;
            mSpriteComp->setActive(false);
        }
    }
}

Vector2 AnchorComponent::worldPosition() const {
    return mOwner->transform()->getWorldPosition();
}

Vector2 AnchorComponent::enemyPosition() const {
    if (!mHitActor) {
        return Vector2::zero;
    }
    return mHitActor->transform()->getPosition();
}

void AnchorComponent::computeScale() {
    mOwner->transform()->setScale(Vector2(mCurrentAnchorLength, mThick));
}
