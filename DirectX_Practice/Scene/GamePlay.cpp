#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Device/Physics.h"
#include "../Device/Renderer.h"
#include "../System/Game.h"
#include "../UI/Pause.h"
#include "../UI/PlayerHPSP.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

GamePlay::GamePlay() :
    SceneBase(),
    mActorManager(std::make_shared<ActorManager>()),
    mState(GameState::Play),
    mSlowBlack(new Sprite("slow.png", 0.05f)),
    mEnd(nullptr),
    mFade(nullptr) {
    auto p = new PlayerActor();
    auto e = new EnemyActor(p);
    mUIManager->add(new PlayerHPSP(p, e));
    new Sprite("gameplay.png", 0.99f);
    mSlowBlack->setAlpha(0.f);

    mSound = Renderer::getSound("gameplay.wav");
    mSound->play(true);
}

GamePlay::~GamePlay() {
    mActorManager->clear();
    Renderer::clear();
    Physics::clear();
    mSound->stop();
}

void GamePlay::updateScene() {
    if (mState == GameState::Play) {
        mActorManager->update();

        AvoidancePlayerActor::slowTime();
        auto alpha = AvoidancePlayerActor::mSuccessedAvoidance ? 1.f : 0.f;
        mSlowBlack->setAlpha(alpha);

        Physics::sweepAndPrune();

        //if (Input::getKeyDown(KeyCode::Escape)) {
        //    mUIManager->add(new Pause(shared_from_this()));
        //}
        if (isEndGame()) {
            mFade = new Sprite("fade.png", 0.01f);
            mFade->setScale(Vector2(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
            mFade->setAlpha(0.f);
            mState = GameState::Fade;
        }
    } else if (mState == GameState::Fade) {
        mFade->setAlpha(mFade->getColor().w + 0.01f);
        if (mFade->getColor().w >= 1.f) {
            mState = GameState::Result;
        }
    } else if (mState == GameState::Result) {
        mEnd->setAlpha(mEnd->getColor().w + 0.01f);
        if (mEnd->getColor().w > 1.f) {
            mEnd->setAlpha(1.f);
        }
        if (Input::getKeyDown(KeyCode::Space)) {
            next(Scene::Title);
        }
    }
}

void GamePlay::drawScene() const {
    mActorManager->draw();
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}

bool GamePlay::isEndGame() {
    if (!mActorManager->getActor<EnemyActor>()) {
        mEnd = new Sprite("gameclear.png", 0.001f);
        mEnd->setAlpha(0.f);
        mSound->stop();
        mSound.reset();
        mSound = Renderer::getSound("gameclear.wav");
        mSound->play();
        return true;
    }
    if (!mActorManager->getPlayer()) {
        mEnd = new Sprite("gameover.png", 0.001f);
        mEnd->setAlpha(0.f);
        mSound->stop();
        mSound.reset();
        mSound = Renderer::getSound("gameover.wav");
        mSound->play();
        return true;
    }
    return false;
}
