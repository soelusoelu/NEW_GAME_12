#include "Hole.h"
#include "Transform2D.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"

Hole::Hole(std::shared_ptr<Renderer> renderer, const Vector2& pos, const char* tag):
	Actor(renderer,tag),
	mCollide(new CircleCollisionComponent(this)),
	mSprite(new SpriteComponent(this, "bbbb.png")),
	mGimmick(new GimmickComponent(this))
{
	transform()->setPosition(pos);
}

Hole::~Hole() = default;

void Hole::updateActor()
{
}
