#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class SpriteComponent;
class CircleCollisionComponent;

class AnchorComponent : public Component {
public:
    AnchorComponent(Actor* owner, Actor* player, const Vector2& anchorDirection);
    ~AnchorComponent();
    virtual void start() override;
    virtual void update() override;

private:
    //アンカーの動き
    void extend();
    //アンカーの当たり判定を毎フレーム更新
    void updateCollider();
    //当たり判定
    void hit();
    //アンカーが刺さったときの移動制限
    void hitClamp();
    //死ぬ条件
    void dead();
    //プレイヤーの中心座標の取得
    Vector2 playerCenter() const;

private:
    Actor* mPlayer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    std::shared_ptr<CircleCollisionComponent> mCollide;
    Vector2 mAnchorDirection;
    float mAnchorIncrease;
    float mCurrentAnchorLength;
    bool mIsHit;
    Vector2 mHitEnemyCenter;
    static const float MAX_LENGTH;
};
