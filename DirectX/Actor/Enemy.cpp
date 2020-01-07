#include "Enemy.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/EnemyComponent.h"
#include "Transform2D.h"
#include "../Device/Time.h"

#include <cassert>

Enemy::Enemy(std::shared_ptr<Renderer> renderer, const Vector2 & pos, Scale scale, Type type, const char * tag):
	Actor(tag),
	mCollide(new CircleCollisionComponent(this)),
	mSprite(new SpriteComponent(this, renderer, "player.png", 0.51f)),
	mEnemy(new EnemyComponent(this)),
	mScale(scale),
	mType(type)
{
	getTransform()->setPosition(pos);
	switch (mScale)
	{
	case Scale::SMALL: getTransform()->setScale(0.5f); break;
	case Scale::MIDDL:                                 break;
	case Scale::BIG:   getTransform()->setScale(1.5f); break;
	default:
		assert(false);//Debug中は処理を停止。Release中はスルーする(デバックでエラーならエラーが出る)
		break;
	}
}

Enemy::~Enemy() = default;

void Enemy::updateActor()
{
	switch (mType)
	{
	case Type::NORMAL:break;
	case Type::SHOT:break;
	case Type::TACKLE:break;
	default:
		assert(false);
		break;
	}
}

