#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

enum class BulletState {
    READY,
    UPDATING,
};

class Actor;
class CircleCollisionComponent;
class SpriteComponent;
class Time;

class EnemyBulletComponent : public Component {
public:
    EnemyBulletComponent(Actor* owner);
    ~EnemyBulletComponent();
    virtual void start() override;
    virtual void update() override;
    void shot();
    bool isReady() const;

private:
    void end();

private:
    std::shared_ptr<CircleCollisionComponent> mCollider;
    std::shared_ptr<SpriteComponent> mSprite;
    std::unique_ptr<Time> mEndTimer;
    static const float BULLET_SPEED;
    Vector2 mBulletDir;
    BulletState mState;
};

