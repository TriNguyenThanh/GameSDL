#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "function.h"

class BaseObject {
protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
public:
	BaseObject();
	~BaseObject();
	void setRect(const int& x, const int& y);
	SDL_Rect getRect();
	SDL_Texture* getObject();

	virtual bool loadImg(std::string filepath, SDL_Renderer* scr);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
};

#endif // !BASE_OBJECT_H_
