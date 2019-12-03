#include "SpriteComponent.h"
#include "../Actor/Actor.h"
#include "../UI/Sprite.h"

SpriteComponent::SpriteComponent(Actor* owner, const char* fileName, const Vector2& size, float z) :
    Component(owner),
    mSprite(new Sprite(fileName, size, z)) {
}

SpriteComponent::~SpriteComponent() {
    Sprite::destroy(mSprite);
}

void SpriteComponent::update() {
}

Sprite* SpriteComponent::getSprite() const {
    return mSprite;
}
