#include "EnemyComponent.h"

#include "../Actor/ActorManager.h"
#include "../Device/Time.h"
#include "../Actor/Actor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Component/ComponentManager.h"
#include "../Component/Collider.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Actor/Enemy.h"

EnemyComponent::EnemyComponent(Actor * owner) :
	Component(owner),
	mFlag(SkippedFlag::FALSE),
	mDestination(Vector2(0.f,0.f)),
	mCol(nullptr)
{
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::start()
{
	mCol = mOwner->componentManager()->getComponent<Collider>();//CircleCollisionComponent
	mDestination = mOwner->transform()->getPosition();
}

void EnemyComponent::update()
{
	//move(search());
	hit();
}

void EnemyComponent::move(const Vector2 & movement)//移動
{
	Vector2 difference = movement - mOwner->transform()->getPosition();
	difference.normalize();
	
	mOwner->transform()->translate(difference * 60.f * Time::deltaTime);//移動処理(60倍する)

	
}

void EnemyComponent::hit()//当たり判定
{
	auto lists = mCol->onCollisionEnter();
	for (auto&& i : lists)
	{
		if (i->getOwner()->tag() == "Player")//プレイヤーとあたったら(ほんとは穴に落ちる)
		{
			//プレイヤーのスピードに応じてダメージ

			//フラグをtrueに
			mFlag = SkippedFlag::TRUE;


			//Vector2 mVec = Actor::getActorManager()->getPlayer()->getTransform()->getPosition() - mOwner->getTransform()->getPosition();
			//mVec *= -1;
			//mVec.normalize();//エネミーから見たプレイヤーと反対のベクトル
			//mOwner->getTransform()->translate(mVec * 750.f *60.f * Time::deltaTime);//移動処理
		}

		if (i->getOwner()->tag() == "Hole")//穴に落ちると即死
		{
			Actor::destroy(mOwner);//自分が消える
		}

	}
}

Vector2 EnemyComponent::normal()
{
	return Vector2();
}

Vector2 EnemyComponent::shot()
{
	return Vector2();
}

Vector2 EnemyComponent::tackle(const Vector2 & movement)
{
	return Vector2();
}

Vector2 EnemyComponent::search()//プレイヤーの位置情報を受け取りその値を返す
{
	//auto b = Actor::getActorManager()->getPlayer()->getTransform()->getPosition();

	//return  b;
	auto p = mOwner->getActorManager()->getPlayer();
	if (p) {
		return p->transform()->getPosition();
	}
	return Vector2::zero;
}
