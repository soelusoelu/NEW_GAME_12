#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../UI/Sprite.h"

SpriteComponent::SpriteComponent(Actor* owner, const char* fileName, float z) :
    Component(owner),
    mSprite(new Sprite(fileName, z)) {
}

SpriteComponent::~SpriteComponent() {
    Sprite::destroy(mSprite);
}

void SpriteComponent::update() {
}

Sprite* SpriteComponent::getSprite() const {
    return mSprite;
}
