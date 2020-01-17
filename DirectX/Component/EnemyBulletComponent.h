#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class CircleCollisionComponent;
class PlayerActor;

class EnemyBulletComponent : public Component {
public:
    EnemyBulletComponent(Actor* owner);
    ~EnemyBulletComponent();
    virtual void start() override;
    virtual void update() override;

private:
    std::weak_ptr<PlayerActor> mPlayer;
    std::shared_ptr<CircleCollisionComponent> mCollider;
    float mBulletSpeed;
    Vector2 mBulletDir;
};

