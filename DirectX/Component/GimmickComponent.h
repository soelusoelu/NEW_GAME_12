#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class CircleCollisionComponent;

class GimmickComponent :public Component
{
public:
	GimmickComponent(Actor* owner);
	~GimmickComponent();

	virtual void start() override;
    virtual void update() override;

private:
    void hit();

private:
    std::shared_ptr<CircleCollisionComponent> mCollider;
};

