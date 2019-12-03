#include "SpriteManager.h"
#include "Sprite.h"
#include "Texture.h"
#include <algorithm>

SpriteManager::SpriteManager() = default;

SpriteManager::~SpriteManager() = default;

void SpriteManager::update() {
    for (auto&& sprite : mSprites) {
        sprite->update();
    }
    remove();
    sortByZ();
}

void SpriteManager::draw() const {
    Texture::drawAll(&mSprites);
}

void SpriteManager::add(Sprite* add) {
    std::shared_ptr<Sprite> s(add);
    float z = s->getDepth();
    auto itr = mSprites.begin();
    for (; itr != mSprites.end(); ++itr) {
        if (z > (*itr)->getDepth()) {
            break;
        }
    }
    mSprites.insert(itr, s);
}

void SpriteManager::remove() {
    auto itr = mSprites.begin();
    while (itr != mSprites.end()) {
        if ((*itr)->getState() == SpriteState::Dead) {
            itr = mSprites.erase(itr);
        } else {
            ++itr;
        }
    }
}

void SpriteManager::clear() {
    mSprites.clear();
}

void SpriteManager::sortByZ() {
    if (Sprite::mZSortFlag) { //z値を変更したやつがいればソート
        Sprite::mZSortFlag = false;
        //std::sort(mSprites.begin(), mSprites.end(), [](std::shared_ptr<Sprite> a, std::shared_ptr<Sprite> b) {
        //    return a->getDepth() > b->getDepth();
        //});
    }
}

std::list<std::shared_ptr<Sprite>> SpriteManager::mSprites;
