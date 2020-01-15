﻿#pragma once

#include "../Utility/Math.h"
#include <memory>

enum class ActorState {
    ACTIVE,
    DEAD
};

class ComponentManager;
class Transform2D;
class Time;
class ActorManager;

class Actor {
protected:
    Actor(const char* tag = "");
    Actor(Actor* parent, const char* tag = "");
public:
    virtual ~Actor();

    //すべての更新
    void update();
    //アクター固有の更新
    virtual void updateActor() = 0;

    //ワールド行列の更新
    void computeWorldTransform();

    //親子関係
    void addChild(Actor* child);
    void removeChild(Actor* child);
    void removeChild(const char* tag);
    Actor* findChild(const char* tag);
    Actor* parent() const;
    Actor* root() const;

    //アクター削除
    static void destroy(Actor* actor);
    static void destroy(std::shared_ptr<Actor> actor);
    static void destroy(Actor* actor, float sec);
    static void destroy(std::shared_ptr<Actor> actor, float sec);

    //ゲッター、セッター
    std::shared_ptr<ComponentManager> componentManager() const;
    std::shared_ptr<Transform2D> transform() const;
    ActorState getState() const;
    const char* tag() const;

    //ActorManagerの登録
    static void setActorManager(ActorManager* manager);
    ActorManager* getActorManager();

private:
    void destroyTimer();
    void setParent(Actor* parent);

private:
    std::shared_ptr<ComponentManager> mComponentManager;
    std::shared_ptr<Transform2D> mTransform;
    std::unique_ptr<Time> mDestroyTimer;
    Actor* mParent;
    Actor** mChildren;
    unsigned mChildCount;
    ActorState mState;
    const char* mTag;

    static ActorManager* mActorManager;
};

