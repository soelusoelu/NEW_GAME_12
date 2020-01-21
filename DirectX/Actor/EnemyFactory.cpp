#include "EnemyFactory.h"
#include "EnemyActor.h"
#include "Transform2D.h"
#include "../Device/CSVReader.h"
#include "../Device/Time.h"
#include "../Utility/Math.h"

EnemyFactory::EnemyFactory(std::shared_ptr<Renderer> renderer) :
    mRenderer(renderer),
    mCSV(std::make_unique<CSVReader>()),
    mEnemyList(0),
    mEnemyData(0),
    mSpawnTimer(0.f),
    mEnemyCount(0) {
    mEnemyList = mCSV->loadString("EnemyList.csv");

    for (size_t i = 0; i < mCSV->getHeight(); i++) {
        parse(i);
    }
    mEnemyCount = mEnemyData.size();
}

EnemyFactory::~EnemyFactory() = default;

void EnemyFactory::update() {
    if (mEnemyData.empty()) {
        return;
    }
    mSpawnTimer += Time::deltaTime;
    while (mEnemyData.front().spawnTime <= mSpawnTimer) {
        create(mEnemyData.front());
        mEnemyData.pop_front();
        if (mEnemyData.empty()) {
            break;
        }
    }
}

size_t EnemyFactory::getEnemyCount() const {
    return mEnemyCount;
}

void EnemyFactory::create(const EnemyData & data) {
    auto e = new EnemyActor(mRenderer, data.type, data.scaleName);
    e->transform()->setScale(data.scale);
    e->transform()->setPosition(data.position);
}

void EnemyFactory::parse(unsigned row) {
    EnemyData data;

    const int num = mCSV->getWidth() * row;
    data.position.x = atoi(mEnemyList.at(num + 1).c_str());
    data.position.y = atoi(mEnemyList.at(num + 2).c_str());
    data.scale = selectScale(mEnemyList.at(num + 3));
    data.scaleName = mEnemyList.at(num + 3);
    data.type = selectType(mEnemyList.at(num + 4));
    data.spawnTime = atoi(mEnemyList.at(num + 5).c_str());
    data.spawnTime /= 60.f;

    mEnemyData.emplace_back(data);
}

float EnemyFactory::selectScale(const std::string & name) const {
    if (name == "Small") {
        return 0.3f;
    } else if (name == "Middle") {
        return 0.5f;
    } else if (name == "Large") {
        return 0.8f;
    }
    return 1.f;
}

EnemyType EnemyFactory::selectType(const std::string & name) const {
    if (name == "Normal") {
        return EnemyType::NORMAL;
    } else if (name == "Shot") {
        return EnemyType::SHOT;
    } else if (name == "Tackle") {
        return EnemyType::TACKLE;
    }
    return EnemyType::NORMAL;
}
