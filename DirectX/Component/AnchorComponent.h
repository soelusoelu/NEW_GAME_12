#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class SpriteComponent;
class Collider;

class AnchorComponent : public Component {
public:
    AnchorComponent(Actor* owner, Actor* player, const Vector2& anchorDirection);
    ~AnchorComponent();
    virtual void start() override;
    virtual void update() override;

private:
    Actor* mPlayer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    std::shared_ptr<Collider> mCollide;
    float mCurrentAnchorLength;
    static const float MAX_LENGTH;
};
