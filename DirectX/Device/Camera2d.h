#pragma once
#include "../Utility/Math.h"
#include <memory>

class PlayerActor;

class Camera2d
{
public:
	Camera2d(std::shared_ptr<PlayerActor> Player);
	~Camera2d();
	void init(int XPos, int YPos);//マップ全体の大きさ
	void update();
	void setPlayer(std::shared_ptr<PlayerActor> Player);
	Vector2 getCameraPos();
private:
	Vector2 getPlayerPos();
    Vector2 mCameraPos;//カメラの位置
	std::weak_ptr<PlayerActor> mPlayer;//プレイヤーの位置
	int mXPos;//マップのX値
	int mYPos;//マップのY値
    Vector2 mPreviousPlayerPos;
};