#include "GimmickComponent.h"
#include "CircleCollisionComponent.h"
#include "ComponentManager.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"


GimmickComponent::GimmickComponent(Actor* owner):
	Component(owner),
	mCollider(nullptr)
{

}


GimmickComponent::~GimmickComponent() = default;


void GimmickComponent::start()
{
	mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
}

void GimmickComponent::update()
{
	hit();
}

void GimmickComponent::hit()
{
	for (auto&& hit : mCollider->onCollisionEnter())
	{
		auto a = hit;
		if (hit->getOwner()->tag() == "Player")
		{
			Actor::destroy(hit->getOwner());
		}
		if (hit->getOwner()->tag() == "Enemy")
		{
			Actor::destroy(hit->getOwner());
		}
	}
}
