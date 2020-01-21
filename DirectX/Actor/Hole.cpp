#include "Hole.h"
#include "Transform2D.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

Hole::Hole(std::shared_ptr<Renderer> renderer, const Vector2& pos, const char* tag):
	Actor(tag),
	mCollide(new CircleCollisionComponent(this)),
	mSprite(new SpriteComponent(this, renderer, "circleP.png", 0.5f))
{
	transform()->setPosition(pos);
}

Hole::~Hole() = default;

void Hole::updateActor()
{

}