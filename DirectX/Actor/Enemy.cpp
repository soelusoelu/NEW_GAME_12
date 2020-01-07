#include "Enemy.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/EnemyComponent.h"
#include "Transform2D.h"
#include "../Device/Time.h"

Enemy::Enemy(std::shared_ptr<Renderer> renderer, const Vector2 & pos, const char * tag):
	Actor(tag),
	mCollide(new CircleCollisionComponent(this)),
	mSprite(new SpriteComponent(this, renderer, "player.png", 0.51f)),
	mEnemy(new EnemyComponent(this))
{
	//mSprite->setUV();//�摜�؂���
	getTransform()->setPosition(pos);//�ʒu(����)

}

Enemy::Enemy(std::shared_ptr<Renderer> renderer, const Vector2 & pos, const float& size, const char * tag):
	Actor(tag),
	mCollide(new CircleCollisionComponent(this)),
	mSprite(new SpriteComponent(this, renderer, "player.png", 0.51f)),
	mEnemy(new EnemyComponent(this))
{
	getTransform()->setPosition(pos);//�ʒu(����)
	getTransform()->setScale(size);
}

Enemy::~Enemy() = default;

void Enemy::updateActor()
{
}

