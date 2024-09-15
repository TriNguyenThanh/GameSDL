#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "function.h"
#include "Base_Object.h"

#define MAX_TILE 20

class TileMat : public BaseObject {
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* scr);
	void DrawMap(SDL_Renderer* scr);
	Map getMap();
	void setmap(Map& map_data) { game_map = map_data;}
	
private:
	Map game_map;
	TileMat tile_mat[MAX_TILE];
};

#endif // !GAME_MAP_H_
