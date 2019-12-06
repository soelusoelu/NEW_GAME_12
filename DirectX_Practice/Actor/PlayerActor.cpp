#include "PlayerActor.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Component/AnimationComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SPComponent.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mAnimation(new AnimationComponent(this, 0.25f, Vector2(128.f, 128.f))),
    mCircle(new CircleCollisionComponent(this)),
    mHP(new HitPointComponent(this, 1000)),
    mPlayerMove(new PlayerMoveComponent(this)),
    mSP(new SPComponent(this)),
    mSprite(new SpriteComponent(this, "player_anime.png", 0.5f)) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
}
