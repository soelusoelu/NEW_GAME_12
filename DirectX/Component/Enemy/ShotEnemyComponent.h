#pragma once

#include "../Component.h"
#include <memory>
#include <list>

class Actor;
class Renderer;
class Time;
class EnemyBullet;

class ShotEnemyComponent : public Component {
public:
    ShotEnemyComponent(Actor* owner, std::shared_ptr<Renderer> renderer);
    ~ShotEnemyComponent();
    virtual void start() override;
    virtual void update() override;

private:
    void shot();

private:
    std::shared_ptr<Renderer> mRenderer;
    std::unique_ptr<Time> mShotTimer;
    std::list<EnemyBullet*> mEnemyBulletList;
    static const int MAX_BULLET_COUNT;
};
