#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

enum class PlayerState {
    OnGround,
    Jump
};

enum class Direction {
    Right = 0,
    Left = 1
};

class Actor;
class AnimationComponent;
class CircleCollisionComponent;
class HitPointComponent;
class SPComponent;
class Sprite;
class Time;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, int updateOrder = 10);
    ~PlayerMoveComponent();
    virtual void start() override;
    virtual void update() override;

private:
    void move();
    void jump();
    void jumpUpdate();
    void fall();
    void avoidance();
    void avoidanceUpdate();
    void posClamp();
    void canAttack();
    void attack();
    void specialAttack();
    void hit();
    void dead();

private:
    Sprite* mSprite;
    std::shared_ptr< AnimationComponent> mAnim;
    std::shared_ptr<CircleCollisionComponent> mCircle;
    std::shared_ptr<HitPointComponent> mHP;
    std::shared_ptr<SPComponent> mSP;
    const float MOVE_SPEED;
    const float FALL_SPEED;
    float mCurrentJumpPower;
    float mX; //ジャンプ二次関数用
    const int AVOIDANCE_LENGTH;
    std::unique_ptr<Time> mAttackTimer;
    bool mCanAttack;
    PlayerState mState;
    Direction mDir;
    bool mRunningAvoidance;
    Vector2 mAfterPosition;
    Vector2 mNormalDir;
};
