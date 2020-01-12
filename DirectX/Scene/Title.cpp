#include "Title.h"
#include "GamePlay.h"
#include "../Sprite/Sprite.h"

Title::Title() :
    SceneBase(),
    mNextKey(KeyCode::Space) {
}

Title::~Title() = default;

void Title::startScene() {
    new Sprite(mRenderer, "press_space.png", 0.1f);
}

void Title::updateScene() {
    if (Input::getKeyDown(mNextKey)) {
        nextScene(std::make_shared<GamePlay>());
    }
}
