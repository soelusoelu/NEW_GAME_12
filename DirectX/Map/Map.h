#pragma once

#include "../Device/CSVReader.h"
#include "../Utility/Math.h"


enum class Category
{
	EMPTY,//何もない	
	WALL,//壁
	HOLE,//穴
	PILLAR//柱
};

class Map
{
public:                                                                   
	Map();
	~Map();
	void init(const char* filename);
	int howManyWall();//壁が何個あるかを返す
	int howManyHole();//穴が何個あるかを返す
	int howManyPillar();//柱が何個あるかを返す
	Vector2& getPosWall(int i);//壁の位置情報を返す
	Vector2& getPosHole(int i);//穴の位置情報を返す
	Vector2& getPosPillar(int i);//柱の位置情報を返す
	int returnWidth();//マップ全体の横大きさ
	int returnHeight();//マップ全体の縦大きさ

private:
	//Vector2* mWallPos;//位置保管用
	//Vector2* mHolePos;//位置保管用
	//Vector2* mPillarPos;//位置保管用
	std::vector<Vector2>mWallPos;
	std::vector<Vector2>mHolePos;
	std::vector<Vector2>mPillarPos;
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	int mWidth;
	int mHeight;
};
