#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <string>

class Actor;
class Sprite;

class SpriteComponent : public Component {
public:
    SpriteComponent(Actor* owner, const char* fileName, const Vector2& size, float z);
    ~SpriteComponent();
    virtual void update() override;
    Sprite* getSprite() const;

private:
    Sprite* mSprite;
};