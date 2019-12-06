#include "TakeDamageEffectActor.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"

TakeDamageEffectActor::TakeDamageEffectActor(const char* tag) :
    Actor(tag),
    mSprite(new Sprite("takeDamage2.png", 0.01f)) {
}

TakeDamageEffectActor::~TakeDamageEffectActor() {
    Sprite::destroy(mSprite);
}

void TakeDamageEffectActor::updateActor() {
    Actor::destroy(this, 1.f);
}

void TakeDamageEffectActor::drawActor() const {
}
