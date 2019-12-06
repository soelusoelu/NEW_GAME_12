#include "Sousa.h"
#include "../UI/Sprite.h"
#include "../Utility/Input.h"

Sousa::Sousa() :
    SceneBase() {
    new Sprite("sousa.png", 0.1f);
}

Sousa::~Sousa() = default;

void Sousa::updateScene() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::GamePlay);
    }
}

void Sousa::drawScene() const {
}
