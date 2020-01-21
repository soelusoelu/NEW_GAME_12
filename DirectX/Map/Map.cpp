#include "Map.h"
#include "../Actor/Hole.h"
#include "../Actor/Pillar.h"
#include "../Actor/Wall.h"
#include "../Actor/Transform2D.h"



Map::Map(std::shared_ptr<Renderer> renderer) :
	mRenderer(renderer),
	mCSVReader(nullptr),
	mCSV(0),
	mGimmickData(0),
	mWidth(0),
	mHeight(0)
{

}

Map::~Map()
{
}

void Map::init(const char * filename)
{
	mCSV.clear();
	mGimmickData.clear();
	mCSVReader = new CSVReader(filename);
	mCSV = mCSVReader->load(filename);

	mWidth = mCSVReader->getWidth();
	mHeight = mCSVReader->getHeight();
	auto a = mCSV.size();
	for (int i = mCSV.size() - 1; i >= 0; --i)
	{
		GimmickData data;
		data.position = Vector2(i % mCSVReader->getWidth() * 64, i / mCSVReader->getWidth() * 64);
		switch (mCSV[i])
		{
		case 0:data.type = Category::EMPTY; break;
		case 1:data.type = Category::WALL; break;
		case 2:data.type = Category::HOLE; break;
		case 3:data.type = Category::PILLAR; break;
		default:
			break;
		}
		mGimmickData.emplace_back(data);
		
	}
	auto j = mGimmickData.size();
	for (int i = 0; i < j; ++i)
	{
		create(mGimmickData.front());
		mGimmickData.pop_front();
	}
}

void Map::update()
{
	
}

int Map::returnWidth()
{
	return mWidth * 64;
}

int Map::returnHeight()
{
	return mHeight * 64;
}

void Map::create(const GimmickData & data)
{
	if (data.type == Category::WALL)
	{
		auto w = new Wall(mRenderer, data.position);
	}
	else if (data.type == Category::HOLE)
	{
		auto h = new Hole(mRenderer, data.position);
	}
	else if (data.type == Category::PILLAR)
	{
		auto p = new Pillar(mRenderer, data.position);
	}
}
