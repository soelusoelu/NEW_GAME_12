#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SoundComponent;
class SpriteComponent;
class PlayerMoveComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(std::shared_ptr<Renderer> renderer, const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    void anchorReleaseAcceleration();
    Vector2 getAnchorDirection() const;
    bool isHitAnchor() const;
    const float anchorMaxLength() const;
    void rotateDirection();

private:
    CircleCollisionComponent* mCollide;
    SoundComponent* mSound;
    SpriteComponent* mSprite;
    PlayerMoveComponent* mMove;
};

