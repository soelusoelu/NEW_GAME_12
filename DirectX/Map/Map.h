#pragma once

#include "../Device/CSVReader.h"
#include "../Device/Renderer.h"
#include "../Utility/Math.h"
#include <list>
#include <memory>
#include <string>
#include <vector>

enum class Category
{
	EMPTY,//何もない	
	WALL,//壁
	HOLE,//穴
	PILLAR//柱
};

struct GimmickData
{
	Vector2 position;
	Category type;
};

class Map
{
public:                                                                   
	Map(std::shared_ptr<Renderer> renderer);
	~Map();
	void init(const char* filename);
	void update();
	int returnWidth();//マップ全体の横大きさ
	int returnHeight();//マップ全体の縦大きさ
	void create(const GimmickData& data);

	static int width;
	static int height;
    static int wallSize;

private:
	std::shared_ptr<Renderer> mRenderer;
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	std::list<GimmickData>mGimmickData;
};
