#pragma once

#include "UI.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class PlayerActor;
class Sprite;

class AnchorPoint : public UI {
public:
    AnchorPoint(std::shared_ptr<Renderer> renderer, std::shared_ptr<PlayerActor> player);
    ~AnchorPoint();
    virtual void updateUI() override;

private:
    bool lineIntersection(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, Vector2* intersect);

private:
    std::weak_ptr<PlayerActor> mPlayer;
    Sprite* mPoint;
    float mLength;
};

