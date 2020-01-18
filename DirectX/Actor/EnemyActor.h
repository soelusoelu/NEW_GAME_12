#pragma once

#include "Actor.h"
#include "EnemyFactory.h"
#include <memory>
#include <string>

class Renderer;
class CircleCollisionComponent;
class HitPointComponent;
class SpriteComponent;
class EnemyComponent;

class EnemyActor : public Actor {
public:
    EnemyActor(std::shared_ptr<Renderer> renderer, EnemyType type, const std::string& scale, const char* tag = "Enemy");
    ~EnemyActor();
    virtual void updateActor() override;

private:
    CircleCollisionComponent* mCollide;
    HitPointComponent* mHP;
    SpriteComponent* mSprite;
    EnemyComponent* mEnemy;
};

