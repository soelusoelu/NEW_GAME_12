#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class SpriteComponent;
class CircleCollisionComponent;

class AnchorComponent : public Component {
public:
    AnchorComponent(Actor* owner, Actor* player, const Vector2& anchorDirection);
    ~AnchorComponent();
    virtual void start() override;
    virtual void update() override;

private:
    //�A���J�[�̓���
    void extend();
    //�A���J�[�̓����蔻��𖈃t���[���X�V
    void updateCollider();
    //�����蔻��
    void hit();
    //�A���J�[���h�������Ƃ��̈ړ�����
    void hitClamp();
    //���ʏ���
    void dead();
    //�v���C���[�̒��S���W�̎擾
    Vector2 playerCenter() const;

private:
    Actor* mPlayer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    std::shared_ptr<CircleCollisionComponent> mCollide;
    Vector2 mAnchorDirection;
    float mAnchorIncrease;
    float mCurrentAnchorLength;
    bool mIsHit;
    Vector2 mHitEnemyCenter;
    static const float MAX_LENGTH;
};
