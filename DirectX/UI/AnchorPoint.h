#pragma once

#include "UI.h"

class Renderer;
class PlayerActor;
class Sprite;

class AnchorPoint : public UI {
public:
    AnchorPoint(std::shared_ptr<Renderer> renderer, PlayerActor* player);
    ~AnchorPoint();
    virtual void updateUI() override;

private:
    PlayerActor* mPlayer;
    Sprite* mPoint;
};

