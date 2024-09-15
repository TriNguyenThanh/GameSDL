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

//load the image into a texture
bool BaseObject::loadImg(std::string filepath, SDL_Renderer* scr) {
	SDL_Texture* new_texture = NULL;
	//load image as a surface
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	//check if load surface is done
	if (surface != NULL) {
		//set color key to transparent the image background
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, CORLOR_KEY_R, CORLOR_KEY_G, CORLOR_KEY_B));
		//add surface to textture
		new_texture = SDL_CreateTextureFromSurface(scr, surface);
		if (new_texture != NULL) {
			rect.w = surface->w;
			rect.h = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	//set the texture to the object
	SDL_DestroyTexture(p_object);
	p_object = new_texture;

	return p_object != NULL;
}
//Draw the object
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(des, p_object, clip, &renderquad);
}

//Free the object
void BaseObject::Free() {
	if (p_object != NULL) {
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}