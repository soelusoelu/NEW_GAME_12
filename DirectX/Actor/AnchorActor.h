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
    AnchorActor(std::shared_ptr<Renderer> renderer, std::shared_ptr<Transform2D> player, const char* tag = "Anchor");
    ~AnchorActor();
    virtual void updateActor() override;
    void initialize(const Vector2& direction);
    bool isHit() const;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
    AnchorComponent* mAnchor;
};

