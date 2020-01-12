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
    if (mIsHit) { //ƒAƒ“ƒJ[‚ª“G‚ÉŽh‚³‚Á‚Ä‚½‚çŒü‚«‚Ì’²®
        auto dir = mHitEnemyCenter - playerCenter();
        auto rot = Math::toDegrees(Math::atan2(-dir.x, dir.y));
        mOwner->transform()->setRotation(rot);
    } else { //ƒAƒ“ƒJ[‚ª“G‚ÉŽh‚³‚Á‚Ä‚È‚¢‚È‚çˆê’¼ü‚ÉL‚Î‚·
        mCurrentAnchorLength += ANCHOR_INCREASE * Time::deltaTime;
        mOwner->transform()->setScale(Vector2(2.f, mCurrentAnchorLength), false);
    }
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
