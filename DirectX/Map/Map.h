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
	EMPTY,//�����Ȃ�	
	WALL,//��
	HOLE,//��
	PILLAR//��
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
	int returnWidth();//�}�b�v�S�̂̉��傫��
	int returnHeight();//�}�b�v�S�̂̏c�傫��
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
