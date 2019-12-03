#pragma once

#include "../Utility/Math.h"
#include <memory>

enum class ActorState {
    Active,
    Dead
};

class ComponentManagementOfActor;
class Time;

class Actor {
public:
    Actor(const char* tag = "");
    virtual ~Actor();

    //すべての更新
    void update();
    //アクター固有の更新
    virtual void updateActor() = 0;
    //描画
    virtual void drawActor() const = 0;

    //位置、角度、スケールに変更があった際に更新
    void computeWorldTransform();

    //アクター削除
    static void destroy(Actor* actor);
    static void destroy(std::shared_ptr<Actor> actor);
    static void destroy(Actor* actor, float sec);
    static void destroy(std::shared_ptr<Actor> actor, float sec);

    //ゲッター、セッター
    std::shared_ptr<ComponentManagementOfActor> getComponentManager() const;
    ActorState getState() const;
    const char* getTag() const;

private:
    void destroyTimer();

private:
    std::shared_ptr<ComponentManagementOfActor> mComponentManager;
    std::unique_ptr<Time> mDestroyTimer;
    ActorState mState;
    const char* mTag;
};

