#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//screen
const int scr_w = 1280;
const int scr_h = 640;
const int scr_BPP = 32;

const int CORLOR_KEY_R = 167;
const int CORLOR_KEY_G = 175;
const int CORLOR_KEY_B = 180;

const int Render_Draw_Color = 0xff;

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define CharFrame 8

#define GRAVITY 0.7
#define MAX_FALL_SPEED 6
#define PLAYER_SPEED 7
#define PLAYER_JUMP_HEIGHT 12

#define BULLET_SPEED 20

#define FPS 60
struct Input {
	int left;
	int right;
	int up;
	int down;
	int jump;
};

struct Map {
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* file_name;
};

#endif // !FUNCTION_H