#include "AnchorComponent.h"
#include "CircleCollisionComponent.h"
#include "Collider.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
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
    mHitEnemy(nullptr),
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
    mTargetPoint = playerPosition() + direction * MAX_LENGTH;
    mHitEnemy = nullptr;
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

Actor* AnchorComponent::hitEnemy() const {
    return mHitEnemy;
}

float AnchorComponent::hitAngle() const {
    return mHitAngle;
}

void AnchorComponent::rotate() {
    if (mState != AnchorState::EXTEND || mState != AnchorState::HIT) {
        auto other = (isHit()) ? enemyCenterPosition(): mTargetPoint;
        auto dir = other - playerPosition();
        auto rot = Math::toDegrees(Math::atan2(-dir.x, dir.y));
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
    auto dir = mTargetPoint - playerPosition();
    dir.normalize(); //重いねぇ
    mCollide->set(playerPosition() + dir * mCurrentAnchorLength, 3.f);
}

void AnchorComponent::hit() {
    if (mState != AnchorState::EXTEND) {
        return;
    }
    for (auto&& hit : mCollide->onCollisionEnter()) {
        if (hit->getOwner()->tag() == "Enemy") {
            //ヒットしたエネミーの登録
            mHitEnemy = hit->getOwner();

            //プレイヤーとエネミーとの角度計算
            auto dir = enemyCenterPosition() - playerPosition();
            mHitAngle = Math::toDegrees(Math::atan2(-dir.y, -dir.x));

            auto player = dynamic_cast<PlayerActor*>(mOwner->transform()->parent()->getOwner());
            if (player) {
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
            auto player = dynamic_cast<PlayerActor*>(mOwner->transform()->parent()->getOwner());
            if (player) {
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

Vector2 AnchorComponent::playerPosition() const {
    return mOwner->transform()->parent()->getCenter();
}

Vector2 AnchorComponent::enemyCenterPosition() const {
    if (!mHitEnemy) {
        return Vector2::zero;
    }
    return mHitEnemy->transform()->getCenter();
}

void AnchorComponent::computeScale() {
    mOwner->transform()->setScale(Vector2(mThick, mCurrentAnchorLength), false);
}
