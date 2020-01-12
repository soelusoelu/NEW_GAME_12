#pragma once

#include "Component.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Renderer;
class SpriteComponent;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, std::shared_ptr<Renderer> renderer, int updateOrder = 10);
    ~PlayerMoveComponent();
    virtual void start() override;
    virtual void update() override;
    int getAccelerate() const;
    void setAccelerate(const Vector2& acceleration);
    void reSetAccelerate();
    void setDecelerate(bool flag);

private:
    void move();
    void deceleration();
    void anchor();
    void dead();

private:
    std::shared_ptr<Renderer> mRenderer;
    std::shared_ptr<SpriteComponent> mSpriteComp;
    Vector2 mAcceleration;
    float mAccelerationSpeed;
    Vector2 mAccelerationRange;
    Vector2 mAnchorAccelerationRange;
    Vector2 mDeceleration;
    float mDecelerationSpeed;
    float mDestroySpeed;
    bool mIsDecelerated;
    KeyCode mAnchorKey;
};

