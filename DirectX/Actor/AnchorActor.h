#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class AnchorComponent;

class AnchorActor : public Actor {
public:
    AnchorActor(std::shared_ptr<Renderer> renderer, const char* tag = "Anchor");
    ~AnchorActor();
    virtual void updateActor() override;
    void shot(const Vector2& direction);
    bool isHit() const;
    bool canShot() const;
    const float maxLength() const;
    float currentLength() const;
    Actor* hitEnemy() const;
    float hitAngle() const;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
    AnchorComponent* mAnchor;
};

