#include "SceneManager.h"
#include "GamePlay.h"
#include "Sousa.h"
#include "Title.h"

SceneManager::SceneManager() :
    mCurrentScene(std::make_shared<Title>()) {
}

SceneManager::~SceneManager() = default;

void SceneManager::update() {
    mCurrentScene->update();

    if (mCurrentScene->getNextScene() != Scene::None) {
        change(mCurrentScene->getNextScene());
    }
}

void SceneManager::draw() const {
    mCurrentScene->draw();
}

void SceneManager::change(Scene next) {
    mCurrentScene.reset();
    if (next == Scene::Title) {
        mCurrentScene = std::make_shared<Title>();
    } else if (next == Scene::Sousa) {
        mCurrentScene = std::make_shared<Sousa>();
    } else if (next == Scene::GamePlay) {
        mCurrentScene = std::make_shared<GamePlay>();
    }
}
