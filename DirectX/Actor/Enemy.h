#pragma once

#include "Actor.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class EnemyComponent;

class Enemy : public Actor {
public:
    Enemy(std::shared_ptr<Renderer>renderer, const char* tag = "Enemy");
    ~Enemy();
    virtual void updateActor() override;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
    EnemyComponent* mEnemy;
};