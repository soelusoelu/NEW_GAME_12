#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorManager.h"
#include "../Actor/Enemy.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Hole.h"
#include "../Actor/Pillar.h"
#include "../Actor/Wall.h"
#include "../Component/Collider.h"
#include "../Device/Camera2d.h"
#include "../Device/Physics.h"
#include "../Map/Map.h"
#include "../Scene/Title.h"
#include "../System/Game.h"
#include "../UI/AnchorPoint.h"
#include "../UI/Pause.h"


GamePlay::GamePlay() :
    SceneBase(),
    mActorManager(new ActorManager()),
    mPhysics(new Physics()),
    mState(GameState::PLAY),
    mPauseKey(KeyCode::Alpha1) {
    Actor::setActorManager(mActorManager);
    Collider::setPhysics(mPhysics);
}

GamePlay::~GamePlay() {
    SAFE_DELETE(mActorManager);
    SAFE_DELETE(mPhysics);
    //なぜかColliderのPhysicsが生きてるから
    Collider::setPhysics(nullptr);
}

void GamePlay::startScene() {
    new PlayerActor(mRenderer);
    new Enemy(mRenderer, Vector2(500.f, 300.f), Scale::SMALL, Type::NORMAL);
    new AnchorPoint(mRenderer, mActorManager->getPlayer());
	Map* mMap = new Map();
	mMap->init("test.csv");
	for (int i = 0; i < mMap->howManyWall(); ++i)
	{
		new Wall(mRenderer, Vector2(mMap->getPosWall[i]));
	}
	for (int i = 0; i < mMap->howManyHole(); i++)
	{
		new Hole(mRenderer, Vector2(mMap->getPosHole[i]));
	}
	for (int i = -0; i < mMap->howManyPillar(); ++i)
	{
		new Pillar(mRenderer, Vector2(mMap->getPosPillar[i]));
	}
	mCamera2d = std::make_shared<Camera2d>(mActorManager->getPlayer());
	mCamera2d->init(mMap->returnWidth(), mMap->returnHeight());
}

void GamePlay::updateScene() {
    if (mState == GameState::PLAY) {
        //総アクターアップデート
        mActorManager->update();
        //総当たり判定
        mPhysics->sweepAndPrune();

		//カメラ
		mCamera2d->setPlayer(mActorManager->getPlayer());
		mCamera2d->update();

        if (Input::getKeyDown(mPauseKey)) {
            new Pause(shared_from_this(), mRenderer);
        }

        auto p = mActorManager->getPlayer();
        if (!p) {
            //nextScene(std::make_shared<Title>());
        }
    } else if (mState == GameState::PAUSED) {

    }
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
