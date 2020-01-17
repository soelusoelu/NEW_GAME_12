#pragma once

#include "Actor.h"
#include "Enemy.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class EnemyComponent;

class EnemyActor : public Actor {
public:
    EnemyActor(std::shared_ptr<Renderer> renderer, EnemyType type, const char* tag = "Enemy");
    ~EnemyActor();
    virtual void updateActor() override;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
    EnemyComponent* mEnemy;
};

