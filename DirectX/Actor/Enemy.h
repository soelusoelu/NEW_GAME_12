#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <memory>

class Renderer;
class CircleCollisionComponent;
class SpriteComponent;
class EnemyComponent;

enum class Scale{
	SMALL,
	MIDDL,
	BIG
};

enum class Type{
	NORMAL,
	SHOT,
	TACKLE
};

class Enemy :public Actor {
public:
	Enemy(std::shared_ptr<Renderer>renderer,const Vector2& pos,Scale scale, Type type, const char* tag = "Enemy");
	~Enemy();
	virtual void updateActor() override;
	
private:
	
	CircleCollisionComponent* mCollide;
	SpriteComponent* mSprite;
	EnemyComponent* mEnemy;
	Scale mScale;
	Type mType;
};