#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;

class Wall:public Actor
{
public:
	Wall(std::shared_ptr<Renderer> renderer,const Vector2& pos, const char* tag = "Wall");
	~Wall();
	virtual void updateActor() override;

private:
	CircleCollisionComponent* mCollide;
	SpriteComponent* mSprite;
};

