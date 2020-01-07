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
    AnchorActor(
        std::shared_ptr<Renderer> renderer,
        Actor* player,
        const Vector2& anchorDirection,
        const char* tag = "Anchor"
    );
    ~AnchorActor();
    virtual void updateActor() override;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
    AnchorComponent* mAnchor;
};

