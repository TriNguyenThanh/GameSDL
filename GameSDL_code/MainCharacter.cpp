#include "MainCharacter.h"

MainChar::MainChar() {
	x_pos = y_pos = x_val = y_val = 0;
	frame =  W_frame = H_frame = 0;
	status = -1;
	input_type.left = 0;
	input_type.right = 0;
	input_type.jump = 0;
	input_type.down = 0;
	input_type.up = 0;
	on_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	come_back_time = 0;
}
MainChar::~MainChar() { ; }

bool MainChar::loadImg(std::string path, SDL_Renderer* scr) {
	bool ret = BaseObject::loadImg(path, scr);
	if (ret == true) {
		W_frame = rect.w / CharFrame;
		H_frame = rect.h;
	}
	return ret;
}

void MainChar::set_clip() {
	if (W_frame > 0 && H_frame > 0) {
		for (int i = 0; i < CharFrame; ++i) {
			frame_clip[i].x = i*W_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = W_frame;
			frame_clip[i].h = H_frame;
		}
	}
}

void MainChar::Show(SDL_Renderer* des) {
	if (come_back_time == 0) {
		updateImg(des);
		if (input_type.left == 1 || input_type.right == 1) {
			frame++;
		}
		else {
			frame = 0;
		}
		if (frame >= 8) frame = 0;
		rect.x = x_pos - map_x_;
		rect.y = y_pos - map_y_;

		SDL_Rect* current_clip = &frame_clip[frame];
		SDL_Rect renderQuad = { rect.x, rect.y, W_frame, H_frame };

		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
	}
}

void MainChar::HandelInputAction(SDL_Event event, SDL_Renderer* scr) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_d:
			if (status != WALK_RIGHT) {
				status = WALK_RIGHT;
				updateImg(scr);
			}
			input_type.right = 1;
			input_type.left = 0;
			break;
		case SDLK_a:
			if (status != WALK_LEFT) {
				status = WALK_LEFT;
				updateImg(scr);
			}
			input_type.left = 1;
			input_type.right = 0;

			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_d:
			input_type.right = 0;
			break;
		case SDLK_a:
			input_type.left = 0;
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			input_type.jump = 1;
		}
		if (event.button.button == SDL_BUTTON_LEFT) {
			//create bullet
			BulletObject* p_bullet = new BulletObject;
			p_bullet->loadImg("img//player_bullet.png", scr);
			
			if (status == WALK_LEFT) {
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
				p_bullet->setRect(this->rect.x, this->rect.y + H_frame * 0.25);
			}
			else {
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->setRect(this->rect.x + W_frame - 20, this->rect.y + H_frame * 0.25);
			}
			
			p_bullet->set_x_val(BULLET_SPEED);
			p_bullet->set_y_val(BULLET_SPEED);
			p_bullet->set_is_move(true);
			
			//input to the list
			p_bullet_list.push_back(p_bullet);
		}
	}
}

void MainChar::HandleBullet(SDL_Renderer* des) {
	for (int i = 0; i < p_bullet_list.size(); ++i) {
		BulletObject* p_bullet = p_bullet_list.at(i);
		if (p_bullet != nullptr) {
			if (p_bullet->get_is_move() == true) {
				p_bullet->HandleMove(scr_w, scr_h);
				p_bullet->Render(des);
			}
			else {
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != nullptr) {
					delete p_bullet;
					p_bullet = nullptr;
				}
			}
		}
	}
}

void MainChar::DoPlayer(Map& map_data) {
	if (come_back_time == 0) {
		x_val = 0;
		y_val += GRAVITY;

		if (y_val >= MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;

		if (input_type.right == 1) {
			x_val += PLAYER_SPEED;
		}
		else if (input_type.left == 1) {
			x_val -= PLAYER_SPEED;
		}
		if (input_type.jump == 1) {
			if (on_ground == true) {
				y_val = -PLAYER_JUMP_HEIGHT;
			}
			on_ground = false;
			input_type.jump = 0;
		}
		CheckToMap(map_data);
		CenterEntityOnMap(map_data);
	}
	else {
		come_back_time--;
		if (come_back_time == 0) {
			on_ground = true;
			x_pos = 0;
			x_val = 0;
			y_pos = 0;
			y_val = 0;
		}
	}
}

void MainChar::CheckToMap(const Map& map_data) {
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	/*Object rect
	x1,y1-----------x2,y1
	|                 |
	|				  |
	|				  |
	|				  |
	x1,y2-----------x2,y2
	*/



	//check vertical
	int width_min = (W_frame < TILE_SIZE) ? W_frame : TILE_SIZE;

	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + H_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <MAX_MAP_Y) {
		if (y_val > 0) {
			if (map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0) {
				y_pos = y2 * TILE_SIZE;
				y_pos -= (H_frame + 1);
				y_val = 0;
				on_ground = true;
			}
		}
		else if (y_val < 0) {
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0) {
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}
	//check horizontal
	int height_min = (H_frame < TILE_SIZE) ? H_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + W_frame - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val > 0) { // object is moving to the right
			if (map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0) {
				x_pos = x2 * TILE_SIZE;
				x_pos -= (W_frame + 1);
				x_val = 0;
			}
		}
		else if (x_val < 0) {
			if (map_data.tile[y1][x1] != 0 || map_data.tile[y2][x1] != 0) {
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	}
	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0) {
		x_pos = 0;
	}
	if (x_pos + W_frame > map_data.max_x) {
		x_pos = map_data.max_x - W_frame - 1;
	}

	if(y_pos > map_data.max_y) {
		come_back_time = 60;
	}
}

void MainChar::updateImg(SDL_Renderer* des) {
	if (on_ground == true) {
		if (status == WALK_LEFT) {
			loadImg("img//player_left.png", des);
		}
		else if (status == WALK_RIGHT) {
			loadImg("img//player_right.png", des);
		}
	}
	else {
		if (status == WALK_LEFT) {
			loadImg("img//jum_left.png", des);
		}
		else if (status == WALK_RIGHT) {
			loadImg("img//jum_right.png", des);
		}
	}
}
void MainChar::CenterEntityOnMap(Map& map_data) {
	map_data.start_x = x_pos - (scr_w / 2);
	if (map_data.start_x < 0) {
		map_data.start_x = 0;
	}
	else if (map_data.start_x + scr_w >= map_data.max_x) {
		map_data.start_x = map_data.max_x - scr_w;
	}

	map_data.start_y = y_pos - (scr_h / 2);
	if (map_data.start_y < 0) {
		map_data.start_y = 0;
	}
	else if (map_data.start_y + scr_h >= map_data.max_y) {
		map_data.start_y = map_data.max_y - scr_h;
	}
}