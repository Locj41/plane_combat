#include "AmoObject.h"

AmoObject::AmoObject(){
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	amo_type_ = AmoObject::AmoType::NONE;
}

AmoObject::~AmoObject() {
	;
}

void AmoObject::handleInputAction(SDL_Event event) {
	;
}

void AmoObject::handleMove(const int& x_border, const int& y_border) {
	rect_.x += x_val_;
	if (rect_.x > x_border) {
		is_move_ = false;
	}
}

void AmoObject::handleMoveRightToLeft() {
	rect_.x -= x_val_;
	if (rect_.x + rect_.w <= 0) {
		is_move_ = false;
	}
}

