#include "Actor.h"
#include "ActorManager.h"
#include "Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"
#include "../System/Game.h"

Actor::Actor(const char* tag) :
    Actor(nullptr, tag) {
}

Actor::Actor(Actor* parent, const char* tag) :
    mComponentManager(std::make_shared<ComponentManager>()),
    mTransform(std::make_shared<Transform2D>()),
    mDestroyTimer(nullptr),
    mParent(parent),
    mChildren(new Actor*),
    mChildCount(0),
    mState(ActorState::ACTIVE),
    mTag(tag) {
    if (mActorManager) {
        mActorManager->add(this);
    }
}

Actor::~Actor() {
    for (size_t i = 0; i < mChildCount; i++) {
        destroy(mChildren[i]);
    }
    SAFE_DELETE(mChildren);
}

void Actor::update() {
    mComponentManager->start();
    if (mState == ActorState::ACTIVE) {
        computeWorldTransform();

        mComponentManager->update();
        updateActor();

        computeWorldTransform();

        destroyTimer();
    }
    //すべての子供を更新
    for (size_t i = 0; i < mChildCount; i++) {
        mChildren[i]->update();
    }
}

void Actor::computeWorldTransform() {
    if (mTransform->computeWorldTransform()) {
        mComponentManager->onUpdateWorldTransform();
    }
}

void Actor::addChild(Actor* child) {
    mChildren[mChildCount] = child;
    mChildCount++;
    child->setParent(this);
}

void Actor::removeChild(Actor* child) {
    unsigned num = 0;
    for (size_t i = 0; i < mChildCount; i++) {
        if (mChildren[i] == child) {
            destroy(mChildren[i]);
            num = i;
        }
    }
    //削除したやつより右側にあるやつを詰める
    for (size_t i = 0; i < mChildCount - (num + 1); i++) {
        mChildren[num + i] = mChildren[num + i + 1];
    }

    mChildCount--;
}

void Actor::removeChild(const char* tag) {
    unsigned num = 0;
    for (size_t i = 0; i < mChildCount; i++) {
        if (mChildren[i]->mTag == tag) {
            destroy(mChildren[i]);
            num = i;
        }
    }
    //削除したやつより右側にあるやつを詰める
    for (size_t i = 0; i < mChildCount - (num + 1); i++) {
        mChildren[num + i] = mChildren[num + i + 1];
    }

    mChildCount--;
}

Actor* Actor::findChild(const char* tag) {
    Actor* child = nullptr;
    for (size_t i = 0; i < mChildCount; i++) {
        if (mChildren[i]->mTag == tag) {
            child = mChildren[i];
        }
    }
    return child;
}

Actor* Actor::parent() const {
    return mParent;
}

Actor* Actor::root() const {
    Actor* root = mParent;
    while (root) {
        if (!root->mParent) {
            break;
        }
        root = root->mParent;
    }
    return root;
}

void Actor::destroy(Actor* actor) {
    actor->mState = ActorState::DEAD;
}

void Actor::destroy(std::shared_ptr<Actor> actor) {
    actor->mState = ActorState::DEAD;
}

void Actor::destroy(Actor* actor, float sec) {
    if (actor->mDestroyTimer) {
        return;
    }
    actor->mDestroyTimer = std::make_unique<Time>(sec);
}

void Actor::destroy(std::shared_ptr<Actor> actor, float sec) {
    if (actor->mDestroyTimer) {
        return;
    }
    actor->mDestroyTimer = std::make_unique<Time>(sec);
}

std::shared_ptr<ComponentManager> Actor::componentManager() const {
    return mComponentManager;
}

std::shared_ptr<Transform2D> Actor::transform() const {
    return mTransform;
}

ActorState Actor::getState() const {
    return mState;
}

const char* Actor::tag() const {
    return mTag;
}

void Actor::setActorManager(ActorManager* manager) {
    mActorManager = manager;
}

ActorManager* Actor::getActorManager() {
    return mActorManager;
}

void Actor::destroyTimer() {
    if (!mDestroyTimer) {
        return;
    }
    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        mState = ActorState::DEAD;
    }
}

void Actor::setParent(Actor* parent) {
    mParent = parent;
}

ActorManager* Actor::mActorManager = nullptr;
