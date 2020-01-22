#pragma once

#include "Component.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"
#include <memory>

enum class AnchorState {
    EXTEND,
    HIT,
    SHRINK,
    STOP
};

class Actor;
class SpriteComponent;
class CircleCollisionComponent;
class Transform2D;

class AnchorComponent : public Component {
public:
    AnchorComponent(Actor* owner, int updateOrder = 10);
    ~AnchorComponent();
    virtual void start() override;
    virtual void update() override;
    void shot(const Vector2& direction);
    bool isHit() const;
    bool canShot() const;
    const float maxLength() const;
    float currentLength() const;
    void setCurrentLength(float length);
    Actor* hitActor() const;
    float hitAngle() const;

private:
    //アンカーの動き
    void rotate();
    void extend();
    void shrink();
    //アンカーの当たり判定を毎フレーム更新
    void updateCollider();
    //当たり判定
    void hit();
    //死ぬ条件
    void changeState();
    //座標の取得
    Vector2 worldPosition() const;
    Vector2 enemyPosition() const;
    //アンカーの伸縮
    void computeScale();

private:
    std::shared_ptr<SpriteComponent> mSpriteComp;
    std::shared_ptr<CircleCollisionComponent> mCollide;
    const float MAX_LENGTH;
    const float ANCHOR_INCREASE;
    float mCurrentAnchorLength;
    float mThick;
    Vector2 mTargetPoint;
    Actor* mHitActor;
    float mHitAngle;
    KeyCode mReleaseKey;
    JoyCode mReleaseJoy;
    AnchorState mState;
};
