#pragma once
#include "../Utility/Math.h"
#include <memory>

class PlayerActor;

class Camera2d
{
public:
	Camera2d(std::shared_ptr<PlayerActor> Player);
	~Camera2d();
	void init(int XPos, int YPos);//�}�b�v�S�̂̑傫��
	void update();
	void setPlayer(std::shared_ptr<PlayerActor> Player);
	Vector2 getCameraPos();
private:
	Vector2 getPlayerPos();
    Vector2 mCameraPos;//�J�����̈ʒu
	std::weak_ptr<PlayerActor> mPlayer;//�v���C���[�̈ʒu
	int mXPos;//�}�b�v��X�l
	int mYPos;//�}�b�v��Y�l
    Vector2 mPreviousPlayerPos;
};