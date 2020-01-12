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

AnchorComponent::AnchorComponent(Actor* owner, Actor* player, const Vector2& anchorDirection, int updateOrder) :
    Component(owner, updateOrder),
    mPlayer(player),
    mSpriteComp(nullptr),
    mCollide(nullptr),
    mAnchorDirection(anchorDirection),
    mAnchorIncrease(1200.f),
    mCurrentAnchorLength(0.f),
    mIsHit(false),
    mHitEnemy(nullptr),
    mHitEnemyCenter(Vector2::zero) {
    mOwner->transform()->setRotation(Math::toDegrees(Math::atan2(-mAnchorDirection.x, -mAnchorDirection.y)));
}

AnchorComponent::~AnchorComponent() = default;

void AnchorComponent::start() {
    mSpriteComp = mOwner->componentManager()->getComponent<SpriteComponent>();
    mCollide = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
}

void AnchorComponent::update() {
    extend();
    updateCollider();
    hit();
    hitClamp();
    dead();
}

void AnchorComponent::extend() {
    if (mIsHit) { //ƒAƒ“ƒJ[‚ª“G‚ÉŽh‚³‚Á‚Ä‚½‚çŒü‚«‚Ì’²®
        auto dir = mHitEnemyCenter - playerCenter();
        auto rot = Math::toDegrees(Math::atan2(-dir.x, dir.y));
        mOwner->transform()->setRotation(rot);
    } else { //ƒAƒ“ƒJ[‚ª“G‚ÉŽh‚³‚Á‚Ä‚È‚¢‚È‚çˆê’¼ü‚ÉL‚Î‚·
        mCurrentAnchorLength += mAnchorIncrease * Time::deltaTime;
        mOwner->transform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);
    }
    mOwner->transform()->setPosition(playerCenter());
}

void AnchorComponent::updateCollider() {
    if (mIsHit) {
        return;
    }
    //ƒAƒ“ƒJ[‚Ìæ’[‚É‚¾‚¯“–‚½‚è”»’è
    mCollide->set(mOwner->transform()->getPosition() + mAnchorDirection * mCurrentAnchorLength, 3.f);
}

void AnchorComponent::hit() {
    if (mIsHit) {
        if (!mHitEnemy) {
            return;
        }
        auto dot = Vector2::cross(playerCenter(), mHitEnemyCenter);
        return;
    }
    auto hits = mCollide->onCollisionEnter();
    for (auto&& hit : hits) {
        if (hit->getOwner()->tag() == "Enemy") {
            mHitEnemy = hit->getOwner();
            auto enemyTrans = hit->getOwner()->transform();
            mHitEnemyCenter = enemyTrans->getPosition() + enemyTrans->getPivot();

            //ƒAƒ“ƒJ[‚Ì’·‚³‚ðŒÅ’è
            mCurrentAnchorLength = Vector2::distance(mHitEnemyCenter, playerCenter());
            mOwner->transform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);

            mIsHit = true;
            mCollide->disabled();
            mPlayer->componentManager()->getComponent<PlayerMoveComponent>()->setDecelerate(false);
            break;
        }
    }
}

void AnchorComponent::hitClamp() {
    if (!mIsHit) {
        return;
    }
    //‰~‚ð•`‚­‚½‚ß‚É–³—‚â‚è
    auto dis = Vector2::distance(mHitEnemyCenter, playerCenter());
    auto dir = mHitEnemyCenter - playerCenter();
    dir.normalize();
    mPlayer->transform()->translate(dir * (dis - mCurrentAnchorLength));
}

void AnchorComponent::dead() {
    auto flag = false;
    if (mIsHit) {
        if (Input::getKeyDown(KeyCode::W)) {
            flag = true;
        }
    } else {
        if (mCurrentAnchorLength >= MAX_LENGTH) {
            flag = true;
        }
    }

    if (flag) {
        Actor::destroy(mOwner);
        mPlayer->componentManager()->getComponent<PlayerMoveComponent>()->setDecelerate(true);
    }
}

Vector2 AnchorComponent::playerCenter() const {
    auto playerTrans = mPlayer->transform();
    return playerTrans->getPosition() + playerTrans->getPivot();
}

const float AnchorComponent::MAX_LENGTH = 400.f;
