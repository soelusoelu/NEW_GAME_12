#include "PlayerActor.h"
#include "Transform2D.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SpriteComponent.h"

PlayerActor::PlayerActor(std::shared_ptr<Renderer> renderer, const char* tag) :
    Actor(tag),
    mCollide(new CircleCollisionComponent(this)),
    mMove(new PlayerMoveComponent(this, renderer)),
    mSprite(new SpriteComponent(this, renderer, "player.png", 0.5f)) {
    getTransform()->setScale(0.5f, mSprite->getTextureSize());
    getTransform()->setPosition(Vector2(100.f, 100.f));
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}
