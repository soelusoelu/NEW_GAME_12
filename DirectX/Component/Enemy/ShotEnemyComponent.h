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
    ShotEnemyComponent(Actor* owner);
    ~ShotEnemyComponent();
    virtual void start() override;
    virtual void update() override;

private:
    void shot();

private:
    std::unique_ptr<Time> mShotTimer;
    std::list<EnemyBullet*> mEnemyBulletList;
    static const int MAX_BULLET_COUNT;
};
