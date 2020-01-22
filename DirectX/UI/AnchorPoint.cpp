#include "AnchorPoint.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/Transform2D.h"
#include "../Sprite/Sprite.h"
#include "../System/Game.h"
#include "../Map/Map.h"

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
        auto point = (p->transform()->getPosition() + p->getAnchorDirection() * mLength);

        auto min = Vector2::zero + mPoint->transform()->getSize();
        auto max = Vector2((Map::width - 1) * Map::wallSize, (Map::height - 1) * Map::wallSize) - mPoint->transform()->getSize();

        if (!(point.x < min.x || point.x > max.x || point.y < min.y || point.y > max.y)) { //ポイントがマップ内なら
            mPoint->transform()->setPosition(point);
            return;
        }

        Vector2 p0[4] = {
            min,
            min,
            Vector2(max.x, min.y),
            Vector2(min.x, max.y)
        };
        Vector2 p1[4] = {
            Vector2(max.x, min.y),
            Vector2(min.x, max.y),
            max,
            max
        };

        Vector2 intersect;
        for (int i = 0; i < 4; i++) {
            auto result = lineIntersection(p0[i], p1[i], p->transform()->getPosition(), point, &intersect);
            if (result) {
                break;
            }
        }
        mPoint->transform()->setPosition(intersect);
    } else {
        close();
    }
}

bool AnchorPoint::lineIntersection(const Vector2 & p0, const Vector2 & p1, const Vector2 & p2, const Vector2 & p3, Vector2 * intersect) {
    auto a = p1 - p0;
    auto b = p3 - p2;
    auto c = p2 - p0;

    auto ab = Vector2::cross(a, b);
    auto t1 = Vector2::cross(c, a) / ab;
    auto t2 = Vector2::cross(c, b) / ab;

    *intersect = p0 + t2 * a; //交差しなくても求めとく

    return ((0 < t1 && t1 < 1) && (0 < t2 && t2 < 1));
}
