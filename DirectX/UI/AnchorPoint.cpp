#include "AnchorPoint.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Sprite/Sprite.h"
#include "../System/Game.h"

AnchorPoint::AnchorPoint(std::shared_ptr<Renderer> renderer, std::shared_ptr<PlayerActor> player) :
    UI(),
    mPlayer(player),
    mPoint(new Sprite(renderer, "Anchor.png")),
    mLength(200.f) {
    addSprite(mPoint, false);
}

AnchorPoint::~AnchorPoint() = default;

void AnchorPoint::updateUI() {
    //アンカーが刺さってたら消して、刺さってなかったら映す
    if (auto p = mPlayer.lock()) {
        mPoint->setActive(!p->isHitAnchor());
        if (!mPoint->getActive()) {
            return;
        }
        auto point = (p->transform()->getPosition() + Vector2::normalize(p->getAnchorDirection()) * mLength);
        mPoint->transform()->setPosition(point);

        //ポイント範囲調整
        //mPoint->setPosition(Vector2::clamp(
        //    mPoint->getPosition(),
        //    Vector2::zero,
        //    Vector2(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT) - full
        //));
    } else {
        close();
    }
}
