#include "ActorManager.h"
#include "Actor.h"
#include "PlayerActor.h"
#include <algorithm>
#include <iterator>

ActorManager::ActorManager() = default;

ActorManager::~ActorManager() = default;

void ActorManager::update() {
    mUpdatingActors = true;
    for (auto&& actor : mActors) {
        actor->update();
    }
    mUpdatingActors = false;

    fromPendingToMain();

    remove();
}

void ActorManager::draw() const {
    for (const auto& actor : mActors) {
        actor->drawActor();
    }
}

void ActorManager::add(Actor * add) {
    if (mUpdatingActors) {
        mPendingActors.emplace_back(add);
    } else {
        mActors.emplace_back(add);
    }
}

void ActorManager::remove() {
    auto itr = mActors.begin();
    while (itr != mActors.end()) {
        if ((*itr)->getState() == ActorState::Dead) {
            itr = mActors.erase(itr);
        } else {
            ++itr;
        }
    }
}

void ActorManager::clear() {
    mPendingActors.clear();
    mActors.clear();
}

std::shared_ptr<PlayerActor> ActorManager::getPlayer() const {
    std::shared_ptr<PlayerActor> p = nullptr;
    for (const auto& actor : mActors) {
        p = std::dynamic_pointer_cast<PlayerActor>(actor);
        if (p) {
            return p;
        }
    }
    //最後まで見つからなければnullptrを返す
    return p;
}

void ActorManager::fromPendingToMain() {
    if (mPendingActors.empty()) {
        return;
    }
    std::copy(mPendingActors.begin(), mPendingActors.end(), std::back_inserter(mActors));
    mPendingActors.clear();
}

std::list<std::shared_ptr<Actor>> ActorManager::mActors;
std::list<std::shared_ptr<Actor>> ActorManager::mPendingActors;
bool ActorManager::mUpdatingActors = false;