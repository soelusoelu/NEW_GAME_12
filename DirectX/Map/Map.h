#pragma once

#include "../Device/CSVReader.h"
#include "../Utility/Math.h"


enum class Category
{
	EMPTY,//�����Ȃ�	
	WALL,//��
	HOLE,//��
	PILLAR//��
};

class Map
{
public:                                                                   
	Map();
	~Map();
	void init(const char* filename);
	int howManyWall();//�ǂ������邩��Ԃ�
	int howManyHole();//���������邩��Ԃ�
	int howManyPillar();//���������邩��Ԃ�
	Vector2& getPosWall(int i);//�ǂ̈ʒu����Ԃ�
	Vector2& getPosHole(int i);//���̈ʒu����Ԃ�
	Vector2& getPosPillar(int i);//���̈ʒu����Ԃ�
	int returnWidth();//�}�b�v�S�̂̉��傫��
	int returnHeight();//�}�b�v�S�̂̏c�傫��

private:
	//Vector2* mWallPos;//�ʒu�ۊǗp
	//Vector2* mHolePos;//�ʒu�ۊǗp
	//Vector2* mPillarPos;//�ʒu�ۊǗp
	std::vector<Vector2>mWallPos;
	std::vector<Vector2>mHolePos;
	std::vector<Vector2>mPillarPos;
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	int mWidth;
	int mHeight;
};
