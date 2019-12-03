#include "UI.h"
#include "Sprite.h"

UI::UI() :
    mState(UIState::Active) {
}

UI::~UI() {
    for (auto&& sprite : mSprites) {
        Sprite::destroy(sprite);
    }
}

void UI::close() {
    mState = UIState::Closing;
}

void UI::addSprite(Sprite* add) {
    mSprites.emplace_back(add);
}

UIState UI::getState() const {
    return mState;
}
