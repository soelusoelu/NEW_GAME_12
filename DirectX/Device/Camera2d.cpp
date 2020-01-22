#include "Camera2d.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Device/Time.h"
#include "../System/Game.h"

Camera2d::Camera2d(std::shared_ptr<PlayerActor> Player):
	mCameraPos(Vector2(0.f,0.f)),
	mPlayer(Player),
	mXPos(0),
	mYPos(0),
    mPreviousPlayerPos(Vector2::zero)
{
	
}

Camera2d::~Camera2d()
{
}

void Camera2d::init(int mXPos, int mYPos)
{
	this->mXPos = mXPos;
	this->mYPos = mYPos;
}

void Camera2d::update()
{
	
	if (auto p = mPlayer.lock())
	{
		if (p->isHitAnchor())
		{
			if (!p->hitActor()) {
				return;
			}
			Vector2 temp;
			temp.x = p->hitActor()->transform()->getPosition().x - Game::WINDOW_WIDTH / 2.f;
			temp.y = p->hitActor()->transform()->getPosition().y - Game::WINDOW_HEIGHT / 2.f;
			mCameraPos = Vector2::lerp(mCameraPos, temp, Time::deltaTime);
			return;
		}
	}
	//�J����X�l��2/3�𒴂�����v���[���[�ƂƂ��ɃJ�������ړ�������
	if ((mCameraPos.x + Game::WINDOW_WIDTH < mXPos) && (getPlayerPos().x > mCameraPos.x + Game::WINDOW_WIDTH * 2 / 3))
	{
		this->mCameraPos.x = getPlayerPos().x - Game::WINDOW_WIDTH * 2 / 3;
	}
	//�J����X�l��1/3��菬�����Ȃ�����v���[���[�ƂƂ��ɃJ�����ړ�
	if ((mCameraPos.x > 0) && (getPlayerPos().x < mCameraPos.x + Game::WINDOW_WIDTH / 3))
	{
		this->mCameraPos.x = getPlayerPos().x - Game::WINDOW_WIDTH / 3;
	}

	//�J����Y��    
	if ((mCameraPos.y > 0) && (getPlayerPos().y < mCameraPos.y + Game::WINDOW_HEIGHT  / 3))
	{
		this->mCameraPos.y = getPlayerPos().y - Game::WINDOW_HEIGHT  / 3;
	}

	//�J����Y��
	if ((mCameraPos.y + Game::WINDOW_HEIGHT < mYPos) && (getPlayerPos().y > mCameraPos.y + Game::WINDOW_HEIGHT * 2 / 3))
	{
		this->mCameraPos.y = getPlayerPos().y - Game::WINDOW_HEIGHT * 2 / 3;
	}
}

void Camera2d::setPlayer(std::shared_ptr<PlayerActor> Player)
{
	mPlayer = Player;
}

Vector2 Camera2d::getCameraPos()
{
	return mCameraPos;
}

Vector2 Camera2d::getPlayerPos()
{
	if (auto p = mPlayer.lock())
	{
        auto pos = p->transform()->getPosition();
        mPreviousPlayerPos = pos;
        return pos;
	}
    return mPreviousPlayerPos;
}
