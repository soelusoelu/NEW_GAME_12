#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AnchorActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Device/Time.h"
#include "../System/Game.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer, int updateOrder) :
    Component(owner, updateOrder),
    mAnchor(new AnchorActor(renderer)),
    mRenderer(renderer),
    mCollider(nullptr),
    mAcceleration(Vector2(30.f, 0.f)),
    mAccelerationSpeed(120.f),
    mAccelerationRange(400.f),
    mAnchorAccelerationTimes(5.f),
    mAnchorAccelerationRange(600.f),
    mDecelerationSpeed(30.f),
    mDestroyRange(3.f),
    mRotateCount(0.f),
    mRotateDirection(0.f),
    mPreviousPos(Vector2::zero),
    mAnchorKey(KeyCode::Q),
    mAnchorJoy(JoyCode::RightButton),
    mAnchorDir(Vector2::right) {
}

PlayerMoveComponent::~PlayerMoveComponent() = default;

void PlayerMoveComponent::start() {
    mOwner->transform()->setPosition(Vector2(100.f, 200.f));
    mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();

    mOwner->transform()->addChild(mAnchor->transform());
    mAnchor->transform()->setPivot(mAnchor->transform()->getPosition());
}

void PlayerMoveComponent::update() {
    move();
    deceleration();
    anchorUpdate();
    anchorInjection();
    clamp();
    hit();
    dead();
}

Vector2 PlayerMoveComponent::getMoveDirection() const {
    return mOwner->transform()->getPosition() - mPreviousPos;
}

void PlayerMoveComponent::anchorReleaseAcceleration() {
    mAcceleration = getMoveDirection() * 30.f;
}

Vector2 PlayerMoveComponent::getAnchorDirection() const {
    return mAnchorDir;
}

bool PlayerMoveComponent::isHitAnchor() const {
    return mAnchor->isHit();
}

const float PlayerMoveComponent::anchorMaxLength() const {
    return mAnchor->maxLength();
}

void PlayerMoveComponent::rotateDirection() {
    auto dir = getMoveDirection();
    auto enemyPos = mAnchor->hitEnemy()->transform()->getPosition();
    auto temp = enemyPos - mOwner->transform()->getPosition();
    if (temp.y > 0) {
        mRotateDirection = (dir.x > 0) ? 1.f : -1.f;
    } else {
        mRotateDirection = (dir.x > 0) ? -1.f : 1.f;
    }
}

void PlayerMoveComponent::move() {
    //1フレーム前の座標を記憶
    mPreviousPos = mOwner->transform()->getPosition();

    float h = Input::horizontal();
    float v = Input::vertical();
    if (Math::nearZero(h) && Math::nearZero(v)) {
        h = Input::joyHorizontal();
        v = Input::joyVertical();
    }
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        auto fh = h * mAccelerationSpeed * Time::deltaTime;
        auto fv = v * mAccelerationSpeed * Time::deltaTime;

        auto a = Vector2(fh, -fv);
        mAcceleration += (isHitAnchor()) ? a * mAnchorAccelerationTimes : a;
    }

    //現在の加速度で移動
    if (isHitAnchor()) {
        rotate();
    } else {
        mOwner->transform()->translate(mAcceleration * Time::deltaTime);
    }
}

void PlayerMoveComponent::rotate() {
    auto rate = (Math::abs(mAcceleration.x) + Math::abs(mAcceleration.y)) / 2.f;
    mRotateCount += Time::deltaTime * rate;
    auto angle = (mAnchor->hitAngle() + mRotateCount);
    angle *= mRotateDirection;
    mOwner->transform()->setPosition(
        mAnchor->hitEnemy()->transform()->getPosition() + Vector2(Math::cos(angle), Math::sin(angle)) * mAnchor->currentLength()
    );
}

void PlayerMoveComponent::deceleration() {
    if (isHitAnchor()) {
        return;
    }
    Vector2 d;
    d.x = (mAcceleration.x > 0.f) ? -mDecelerationSpeed : mDecelerationSpeed;
    d.y = (mAcceleration.y > 0.f) ? -mDecelerationSpeed : mDecelerationSpeed;
    mAcceleration += d * Time::deltaTime;
}

void PlayerMoveComponent::anchorInjection() {
    if ((!Input::getKeyDown(mAnchorKey) && !Input::getJoyDown(mAnchorJoy)) || !mAnchor->canShot()) {
        return;
    }
    mAnchor->shot(Vector2::normalize(mAnchorDir));
    mRotateCount = 0.f;
}

void PlayerMoveComponent::anchorUpdate() {
    //アンカーを指す位置
    auto h = Input::joyRhorizontal();
    auto v = Input::joyRvertical();
    if (!Math::nearZero(h) || !Math::nearZero(v)) {
        if (Math::abs(h) < 0.5f && Math::abs(v) < 0.5f) {
            return;
        }
        mAnchorDir.set(h, -v);
    }
}

void PlayerMoveComponent::clamp() {
    //auto t = mOwner->transform();
    //t->setPosition(Vector2::clamp(
    //    t->getPosition(),
    //    Vector2::zero,
    //    Vector2(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT) - Vector2(mSpriteComp->getScreenTextureSize().x, mSpriteComp->getScreenTextureSize().y)
    //));

    //最大最小加速度
    auto range = (isHitAnchor()) ? mAnchorAccelerationRange : mAccelerationRange;
    mAcceleration.clamp(Vector2(-range, -range), Vector2(range, range));
}

void PlayerMoveComponent::hit() {
    for (auto&& c : mCollider->onCollisionEnter()) {
        if (c->getOwner()->tag() == "EnemyBullet") {
            //減速
            Vector2 d;
            d.x = (mAcceleration.x > 0.f) ? -300.f : 300.f;
            d.y = (mAcceleration.y > 0.f) ? -300.f : 300.f;
            mAcceleration += d * Time::deltaTime;
        }
    }
}

void PlayerMoveComponent::dead() {
    if (Math::abs(mAcceleration.x) < mDestroyRange &&
        Math::abs(mAcceleration.y) < mDestroyRange) {
        //Actor::destroy(mOwner);
    }
}
