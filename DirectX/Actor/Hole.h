#pragma once

#include "Actor.h"
#include "../Component/GimmickComponent.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;

class Hole: public Actor
{
public:
	Hole(std::shared_ptr<Renderer> renderer, const Vector2& pos, const char* tag = "Hole");
	~Hole();
	virtual void updateActor() override;

private:
	CircleCollisionComponent* mCollide;
	SpriteComponent* mSprite;
	GimmickComponent* mGimmick;
};

