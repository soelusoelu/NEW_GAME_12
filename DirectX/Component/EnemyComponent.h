#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Collider;

enum class SkippedFlag
{
	FALSE, //��΂���Ă��Ȃ��Ȃ�
	TRUE   //��΂���Ă���Ȃ�
};

class EnemyComponent:public Component
{
public:
	EnemyComponent(Actor* owner);
	~EnemyComponent();
	// Component ����Čp������܂���
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
	Vector2 mDestination;//�����̌��̈ʒu
	std::shared_ptr<Collider>mCol;
};

