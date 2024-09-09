#pragma once
#include "Base_Object.h"
BaseObject::BaseObject() {
	p_object = NULL;
	rect.x = rect.y = rect.w = rect.h = 0;
}
BaseObject::~BaseObject() {

}
void BaseObject::setRect(const int& x, const int& y) {
	rect.x = x;
	rect.y = y;
}
SDL_Rect BaseObject::getRect() {
	return rect;
}
SDL_Texture* BaseObject::getObject() {
	return p_object;
}
bool BaseObject::loadImg(std::string filepath, SDL_Renderer* scr) {
	SDL_Texture* new_texture = NULL;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, CORLOR_KEY_R, CORLOR_KEY_G, CORLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(scr, surface);
		if (new_texture) {
			rect.w = surface->w;
			rect.h = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	p_object = new_texture;

	return p_object != NULL;
}
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(des, p_object, clip, &renderquad);
}

void BaseObject::Free() {
	if (p_object != NULL) {
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}