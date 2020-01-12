#include "AnchorComponent.h"
#include "CircleCollisionComponent.h"
#include "Collider.h"
#include "ComponentManager.h"
#include "PlayerMoveComponent.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"
#include "../Utility/Input.h"

AnchorComponent::AnchorComponent(Actor* owner, std::shared_ptr<Transform2D> player, int updateOrder) :
    Component(owner, updateOrder),
    mPlayer(player),
    mSpriteComp(nullptr),
    mCollide(nullptr),
    mAnchorDirection(Vector2::right),
    MAX_LENGTH(400.f),
    ANCHOR_INCREASE(1200.f),
    mCurrentAnchorLength(0.f),
    mIsHit(false),
    mHitEnemy(nullptr),
    mHitEnemyCenter(Vector2::zero),
    mIsUpdate(false) {
}

AnchorComponent::~AnchorComponent() = default;

void AnchorComponent::start() {
    mSpriteComp = mOwner->componentManager()->getComponent<SpriteComponent>();
    mCollide = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
}

void AnchorComponent::update() {
    if (!mIsUpdate) {
        return;
    }
    extend();
    updateCollider();
    hit();
    hitClamp();
    dead();
}

void AnchorComponent::initialize(const Vector2 & direction) {
    mAnchorDirection = direction;
    mOwner->transform()->setRotation(Math::toDegrees(Math::atan2(-mAnchorDirection.x, mAnchorDirection.y)));
    mIsHit = false;
    mHitEnemy = nullptr;
    mCurrentAnchorLength = 0.f;
    mIsUpdate = true;
}

bool AnchorComponent::isHit() const {
    return mIsHit;
}

void AnchorComponent::extend() {
    if (mIsHit) { //アンカーが敵に刺さってたら向きの調整
        auto dir = mHitEnemyCenter - playerCenter();
        auto rot = Math::toDegrees(Math::atan2(-dir.x, dir.y));
        mOwner->transform()->setRotation(rot);
    } else { //アンカーが敵に刺さってないなら一直線に伸ばす
        mCurrentAnchorLength += ANCHOR_INCREASE * Time::deltaTime;
        mOwner->transform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);
    }
}

void AnchorComponent::updateCollider() {
    if (mIsHit) {
        return;
    }
    //アンカーの先端にだけ当たり判定
    mCollide->set(mOwner->transform()->getPosition() + mAnchorDirection * mCurrentAnchorLength, 3.f);
}

void AnchorComponent::hit() {
    if (mIsHit) {
        return;
    }
    auto hits = mCollide->onCollisionEnter();
    for (auto&& hit : hits) {
        if (hit->getOwner()->tag() == "Enemy") {
            mHitEnemy = hit->getOwner();
            auto enemyTrans = hit->getOwner()->transform();
            mHitEnemyCenter = enemyTrans->getPosition() + enemyTrans->getPivot();

            //アンカーの長さを固定
            mCurrentAnchorLength = Vector2::distance(mHitEnemyCenter, playerCenter());
            mOwner->transform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);

            mIsHit = true;
            mCollide->disabled();
            break;
        }
    }
}

void AnchorComponent::hitClamp() {
    if (!mIsHit) {
        return;
    }
    //円を描くために無理やり
    auto dis = Vector2::distance(mHitEnemyCenter, playerCenter());
    auto dir = mHitEnemyCenter - playerCenter();
    dir.normalize();
    mPlayer->translate(dir * (dis - mCurrentAnchorLength));
}

void AnchorComponent::dead() {
    auto dead = false;
    if (mIsHit) {
        if (Input::getKeyDown(KeyCode::E)) {
            dead = true;
        }
    } else {
        if (mCurrentAnchorLength >= MAX_LENGTH) {
            dead = true;
        }
    }

    if (dead) {
        mIsUpdate = false;
    }
}

Vector2 AnchorComponent::playerCenter() const {
    return mPlayer->getPosition() + mPlayer->getPivot();
}
