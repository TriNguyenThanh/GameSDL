#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "function.h"
#include "Base_Object.h"

class BulletObject :public BaseObject {
public:
	BulletObject();
	~BulletObject();

	enum BulletDir {
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP = 22,
		DIR_UP_LEFT = 23,
		DIR_UP_RIGHT = 24,
		DIR_DOWN_LEFT = 25,
		DIR_DOWN_RIGHT = 26,
		DIR_DOWN = 27,
	};

	void set_x_val(const int& x) { x_val = x; }
	void set_y_val(const int& y) { y_val = y; }
	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val; }

	void set_bullet_dir(const int& bulletDir) { bullet_dir = bulletDir; }
	int get_bullet_dir() const { return bullet_dir; }

	void set_is_move(const bool& isMove) { is_move = isMove; }
	bool get_is_move() const { return is_move; }
	void HandleMove(const int& x_border, const int& y_border);
private:
	int x_val, y_val;
	bool is_move;

	int bullet_dir;
};

#endif // !BULLET_OBJECT_H_
