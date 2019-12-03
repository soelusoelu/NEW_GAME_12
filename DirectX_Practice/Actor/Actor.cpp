#include "Actor.h"
#include "ActorManager.h"
#include "ComponentManagementOfActor.h"
#include "../Device/Time.h"

Actor::Actor(const char* tag) :
    mComponentManager(std::make_shared<ComponentManagementOfActor>()),
    mDestroyTimer(nullptr),
    mState(ActorState::Active),
    mTag(tag) {
    ActorManager::add(this);
}

Actor::~Actor() = default;

void Actor::update() {
    mComponentManager->start();
    if (mState == ActorState::Active) {
        computeWorldTransform();

        mComponentManager->update();
        updateActor();

        computeWorldTransform();

        destroyTimer();
    }
}

void Actor::computeWorldTransform() {
    //mComponentManager->executeOnUpdateWorldTransform();
}

void Actor::destroy(Actor * actor) {
    actor->mState = ActorState::Dead;
}

void Actor::destroy(std::shared_ptr<Actor> actor) {
    actor->mState = ActorState::Dead;
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

std::shared_ptr<ComponentManagementOfActor> Actor::getComponentManager() const {
    return mComponentManager;
}

ActorState Actor::getState() const {
    return mState;
}

const char* Actor::getTag() const {
    return mTag;
}

void Actor::destroyTimer() {
    if (!mDestroyTimer) {
        return;
    }
    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        mState = ActorState::Dead;
    }
}
