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
static SDL_Event* g_event = NULL;

//screen
const int scr_w = 1280;
const int scr_h = 640;
const int scr_BPP = 32;

const int CORLOR_KEY_R = 167;
const int CORLOR_KEY_G = 175;
const int CORLOR_KEY_B = 180;

#endif // !FUNCTION_H