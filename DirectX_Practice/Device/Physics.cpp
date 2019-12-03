#include "Physics.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/ActorManager.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Utility/Collision.h"
#include <algorithm>

Physics::Physics() = default;
Physics::~Physics() = default;

void Physics::sweepAndPrune() {
    //mCenter.x - mCenter.mRadiusが小さい順にソート
    std::sort(mCircles.begin(), mCircles.end(), [](CircleCollisionComponent* a, CircleCollisionComponent* b) {
        return a->getCircle()->mCenter.x - a->getCircle()->mRadius < b->getCircle()->mCenter.x - b->getCircle()->mRadius;
    });

    for (size_t i = 0; i < mCircles.size(); i++) {
        auto a = mCircles[i];
        if (!a->getEnable()) {
            continue;
        }
        auto ac = a->getCircle();
        //mCircles[i]の中心+半径を取得
        float max = ac->mCenter.x + ac->mRadius;
        for (size_t j = i + 1; j < mCircles.size(); j++) {
            auto b = mCircles[j];
            if (!b->getEnable()) {
                continue;
            }
            auto bc = b->getCircle();
            //もしmCircles[j]の中心-半径が、mCircles[i]の中心+半径を超えていたら、
            //mCircles[i]と交差する可能性があるボックスは存在しない
            if (bc->mCenter.x - bc->mRadius > max) {
                break;
            } else if (intersect(*ac, *bc)) {
                a->addHitCircle(b);
                b->addHitCircle(a);
            }
        }
    }
}

void Physics::add(CircleCollisionComponent* circle) {
    mCircles.emplace_back(circle);
}

void Physics::remove(CircleCollisionComponent* circle) {
    auto itr = std::find(mCircles.begin(), mCircles.end(), circle);
    if (itr != mCircles.end()) {
        std::iter_swap(itr, mCircles.end() - 1);
        mCircles.pop_back();
        return;
    }
}

void Physics::clear() {
    mCircles.clear();
}

std::vector<CircleCollisionComponent*> Physics::mCircles;
