#pragma once

#include "Component.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class AnchorActor;
class Renderer;
class SpriteComponent;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer, int updateOrder = 10);
    ~PlayerMoveComponent();
    virtual void start() override;
    virtual void update() override;
    Vector2 getAcceleration() const;
    void anchorReleaseAcceleration();
    Vector2 getLastInput() const;
    bool isHitAnchor() const;
    const float anchorMaxLength() const;
    void rotateDirection();

private:
    void move();
    void rotate();
    void deceleration();
    void anchorInjection();
    void anchorUpdate();
    void clamp();
    void dead();
    Vector2 centerPosition() const;
    Vector2 moveDirection() const;

private:
    AnchorActor* mAnchor;
    std::shared_ptr<Renderer> mRenderer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    Vector2 mAcceleration; //現加速度
    float mAccelerationSpeed; //追加速度
    float mAccelerationRange; //加速度範囲
    float mAnchorAccelerationTimes; //アンカー時速度倍率
    float mAnchorAccelerationRange; //アンカー時加速度範囲
    float mDecelerationSpeed; //減速度
    float mDestroyRange; //死亡範囲
    float mRotateCount;
    float mRotateDirection;
    Vector2 mPreviousPos;
    KeyCode mAnchorKey;
    JoyCode mAnchorJoy;
    Vector2 mLastInput;
};

