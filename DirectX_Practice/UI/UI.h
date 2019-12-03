#pragma once

#include <list>

enum class UIState {
    Active,
    Closing
};

class Sprite;

class UI {
public:
    UI();
    virtual ~UI();
    virtual void update() = 0;
    void close();
    void addSprite(Sprite* add);
    UIState getState() const;

private:
    std::list<Sprite*> mSprites;
    UIState mState;
};
