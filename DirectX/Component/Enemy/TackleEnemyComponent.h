#pragma once

#include "../Component.h"
#include "../../Utility/Math.h"
#include <memory>

enum class TackleState {
    THINK,
    TACKLE
};

class Actor;
class PlayerActor;
class Renderer;
class Time;
class CircleCollisionComponent;
class SpriteComponent;

class TackleEnemyComponent : public Component {
public:
    TackleEnemyComponent(Actor* owner);
    ~TackleEnemyComponent();
    virtual void start() override;
    virtual void update() override;
    Vector2 moveDirection() const;

private:
    void tackle();
    void toPlayer();
    void changeColor();
    void hit();

private:
    std::weak_ptr<PlayerActor> mPlayer;
    std::shared_ptr<CircleCollisionComponent> mCollider;
    std::shared_ptr<SpriteComponent> mSprite;
    std::unique_ptr<Time> mThinkTimer;
    std::unique_ptr<Time> mTackleTimer;
    Vector2 mPreviousPos;
    Vector2 mToPlayer;
    TackleState mState;
    static const float TACKLE_SPEED;
};

