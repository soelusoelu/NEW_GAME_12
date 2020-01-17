#pragma once

#include "Component.h"
#include <memory>

class Actor;
class Renderer;
class Time;

class ShotEnemyComponent : public Component {
public:
    ShotEnemyComponent(std::shared_ptr<Renderer> renderer, Actor* owner);
    ~ShotEnemyComponent();
    virtual void start() override;
    virtual void update() override;

private:
    std::shared_ptr<Renderer> mRenderer;
    std::unique_ptr<Time> mShotTimer;
};

