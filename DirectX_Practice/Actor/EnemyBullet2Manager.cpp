#include "EnemyBullet2Manager.h"
#include "EnemyBullet2.h"
#include "../Device/Sound.h"
#include "../Device/Time.h"

EnemyBullet2Manager::EnemyBullet2Manager(Sprite* enemySprite, bool* completedAttack, int shotCount, float rate) :
    Actor(),
    mCompletedAttack(completedAttack),
    mDestroyTimer(std::make_unique<Time>(2.f)) {
    int rot = 360 / shotCount;
    for (int i = 0; i < shotCount; i++) {
        new EnemyBullet2(enemySprite, i * rot, rate);
    }
    Sound::play("boss_nomal_attak.wav");
}

EnemyBullet2Manager::~EnemyBullet2Manager() {
    *mCompletedAttack = true;
}

void EnemyBullet2Manager::updateActor() {
    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(this);
    }
}

void EnemyBullet2Manager::drawActor() const {
}
