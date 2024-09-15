#ifndef MAIN_CHARACTER_H_
#define MAIN_CHARACTER_H_

#include <vector>
#include "function.h"
#include "Base_Object.h"
#include "BulletObject.h"

class MainChar : public BaseObject {
public:
	MainChar();
	~MainChar();

	enum walk_type {
		WALK_RIGHT = 0,
		WALK_LEFT = -1
	};
	bool loadImg(std::string path, SDL_Renderer* scr);
	void Show(SDL_Renderer* des);
	void HandelInputAction(SDL_Event evt, SDL_Renderer* scr);
	void set_clip();
	void updateImg(SDL_Renderer* des);
	void DoPlayer(Map& map_data);
	void CheckToMap(const Map& map_data);
	void SetMapXY(const int& map_x, const int& map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);

	void set_bullet_list(std::vector<BulletObject*> bullet_list) { p_bullet_list = bullet_list; }
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list; }
	void HandleBullet(SDL_Renderer* des);
private:
	std::vector<BulletObject*> p_bullet_list;

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int W_frame;
	int H_frame;

	SDL_Rect frame_clip[8];
	Input input_type;
	int frame;
	int status;
	bool on_ground;

	int map_x_, map_y_;
	int come_back_time;
};

#endif // !MAIN_CHARACTER_H_
