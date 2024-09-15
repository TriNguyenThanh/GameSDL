#include "game_map.h"

void GameMap::LoadMap(const char* name) {
	FILE* fptr = nullptr;
	fopen_s(&fptr, name, "rb");
	if (fptr == nullptr) {
		return;
	}
	game_map.max_x = game_map.max_y = 0;
	for (int i = 0; i < MAX_MAP_Y; ++i) {
		for (int j = 0; j < MAX_MAP_X; ++j) {
			fscanf_s(fptr, "%d", &game_map.tile[i][j]);
			int val = game_map.tile[i][j];
			if (val > 0) {
				if (j > game_map.max_x)
					game_map.max_x = j;
				if (i > game_map.max_y)
					game_map.max_y = i;
			}
		}
	}
	//transform to pixel
	game_map.max_x = (game_map.max_x + 1) * TILE_SIZE;
	game_map.max_y = (game_map.max_y + 1) * TILE_SIZE;

	game_map.start_x = game_map.start_y = 0;
	game_map.file_name = name;

	fclose(fptr);
}

void GameMap::LoadTiles(SDL_Renderer* scr) {
	char img_name[20];
	FILE* fptr = nullptr;

	for (int i = 0; i < MAX_TILE; ++i) {
		sprintf_s(img_name, "map/%d.png", i);
		fopen_s(&fptr, img_name, "rb");
		if (fptr == nullptr) {
			continue;
		}
		fclose(fptr);

		tile_mat[i].loadImg(img_name, scr);
	}
}

void GameMap::DrawMap(SDL_Renderer* scr) {
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	int map_x = 0, map_y = 0;

	map_x = game_map.start_x / TILE_SIZE;
	map_y = game_map.start_y / TILE_SIZE;

	x1 = (game_map.start_x % TILE_SIZE) * -1;
	x2 = x1 + scr_w + ((x1 == 0) ? 0 : TILE_SIZE);

	y1 = (game_map.start_y % TILE_SIZE) * -1;
	y2 = y1 + scr_h + ((y1 == 0) ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map.tile[map_y][map_x];
			if (val > 0) {
				tile_mat[val].setRect(j, i);
				tile_mat[val].Render(scr);
			}
			map_x++;
		}
		map_y++;
	}
}

Map GameMap::getMap() {
	return game_map;
}