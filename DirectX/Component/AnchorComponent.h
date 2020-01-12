#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class SpriteComponent;
class CircleCollisionComponent;
class Transform2D;

class AnchorComponent : public Component {
public:
    AnchorComponent(Actor* owner, std::shared_ptr<Transform2D> player, int updateOrder = 10);
    ~AnchorComponent();
    virtual void start() override;
    virtual void update() override;
    void initialize(const Vector2& direction);
    bool isHit() const;

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
    std::shared_ptr<Transform2D> mPlayer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    std::shared_ptr<CircleCollisionComponent> mCollide;
    Vector2 mAnchorDirection;
    const float MAX_LENGTH;
    const float ANCHOR_INCREASE;
    float mCurrentAnchorLength;
    bool mIsHit;
    Actor* mHitEnemy;
    Vector2 mHitEnemyCenter;
    bool mIsUpdate;
};
