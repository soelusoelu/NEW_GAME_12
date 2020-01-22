#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AnchorActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SoundComponent.h"
#include "../Device/Time.h"
#include "../Map/Map.h"
#include "../System/Game.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mAnchor(new AnchorActor(mOwner->renderer())),
    mCollider(nullptr),
    mSound(nullptr),
    mAcceleration(Vector2(30.f, 0.f)),
    mAccelerationSpeed(160.f),
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
    mOwner->transform()->setPrimary(10);
    mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
    mSound = mOwner->componentManager()->getComponent<SoundComponent>();

    mOwner->transform()->addChild(mAnchor->transform());
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

int PlayerMoveComponent::getSpeedRate() const {
    auto value = getMoveDirection().length();
    //auto value = Math::Max<float>(Math::abs(mAcceleration.x), Math::abs(mAcceleration.y));
    constexpr float min = 5.f;
    constexpr float max = 10.f;
    if (value < min) {
        return 1;
    } else if (value >= min && value < max) {
        return 3;
    } else if (value >= max) {
        return 5;
    }
}

Vector2 PlayerMoveComponent::getMoveDirection() const {
    return mOwner->transform()->getPosition() - mPreviousPos;
}

void PlayerMoveComponent::addAcceleration(const Vector2& add) {
    mAcceleration += add;
}

void PlayerMoveComponent::anchorReleaseAcceleration() {
    mAcceleration = getMoveDirection() * 30.f;
}

Vector2 PlayerMoveComponent::getAnchorDirection() const {
    return Vector2::normalize(mAnchorDir);
}

bool PlayerMoveComponent::isHitAnchor() const {
    return mAnchor->isHit();
}

Actor* PlayerMoveComponent::hitActor() const {
    return mAnchor->hitActor();
}

const float PlayerMoveComponent::anchorMaxLength() const {
    return mAnchor->maxLength();
}

void PlayerMoveComponent::rotateDirection() {
    auto dir = getMoveDirection();
    auto enemyPos = mAnchor->hitActor()->transform()->getPosition();
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
    auto rate = Math::abs(mAcceleration.x) / 2.f;
    rate *= mRotateDirection;
    //auto rate = (Math::abs(mAcceleration.x) + Math::abs(mAcceleration.y)) / 3.f;
    mRotateCount += Time::deltaTime * rate;
    auto angle = (mAnchor->hitAngle() + mRotateCount);
    //angle *= mRotateDirection;

    mOwner->transform()->setPosition(
        mAnchor->hitActor()->transform()->getPosition() + Vector2(Math::cos(angle), Math::sin(angle)) * mAnchor->currentLength()
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
    mAcceleration.x = Math::abs(mAcceleration.x);
    mAcceleration.y = Math::abs(mAcceleration.y);
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
    auto t = mOwner->transform();
    t->setPosition(Vector2::clamp(
        t->getPosition(),
        Vector2::zero + mOwner->transform()->getSize(),
        Vector2((Map::width - 1) * Map::wallSize, (Map::height - 1) * Map::wallSize) - mOwner->transform()->getSize()
    ));
    if (isHitAnchor()) { //アンカーをクランプ
        float dis = Vector2::distance(mOwner->transform()->getPosition(), mAnchor->hitActor()->transform()->getPosition());
        mAnchor->setCurrentLength(dis);
    }

    //最大最小加速度
    auto range = (isHitAnchor()) ? mAnchorAccelerationRange : mAccelerationRange;
    mAcceleration.clamp(Vector2(-range, -range), Vector2(range, range));
}

void PlayerMoveComponent::hit() {
    for (auto&& c : mCollider->onCollisionEnter()) {
        if (c->getOwner()->tag() == "EnemyBullet") {
            //減速
            Vector2 d;
            constexpr float add = 3000.f;
            d.x = (getMoveDirection().x > 0.f) ? -add : add;
            d.y = (getMoveDirection().y > 0.f) ? -add : add;
            mAcceleration += d * Time::deltaTime;
        }
    }
}

void PlayerMoveComponent::dead() {
    if (Math::abs(mAcceleration.x) < mDestroyRange &&
        Math::abs(mAcceleration.y) < mDestroyRange) {
        Actor::destroy(mOwner);
    }
}
