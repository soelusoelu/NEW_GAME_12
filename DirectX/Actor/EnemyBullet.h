#pragma once

#include "Actor.h"

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class EnemyBulletComponent;

class EnemyBullet : public Actor {
public:
    EnemyBullet(std::shared_ptr<Renderer> renderer, const char* tag = "EnemyBullet");
    ~EnemyBullet();
    virtual void updateActor() override;

private:
    CircleCollisionComponent* mCircle;
    SpriteComponent* mSprite;
    EnemyBulletComponent* mBullet;
};
