#include "Wall.h"
#include "Transform2D.h"
#include "../Component/SpriteComponent.h"

Wall::Wall(std::shared_ptr<Renderer> renderer, const Vector2& pos, const char* tag) :
	Actor(renderer,tag),
	mSprite(new SpriteComponent(this,  "aaaa.png")),
	mOnly(new OnlyHitComponent(this))
{
	transform()->setPosition(pos);
}

Wall::~Wall() = default;

void Wall::updateActor()
{

}


