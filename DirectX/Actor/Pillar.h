#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;

class Pillar:public Actor
{
public:
	Pillar(std::shared_ptr<Renderer> renderer, const Vector2& pos, const char* tag = "Pillar");
	~Pillar();
	virtual void updateActor() override;

private:
	CircleCollisionComponent* mCollide;
	SpriteComponent* mSprite;
};

