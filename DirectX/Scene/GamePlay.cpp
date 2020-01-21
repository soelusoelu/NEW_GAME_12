#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorManager.h"
#include "../Actor/EnemyFactory.h"
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
    mEnemyCreater(nullptr),
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
    mEnemyCreater = std::make_unique<EnemyFactory>(mRenderer);
    auto p = mActorManager->getPlayer();
    new AnchorPoint(mRenderer, p);
	Map* mMap = new Map(mRenderer);
	mMap->init("test.csv");
    mCamera2d = std::make_shared<Camera2d>(p);
	mCamera2d->init(mMap->returnWidth() - 64, mMap->returnHeight() - 64);
	//mCamera2d->init(1000, 1000);
	delete(mMap);
}

void GamePlay::updateScene() {
    if (mState == GameState::PLAY) {
        //エネミー生成
        mEnemyCreater->update();
        //総アクターアップデート
        mActorManager->update();
        //総当たり判定
        mPhysics->sweepAndPrune();

        //カメラ
        //mCamera2d->setPlayer(mActorManager->getPlayer());
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
