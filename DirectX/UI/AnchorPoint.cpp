#include "AnchorPoint.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Sprite/Sprite.h"
#include "../System/Game.h"

AnchorPoint::AnchorPoint(std::shared_ptr<Renderer> renderer, std::shared_ptr<PlayerActor> player) :
    UI(),
    mPlayer(player),
    mPoint(new Sprite(renderer, "Anchor.png", 0.1f)) {
    addSprite(mPoint);
}

AnchorPoint::~AnchorPoint() = default;

void AnchorPoint::updateUI() {
    //アンカーが刺さってたら消して、刺さってなかったら映す
    if (auto p = mPlayer.lock()) {
        mPoint->setActive(!p->isHitAnchor());
        if (!mPoint->getActive()) {
            return;
        }
        auto t = p->transform();
        auto center = t->getPosition() + t->getPivot();
        auto full = Vector2(mPoint->getScreenTextureSize().x, mPoint->getScreenTextureSize().y);
        auto half = full / 2.f;
        mPoint->setPosition(center - half + p->getLastInput() * 200.f);

        //ポイント範囲調整
        mPoint->setPosition(Vector2::clamp(
            mPoint->getPosition(),
            Vector2::zero,
            Vector2(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT) - full
        ));
    } else {
        close();
    }
}
