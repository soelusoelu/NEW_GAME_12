#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorManager.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/EnemyFactory.h"
#include "../Actor/PlayerActor.h"
#include "../Component/Collider.h"
#include "../Device/Camera2d.h"
#include "../Device/Physics.h"
#include "../Device/Sound.h"
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
    mState(GameState::PLAY) {
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
        mCamera2d->update();

        if (!mActorManager->getPlayer()) { //ゲームオーバー
            nextScene(std::make_shared<Title>());
        }
        if (mEnemyCreater->getEnemyCount() == 0 && !mActorManager->getActor<EnemyActor>()) { //クリア
            nextScene(std::make_shared<Title>());
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
