#include "Pause.h"
#include "Sprite.h"
#include "../Scene/GamePlay.h"
#include "../UI/SpriteManager.h"
#include "../Utility/Input.h"
#include <list>

Pause::Pause(std::shared_ptr<GamePlay> game) :
    UI(),
    mGame(game) {
    if (auto g = mGame.lock()) {
        g->setState(GameState::Paused);
    }
    addSprite(new Sprite("kuppa.png", Vector2(548.f, 599.f), 0.6f));
    addSprite(new Sprite("cute_cat_illust_3737.png", Vector2(830.f, 800.f), 0.1f));
    addSprite(new Sprite("menuBG.png", Vector2(1024.f, 576.f), 0.9f));
}

Pause::~Pause() {
    if (auto g = mGame.lock()) {
        g->setState(GameState::Play);
    }
}

void Pause::update() {
    if (Input::getKeyDown(KeyCode::Alpha1)) {
        close();
    }
}
