#pragma once
#include "../Vector2.h"

namespace {

	constexpr int map_numX = 4;
	constexpr int map_numY = 4;

	constexpr int map_size = 32;

	constexpr int map_maxwidth = 32;
	constexpr int map_maxheight = 16;

}


struct MapData {

	int height;
	int width;

	int data[map_maxheight][map_maxwidth];
};



class Map
{
public:

	Map();
	~Map();

	void Init();
	void End();
	void Update(Vec2 playerpos);
	void Draw();
	
	void SetMapData();

private:

	MapData map_[map_numX][map_numY];
	int groundH_;

	Vec2 mappos_;
	Vec2 startmappos_;

};
