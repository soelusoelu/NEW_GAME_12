#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Collider;

class EnemyComponent:public Component
{
public:
	EnemyComponent(Actor* owner);
	~EnemyComponent();
	// Component ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void start() override;

	virtual void update() override;

	void move(const Vector2& movement);

	void hit();

	Vector2 search();

private:
	
	std::shared_ptr<Collider>mCol;
};

