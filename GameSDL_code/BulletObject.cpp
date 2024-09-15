#include "BulletObject.h"

BulletObject::BulletObject() {
	x_val = 0;
	y_val = 0;
	is_move = false;
}

BulletObject::~BulletObject() {

}

void BulletObject::HandleMove(const int& x_border, const int& y_border) {
	if (bullet_dir == DIR_RIGHT) {
		rect.x += x_val;
		if (rect.x > x_border) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_LEFT) {
		rect.x -= x_val;
		if (rect.x < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP) {
		rect.y -= y_val;
		if (rect.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN) {
		rect.y += y_val;
		if (rect.y > y_border) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_LEFT) {
		rect.x -= x_val;
		rect.y -= y_val;
		if (rect.x < 0 || rect.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_RIGHT) {
		rect.x += x_val;
		rect.y -= y_val;
		if (rect.x > x_border || rect.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN_LEFT){
		rect.x -= x_val;
		rect.y += y_val;
		if (rect.x < 0 || rect.y > y_border) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN_RIGHT) {
		rect.x += x_val;
		rect.y += y_val;
		if (rect.x > x_border || rect.y > y_border) {
			is_move = false;
		}
	}
}