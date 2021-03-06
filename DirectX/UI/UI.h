﻿#pragma once

#include <list>
#include <memory>

enum class UIState {
    ACTIVE,
    NON_ACTIVE,
    CLOSING
};

class UIManager;
class Sprite;

class UI {
protected:
    UI();
public:
    virtual ~UI();
    void update();
    virtual void updateUI() = 0;
    void close();
    void addSprite(Sprite* sprite, bool fixedUI = true);
    void removeSprite(Sprite* sprite);
    void setActive(bool value);
    bool getActive() const;
    UIState getState() const;

    static void setUIManager(UIManager* manager);

private:
    std::list<Sprite*> mSprites;
    UIState mState;

    static UIManager* mUIManager;
};
