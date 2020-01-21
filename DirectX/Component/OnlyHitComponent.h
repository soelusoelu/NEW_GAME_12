#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class CircleCollisionComponent;

class OnlyHitComponent :public Component
{
public:
	OnlyHitComponent(Actor* owner);
	~OnlyHitComponent();

	virtual void start() override;
	virtual void update() override;

private:
	void hit();

private:
	std::shared_ptr<CircleCollisionComponent> mCollider;
};