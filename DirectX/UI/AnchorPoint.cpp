#include "AnchorPoint.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Sprite/Sprite.h"

AnchorPoint::AnchorPoint(std::shared_ptr<Renderer> renderer, PlayerActor* player) :
    UI(),
    mPlayer(player),
    mPoint(new Sprite(renderer, "Anchor.png", 0.1f)) {
    addSprite(mPoint);
}

AnchorPoint::~AnchorPoint() = default;

void AnchorPoint::updateUI() {
    //ƒAƒ“ƒJ[‚ªŽh‚³‚Á‚Ä‚½‚çÁ‚µ‚ÄAŽh‚³‚Á‚Ä‚È‚©‚Á‚½‚ç‰f‚·
    mPoint->setActive(!mPlayer->isHitAnchor());
    if (!mPoint->getActive()) {
        return;
    }
    auto t = mPlayer->transform();
    auto center = t->getPosition() + t->getPivot();
    auto half = Vector2(mPoint->getScreenTextureSize().x / 2.f, mPoint->getScreenTextureSize().y / 2.f);
    mPoint->setPosition(center - half + mPlayer->getLastInput() * 200.f);
}
