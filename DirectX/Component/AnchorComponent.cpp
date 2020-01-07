#include "AnchorComponent.h"
#include "CircleCollisionComponent.h"
#include "Collider.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"
#include "../Utility/Input.h"

AnchorComponent::AnchorComponent(Actor* owner, Actor* player, const Vector2& anchorDirection) :
    Component(owner),
    mPlayer(player),
    mSpriteComp(nullptr),
    mCollide(nullptr),
    mAnchorDirection(anchorDirection),
    mAnchorIncrease(600.f),
    mCurrentAnchorLength(0.f),
    mIsHit(false),
    mHitEnemyCenter(Vector2::zero) {
    mOwner->getTransform()->setRotation(Math::toDegrees(Math::atan2(-mAnchorDirection.x, -mAnchorDirection.y)));
}

AnchorComponent::~AnchorComponent() = default;

void AnchorComponent::start() {
    mSpriteComp = mOwner->getComponentManager()->getComponent<SpriteComponent>();
    mCollide = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
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
        mOwner->getTransform()->setRotation(Math::toDegrees(Math::atan2(-dir.x, dir.y)));
    } else { //ƒAƒ“ƒJ[‚ª“G‚ÉŽh‚³‚Á‚Ä‚È‚¢‚È‚çˆê’¼ü‚ÉL‚Î‚·
        mCurrentAnchorLength += mAnchorIncrease * Time::deltaTime;
        mOwner->getTransform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);
    }
    mOwner->getTransform()->setPosition(playerCenter());
}

void AnchorComponent::updateCollider() {
    if (mIsHit) {
        return;
    }
    //ƒAƒ“ƒJ[‚Ìæ’[‚É‚¾‚¯“–‚½‚è”»’è
    mCollide->set(mOwner->getTransform()->getPosition() + mAnchorDirection * mCurrentAnchorLength, 3.f);
}

void AnchorComponent::hit() {
    if (mIsHit) {
        return;
    }
    auto hits = mCollide->onCollisionEnter();
    for (auto&& hit : hits) {
        if (hit->getOwner()->getTag() == "Enemy") {
            auto enemyTrans = hit->getOwner()->getTransform();
            mHitEnemyCenter = enemyTrans->getPosition() + enemyTrans->getPivot();

            //ƒAƒ“ƒJ[‚Ì’·‚³‚ðŒÅ’è
            mCurrentAnchorLength = Vector2::distance(mHitEnemyCenter, playerCenter());
            mOwner->getTransform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);

            mIsHit = true;
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
    mPlayer->getTransform()->translate(dir * (dis - mCurrentAnchorLength));
}

void AnchorComponent::dead() {
    if (mIsHit) {
        if (Input::getKeyDown(KeyCode::Q)) {
            Actor::destroy(mOwner);
        }
    }
    if (mCurrentAnchorLength >= MAX_LENGTH) {
        Actor::destroy(mOwner);
    }
}

Vector2 AnchorComponent::playerCenter() const {
    auto playerTrans = mPlayer->getTransform();
    return playerTrans->getPosition() + playerTrans->getPivot();
}

const float AnchorComponent::MAX_LENGTH = 400.f;
