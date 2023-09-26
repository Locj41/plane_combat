#pragma once
#include"BaseObject.h"


#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

class AmoObject : public BaseObject
{
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int amo_type_;
public:
	enum AmoType
	{
		NONE = 0,
		LASER = 1,
		SPHERE = 2
	};


	AmoObject();
	~AmoObject();
	void handleInputAction(SDL_Event event);
	void handleMove(const int& x_border, const int& y_border);
	int get_type() const {
		return amo_type_;
	}
	void set_type(const int& type) {
		this->amo_type_ = type;
	}

	bool get_is_move() {
		return is_move_;
	}
	void set_is_move(bool is_move) {
		this->is_move_ = is_move;
	}

	void setWidthHeight(const int& height, const int& width) {
		rect_.w = width;
		rect_.h = height;
	}
	void handleMoveRightToLeft();
	void set_x_val_(const int& val) { x_val_ = val; }
	void set_y_val_(const int& val) { y_val_ = val; }
	int get_x_val_() const {
		return x_val_;
	}
	int get_y_val_() const {
		return y_val_;
	}

};

