#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class EnemyComponent;


class Enemy :public Actor {
public:
	Enemy(std::shared_ptr<Renderer>renderer,const Vector2& pos, const char* tag = "Enemy");
	Enemy(std::shared_ptr<Renderer>renderer, const Vector2& pos/*1-3‚ð“ü—Í*/,const float& size, const char* tag = "Enemy");
	~Enemy();
	virtual void updateActor() override;
	
private:
	
	CircleCollisionComponent* mCollide;
	SpriteComponent* mSprite;
	EnemyComponent* mEnemy;
};