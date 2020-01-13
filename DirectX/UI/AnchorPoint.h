#pragma once

#include "UI.h"
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
    std::weak_ptr<PlayerActor> mPlayer;
    Sprite* mPoint;
};

