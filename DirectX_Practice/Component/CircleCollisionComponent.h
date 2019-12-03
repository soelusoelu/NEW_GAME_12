#pragma once

#include "Component.h"
#include "../Utility/Collision.h"
#include "../Utility/Math.h"
#include <list>
#include <memory>

class Actor;
class Sprite;

class CircleCollisionComponent : public Component {
public:
    CircleCollisionComponent(Actor* onwer);
    ~CircleCollisionComponent();
    virtual void start() override;
    virtual void update() override;
    std::shared_ptr<Circle> getCircle() const;
    void enabled();
    void disabled();
    bool getEnable() const;
    void addHitCircle(CircleCollisionComponent* hit);
    std::list<CircleCollisionComponent*> onCollisionEnter();
    std::list<CircleCollisionComponent*> onCollisionStay();
    std::list<CircleCollisionComponent*> onCollisionExit();

private:
    std::shared_ptr<Circle> mCircle;
    Sprite* mSprite;
    bool mEnable;
    std::list<CircleCollisionComponent*> mPreviousCircles;
    std::list<CircleCollisionComponent*> mCurrentCircles;
};
