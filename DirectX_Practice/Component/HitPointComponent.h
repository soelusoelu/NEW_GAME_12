#pragma once

#include "Component.h"
#include <memory>

class Actor;

class HitPointComponent : public Component {
public:
    HitPointComponent(Actor* onwer, int hp);
    ~HitPointComponent();
    virtual void update() override;
    void takeDamage(int damage);
    void takeHeal(int heal);
    int hp() const;
    float hpRate() const;

private:
    int mHP;
    const int MAX_HP;
};

