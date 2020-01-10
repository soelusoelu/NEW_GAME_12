#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Collider;

enum class SkippedFlag
{
	FALSE, //”ò‚Î‚³‚ê‚Ä‚¢‚È‚¢‚È‚ç
	TRUE   //”ò‚Î‚³‚ê‚Ä‚¢‚é‚È‚ç
};

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
	Vector2 normal();
	Vector2 shot();
	Vector2 tackle(const Vector2& movement);

	Vector2 search();

private:
	SkippedFlag mFlag;
	Vector2 mDestination;//©•ª‚ÌŒ³‚ÌˆÊ’u
	std::shared_ptr<Collider>mCol;
};

