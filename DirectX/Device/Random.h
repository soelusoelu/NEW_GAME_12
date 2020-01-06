﻿#pragma once

#include "../Utility/Math.h"
#include <random>

class Random {
public:
    static void init();
    //0.f <= value <= 1.f
    static float randomNormal();
    //min <= value <= max
    static int randomRange(int min, int max);
    static float randomRange(float min, float max);
    static Vector2 randomRange(const Vector2& min, const Vector2& max);
    static Vector3 randomRange(const Vector3& min, const Vector3& max);

    Random() = delete;
    ~Random() = delete;

private:
    static std::mt19937 mt;
};

