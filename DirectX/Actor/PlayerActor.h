#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class PlayerMoveComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(std::shared_ptr<Renderer> renderer, const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    Vector2 getLastInput() const;
    bool isHitAnchor() const;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
    PlayerMoveComponent* mMove;
};

