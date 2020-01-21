#include "Map.h"


Map::Map():
	mWallPos(0),
	mHolePos(0),
	mPillarPos(0),
	mCSVReader(nullptr),
	mCSV(0),
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
	mCSVReader = new CSVReader(filename);
	mCSV = mCSVReader->load(filename);

	mWidth = mCSVReader->getWidth();
	mHeight = mCSVReader->getHeight();
	
	for (int i = mCSV.size(); i > 0; --i)
	{
		switch (mCSV[i])
		{
		case 0:break;
		case 1:mWallPos.emplace_back(Vector2(mWidth - i, mHeight - i) * 64); break;
		case 2:mHolePos.emplace_back(Vector2(mWidth - i, mHeight - i) * 64); break;
		case 3:mPillarPos.emplace_back(Vector2(mWidth - i, mHeight - i) * 64); break;
		default:
			break;
		}
	}

}

int Map::howManyWall()
{
	return mWallPos.size();
}

int Map::howManyHole()
{
	return mHolePos.size();
}

int Map::howManyPillar()
{
	return mPillarPos.size();
}

Vector2 & Map::getPosWall(int i)
{
	return mWallPos[i];
}

Vector2 & Map::getPosHole(int i)
{
	return mHolePos[i];
}

Vector2 & Map::getPosPillar(int i)
{
	return mPillarPos[i];
}

int Map::returnWidth()
{
	return mWidth * 64;
}

int Map::returnHeight()
{
	return mHeight * 64;
}
