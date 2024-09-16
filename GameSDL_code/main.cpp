#include "function.h"
#include "Base_Object.h"
#include "game_map.h"
#include "MainCharacter.h"
#include "ImpTimer.h"

BaseObject g_background;

//Init the game
bool initData() {
	bool success = true;
	// SDL prepare the enviroment for the graphic like a window, renderer,...
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;
	
	// 1 is anti aliasing
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	//Create a window
	g_window = SDL_CreateWindow("GAME SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, scr_w, scr_h, SDL_WINDOW_SHOWN);
	
	//check if the window is created
	if (g_window == NULL) {
		success = false;
	}
	else {
		//create a Renderer to draw object like a pen
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		//check if the renderer is created
		if (g_screen == NULL) return false;
		else {
			SDL_SetRenderDrawColor(g_screen, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}
	return success;
}

bool loadBackground() {
	//load background image to backgroung object
	bool ret = g_background.loadImg("img//bkgrd.png", g_screen);
	if (ret == false) return false;
	
	return true;
}

void close() {
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	// init game
	if (initData() == false) return -1;
	// load the background to the background object
	if (loadBackground() == false) return -1;

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	MainChar p_player;
	p_player.loadImg("img//player_right.png", g_screen);
	p_player.set_clip();


	bool is_Quit = false;
	ImpTimer fps_time;
	// infinity loop
	while (!is_Quit) {
		//get the user's activities
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT)
				is_Quit = true;
			p_player.HandelInputAction(g_event, g_screen);

		}
		SDL_SetRenderDrawColor(g_screen, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color);
		//clear the render memory
		SDL_RenderClear(g_screen);

		//draw new screeen into the render memmory
		g_background.Render(g_screen, NULL);
		//game_map.DrawMap(g_screen);
		Map map_data = game_map.getMap();
		
		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x, map_data.start_y);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		game_map.setmap(map_data);
		game_map.DrawMap(g_screen);
		//display to the screen
		SDL_RenderPresent(g_screen);

		int real_time = fps_time.get_tick();
		int time_one_frame = 1000 / FPS;
		if (real_time < time_one_frame) {
			int delay_time = time_one_frame - real_time;
			if (delay_time > 0)
				SDL_Delay(delay_time);
		}
	}

	close();
	return 0;
}