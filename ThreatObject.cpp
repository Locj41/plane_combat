#include "ThreatObject.h"



ThreatObject::ThreatObject() {
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT / 2;
	rect_.w = THREAT_WIDTH;
	rect_.h = THREAT_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject() {
	if (p_amo_list.size() > 0) {
		for (int i = 0; i < p_amo_list.size(); i++) {
			AmoObject* p_amo = p_amo_list.at(i);
			if (p_amo) {
				delete p_amo;
				p_amo = NULL;
			}
		}
	}
}

void ThreatObject::handleMove(const int& x_border, const int& y_border) {
	rect_.x -= x_val_;
	if ((rect_.x + rect_.w) <= 0) {
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - 200) {
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		rect_.y = rand_y;
	}
	
}

void ThreatObject::hanldInputAction(SDL_Event event) {
	;
}

void ThreatObject::initAmo(AmoObject* amo) {
	if (amo) {
		bool ret = amo->load("sphere1.png");
			if (ret) {
				amo->set_is_move(true);
				amo->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
				amo->set_type(AmoObject::AmoType::SPHERE);
				amo->setRect(rect_.x, rect_.y + rect_.h * 0.5);
				p_amo_list.push_back(amo);
			}
	}
}

void ThreatObject::makeAmo( const int& x_limit, const int& y_limit) {
	for (int i = 0; i < p_amo_list.size(); i++) {
		AmoObject* p_amo = p_amo_list.at(i);
		p_amo->set_x_val_(8);
		if (p_amo) {
			if (p_amo->get_is_move()) {
				if (this->rect_.x <= SCREEN_WIDTH) {
					p_amo->show(g_screen);
				}
				p_amo->handleMoveRightToLeft();
			}
			else {
				p_amo->setRect(rect_.x, rect_.y + rect_.h * 0.5);
				p_amo->set_is_move(true);
			}
		}
	}
}

void ThreatObject::resetThreat() {
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - 200) {
		rand_y = SCREEN_HEIGHT * 0.3;
	}
	this->setRect(SCREEN_WIDTH, rand_y);
	for (int i = 0; i < p_amo_list.size(); i++) {
		p_amo_list[i]->set_is_move(false);
	}
}