#pragma once

#include "SceneBase.h"
#include "../Device/Sound.h"
#include "../UI/Sprite.h"
#include <memory>

enum class GameState {
    Play,
    Paused,
    Fade,
    Result,
    Quit
};

class ActorManager;

class GamePlay : public SceneBase, public std::enable_shared_from_this<GamePlay> {
public:
    GamePlay();
    ~GamePlay();
    virtual void updateScene() override;
    virtual void drawScene() const override;

    GameState getState() const;
    void setState(GameState state);

private:
    bool isEndGame();

private:
    std::shared_ptr<ActorManager> mActorManager;
    GameState mState;
    Sprite* mSlowBlack;
    Sprite* mEnd;
    Sprite* mFade;
    std::shared_ptr<SoundInfo> mSound;
};
