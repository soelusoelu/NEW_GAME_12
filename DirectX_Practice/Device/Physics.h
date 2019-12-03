#pragma once

#include "../Utility/Math.h"
#include "../Utility/Collision.h"
#include <vector>

class Actor;
class CircleCollisionComponent;

class Physics {
public:
    Physics();
    ~Physics();
    //ボックスコンポーネントの追加・削除
    static void add(CircleCollisionComponent* circle);
    static void remove(CircleCollisionComponent* circle);
    //全削除
    static void clear();
    //総当たり判定
    static void sweepAndPrune();

private:
    static std::vector<CircleCollisionComponent*> mCircles;
};
