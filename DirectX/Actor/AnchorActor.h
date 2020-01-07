#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;

class AnchorActor : public Actor {
public:
    AnchorActor(
        std::shared_ptr<Renderer> renderer,
        const Vector2& playerCenterPosition,
        const Vector2& anchorDirection,
        float length,
        const char* tag = "Anchor"
    );
    ~AnchorActor();
    virtual void updateActor() override;

private:
    CircleCollisionComponent* mCollide;
    SpriteComponent* mSprite;
};

