#pragma once

#include <memory>

enum class EnemyScale {
    SMALL,
    MIDDLE,
    BIG
};

enum class EnemyType {
    NORMAL,
    SHOT,
    TACKLE
};

class Renderer;

class Enemy {
public:
    Enemy(std::shared_ptr<Renderer>renderer);
    ~Enemy();
    void create(EnemyScale scale, EnemyType type);

private:
    std::shared_ptr<Renderer> mRenderer;
};