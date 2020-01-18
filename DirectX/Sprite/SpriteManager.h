#pragma once
#include "../Utility/Math.h"
#include <memory>
#include <vector>

class Renderer;
class Sprite;

class SpriteManager {
public:
    SpriteManager();
    ~SpriteManager();
    void update();
	void draw(std::shared_ptr<Renderer> renderer, const Vector2& CameraPos = Vector2::zero);
    void add(Sprite* add);
    void add(std::shared_ptr<Sprite> add);
    void clear();

private:
    void remove();
    void sortByZ(); //未実装

    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

private:
    std::vector<std::shared_ptr<Sprite>> mSprites;
};

