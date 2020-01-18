#pragma once

#include "Component.h"
#include <memory>

class Actor;

class HitPointComponent : public Component {
public:
    HitPointComponent(Actor* onwer, int hp);
    ~HitPointComponent();
    virtual void start() override;
    virtual void update() override;
    void takeDamage(int damage);
    void takeHeal(int heal);
    void setHP(int hp, bool isChangeMax = true);
    int hp() const;
    float hpRate() const;

private:
    int mHP;
    int mMaxHP;
};

