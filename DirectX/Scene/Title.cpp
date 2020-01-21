#include "Title.h"
#include "GamePlay.h"
#include "../Actor/Transform2D.h"
#include "../Sprite/Sprite.h"
#include "../System/Game.h"

Title::Title() :
    SceneBase(),
    mNextKey(KeyCode::Space) {
}

Title::~Title() = default;

void Title::startScene() {
    auto title = new Sprite(mRenderer, "press_space.png");
    title->transform()->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f, Game::WINDOW_HEIGHT / 2.f));
}

void Title::updateScene() {
    if (Input::getKeyDown(mNextKey)) {
        nextScene(std::make_shared<GamePlay>());
    }
}
