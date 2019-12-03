#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/PlayerAttack.h"
#include "../Actor/SpecialAttack.h"
#include "../Actor/TakeDamageEffectActor.h"
#include "../Component/AnimationComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Sound.h"
#include "../Device/Time.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"
#include "../Utility/Input.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mAnim(nullptr),
    mSprite(nullptr),
    mCircle(nullptr),
    mHP(nullptr),
    mSP(nullptr),
    MOVE_SPEED(4.f),
    FALL_SPEED(9.8f),
    mCurrentJumpPower(0.f),
    mX(0.f),
    AVOIDANCE_LENGTH(200),
    mAttackTimer(std::make_unique<Time>(0.25f)),
    mCanAttack(true),
    mState(PlayerState::OnGround),
    mDir(Direction::Right),
    mRunningAvoidance(false),
    mAfterPosition(Vector2::zero),
    mNormalDir(Vector2::zero) {
}

PlayerMoveComponent::~PlayerMoveComponent() = default;

void PlayerMoveComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f, Game::WINDOW_HEIGHT - (mSprite->getTextureSize().y * mSprite->getScale().y)));
    mSprite->setUV(0.f, 0.f, 0.25f, 0.5f);
    mSprite->setScale(0.75f);

    mAnim = mOwner->getComponentManager()->getComponent<AnimationComponent>();
    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
    mHP = mOwner->getComponentManager()->getComponent<HitPointComponent>();
    mSP = mOwner->getComponentManager()->getComponent<SPComponent>();
}

void PlayerMoveComponent::update() {
    move();
    jump();
    jumpUpdate();
    fall();
    avoidance();
    avoidanceUpdate();
    posClamp();
    canAttack();
    attack();
    specialAttack();
    hit();
    dead();
}

void PlayerMoveComponent::move() {
    int horizontal = Input::horizontal();
    if (!Math::nearZero(horizontal)) {
        mSprite->translate(Vector2(horizontal, 0.f) * MOVE_SPEED * AvoidancePlayerActor::slowOfPlayer());

        mDir = horizontal < 0 ? Direction::Left : Direction::Right;

        mAnim->set(static_cast<int>(mDir));
    }
}

void PlayerMoveComponent::jump() {
    if (!Input::getKeyDown(KeyCode::W) && !Input::getKeyDown(KeyCode::UpArrow)) {
        return;
    }
    if (mState != PlayerState::OnGround) {
        return;
    }

    //スペースを押していて、地面に立っていたら↓
    mState = PlayerState::Jump;
    mCurrentJumpPower = 0.f;
    mX = 0.f;

    Sound::play("jump.wav");
}

void PlayerMoveComponent::jumpUpdate() {
    if (mState != PlayerState::Jump) { //ジャンプ中以外無視
        return;
    }

    //y = ax ^ 2 + bx + c
    //2次関数でジャンプ量調整
    mX += 0.1f/* * -AvoidancePlayerActor::slowOfPlayer()*/;
    if (mRunningAvoidance) {
        return;
    }
    mCurrentJumpPower = -3 * Math::pow<float>(mX, 2) + mX + 28.f; //一番右の値がジャンプ量に直結
    mSprite->translate(Vector2(0.f, -mCurrentJumpPower));
}

void PlayerMoveComponent::fall() {
    if (mRunningAvoidance) {
        return;
    }
    //重力は常にかける
    mSprite->translate(Vector2(0.f, FALL_SPEED /** AvoidancePlayerActor::slowOfPlayer()*/));

    auto sizeY = mSprite->getScreenTextureSize().y;
    auto posY = mSprite->getPosition().y;
    if (posY + sizeY + 5.f > Game::WINDOW_HEIGHT) { //無理やり
        mState = PlayerState::OnGround;
    }
}

void PlayerMoveComponent::avoidance() {
    if (!Input::getKeyDown(KeyCode::Space)) {
        return;
    }
    if (mRunningAvoidance) {
        return;
    }
    if (AvoidancePlayerActor::mSuccessedAvoidance) {
        return;
    }

    mRunningAvoidance = true;

    auto avoidancePos = mSprite->getPosition();
    auto l = mDir == Direction::Left ? -AVOIDANCE_LENGTH : AVOIDANCE_LENGTH;
    mAfterPosition = mSprite->getPosition();
    mAfterPosition.x += l;
    mAfterPosition.x = Math::clamp<float>(mAfterPosition.x, 0.5f, Game::WINDOW_WIDTH - mSprite->getScreenTextureSize().x + 0.5f);
    mNormalDir = mAfterPosition - mSprite->getPosition();
    mNormalDir.normalize();

    if (l < 0) {
        avoidancePos.x -= AVOIDANCE_LENGTH - mSprite->getScreenTextureSize().x;
    }
    auto scale = mSprite->getScale();
    scale.x = AVOIDANCE_LENGTH / mSprite->getScreenTextureSize().x;

    new AvoidancePlayerActor(dynamic_cast<PlayerActor*>(mOwner), avoidancePos, scale);

    mCircle->disabled();
}

void PlayerMoveComponent::avoidanceUpdate() {
    if (!mRunningAvoidance) {
        return;
    }

    auto oneFrameLength = AVOIDANCE_LENGTH / 10.f;
    mSprite->translate(mNormalDir * oneFrameLength);

    if (Math::abs(mSprite->getPosition().x - mAfterPosition.x) < oneFrameLength + 1) {
        mRunningAvoidance = false;
    }
}

void PlayerMoveComponent::posClamp() {
    auto pos = mSprite->getPosition();
    auto size = mSprite->getScreenTextureSize();
    pos.x = Math::clamp<float>(pos.x, 0.f, Game::WINDOW_WIDTH - size.x);
    pos.y = Math::clamp<float>(pos.y, 0.f, Game::WINDOW_HEIGHT - size.y);

    mSprite->setPosition(pos);
}

void PlayerMoveComponent::canAttack() {
    if (mCanAttack) {
        return;
    }

    mAttackTimer->update();
    if (mAttackTimer->isTime()) {
        mAttackTimer->reset();
        mCanAttack = true;
    }
}

void PlayerMoveComponent::attack() {
    if (!Input::getKeyDown(KeyCode::LeftShift) && !Input::getKeyDown(KeyCode::RightShift)) {
        return;
    }
    if (!mCanAttack) {
        return;
    }
    Vector2 pos = mSprite->getPosition();
    pos += mDir == Direction::Left ? Vector2(-144.f, -64.f) : Vector2(96.f, -64.f);

    new PlayerAttack(dynamic_cast<PlayerActor*>(mOwner), pos);
    mCanAttack = false;

    Sound::play("player_attak.wav");
}

void PlayerMoveComponent::specialAttack() {
    if (!Input::getKeyDown(KeyCode::Q)) {
        return;
    }
    auto sp = mSP->sp();
    if (sp == 0 || sp % mSP->getOneGauge() != 0) {
        return;
    }

    new SpecialAttack(dynamic_cast<PlayerActor*>(mOwner));
    mSP->use(mSP->getOneGauge() * 2 - 1);
}

void PlayerMoveComponent::hit() {
    if (!mCircle->getEnable()) {
        mCircle->enabled();
        return;
    }

    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "EnemyBullet") {
            continue;
        }
        if (AvoidancePlayerActor::mSuccessedAvoidance) {
            continue;
        }

        auto damage = c->getOwner()->getComponentManager()->getComponent<DamageComponent>();
        mHP->takeDamage(damage->damage());

        Sound::play("damage6.wav");

        new TakeDamageEffectActor();
    }
}

void PlayerMoveComponent::dead() {
    if (mHP->hp() <= 0) {
        Actor::destroy(mOwner);
    }
}
