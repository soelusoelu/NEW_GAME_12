#include "EnemyComponent.h"

#include "../Actor/ActorManager.h"
#include "../Device/Time.h"
#include "../Actor/Actor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/Collider.h"
#include "../Component/CircleCollisionComponent.h"

EnemyComponent::EnemyComponent(Actor * owner):
	Component(owner),
	mCol(nullptr)
{
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::start()
{
	mCol = mOwner->getComponentManager()->getComponent<Collider>();//CircleCollisionComponent
}

void EnemyComponent::update()
{
	move(search());
	hit();
}

void EnemyComponent::move(const Vector2 & movement)//�ړ�
{
	Vector2 difference = movement - mOwner->getTransform()->getPosition();
	difference.normalize();
	
	mOwner->getTransform()->translate(difference * 60.f * Time::deltaTime);//�ړ�����(60�{����)
}

void EnemyComponent::hit()//�����蔻��
{
	auto lists = mCol->onCollisionEnter();
	for (auto&& i : lists)
	{
		if (i->getOwner()->getTag() == "Player")//�v���C���[�Ƃ���������(�ق�Ƃ͌��ɗ�����)
		{
			Vector2 mVec = Actor::getActorManager()->getPlayer()->getTransform()->getPosition() - mOwner->getTransform()->getPosition();
			mVec *= -1;
			mVec.normalize();//�G�l�~�[���猩���v���C���[�Ɣ��΂̃x�N�g��
			mOwner->getTransform()->translate(mVec * 750.f *60.f * Time::deltaTime);//�ړ�����
		}

		if (i->getOwner()->getTag() == "Hole")
		{
			Actor::destroy(mOwner);//������������
		}

	}
}

Vector2 EnemyComponent::search()//�v���C���[�̈ʒu�����󂯎�肻�̒l��Ԃ�
{
	//auto b = Actor::getActorManager()->getPlayer()->getTransform()->getPosition();

	//return  b;
	return Actor::getActorManager()->getPlayer()->getTransform()->getPosition();
}
