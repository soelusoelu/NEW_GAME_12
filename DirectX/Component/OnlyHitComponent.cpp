#include "OnlyHitComponent.h"
#include "CircleCollisionComponent.h"
#include "ComponentManager.h"
#include "../Actor/Actor.h"
#include "../Actor/Transform2D.h"

OnlyHitComponent::OnlyHitComponent(Actor * owner):
	Component(owner),
	mCollider(nullptr)
{
}

OnlyHitComponent::~OnlyHitComponent()
{
}

void OnlyHitComponent::start()
{
	mCollider = mOwner->componentManager()->getComponent<CircleCollisionComponent>();
}

void OnlyHitComponent::update()
{
	hit();
}

void OnlyHitComponent::hit()
{
}
