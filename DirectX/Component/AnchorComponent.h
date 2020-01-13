﻿#pragma once

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
    AnchorComponent(Actor* owner, std::shared_ptr<Transform2D> player, int updateOrder = 10);
    ~AnchorComponent();
    virtual void start() override;
    virtual void update() override;
    void shot(const Vector2& direction);
    bool isHit() const;
    bool canShot() const;

private:
    //アンカーの動き
    void rotate();
    void extend();
    void shrink();
    //アンカーの当たり判定を毎フレーム更新
    void updateCollider();
    //当たり判定
    void hit();
    //アンカーが刺さったときの移動制限
    void hitClamp();
    //死ぬ条件
    void changeState();
    //プレイヤーの中心座標の取得
    Vector2 playerCenter() const;

private:
    std::shared_ptr<Transform2D> mPlayer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    std::shared_ptr<CircleCollisionComponent> mCollide;
    const float MAX_LENGTH;
    const float ANCHOR_INCREASE;
    float mCurrentAnchorLength;
    Vector2 mTargetPoint;
    Actor* mHitEnemy;
    Vector2 mHitEnemyCenter;
    KeyCode mReleaseKey;
    AnchorState mState;
};
