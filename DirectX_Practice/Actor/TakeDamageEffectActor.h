#pragma once

#include "Actor.h"

class Sprite;

class TakeDamageEffectActor : public Actor {
public:
    TakeDamageEffectActor(const char* tag = "");
    ~TakeDamageEffectActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    Sprite* mSprite;
};

