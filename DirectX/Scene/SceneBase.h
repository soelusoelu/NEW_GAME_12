#pragma once
#include "../Device/Camera2d.h"
#include <memory>

class Camera2d;
class UIManager;
class SpriteManager;
class Renderer;

class SceneBase {
protected:
    SceneBase();
    virtual ~SceneBase();
public:
    virtual void startScene() = 0;
    void update();
    virtual void updateScene() = 0;
    void draw();
    void nextScene(std::shared_ptr<SceneBase> next);
    std::shared_ptr<SceneBase> getNextScene() const;
    void setRenderer(std::shared_ptr<Renderer> renderer);

private:
    void start();

protected:
    UIManager* mUIManager;
    SpriteManager* mSpriteManager;
    std::shared_ptr<Renderer> mRenderer;
	std::shared_ptr<Camera2d> mCamera2d;

private:
    std::shared_ptr<SceneBase> mNext;
    bool mIsStarted;
};
