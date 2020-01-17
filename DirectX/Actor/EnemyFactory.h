#pragma once

#include "../Utility/Math.h"
#include <list>
#include <memory>
#include <string>
#include <vector>

enum class EnemyType {
    NORMAL,
    SHOT,
    TACKLE
};

struct EnemyData {
    Vector2 position;
    float scale;
    EnemyType type;
    float spawnTime;
};

class Renderer;
class CSVReader;

class EnemyFactory {
public:
    EnemyFactory(std::shared_ptr<Renderer> renderer);
    ~EnemyFactory();
    void update();

private:
    void create(const EnemyData& data);
    void parse(unsigned row);
    float selectScale(const std::string& name) const;
    EnemyType selectType(const std::string& name) const;

private:
    std::shared_ptr<Renderer> mRenderer;
    std::unique_ptr<CSVReader> mCSV;
    std::vector<std::string> mEnemyList;
    std::list<EnemyData> mEnemyData;
    float mSpawnTimer;
};

