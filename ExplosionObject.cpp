#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {
	;
}

ExplosionObject::~ExplosionObject() {
	;
}

void ExplosionObject::setClips() {
	clips_[0].x = 0;
	clips_[0].y = 0;
	clips_[0].w = EXP_WIDTH;
	clips_[0].h = EXP_HEIGHT;

	clips_[1].x = EXP_WIDTH;
	clips_[1].y = 0;
	clips_[1].w = EXP_WIDTH;
	clips_[1].h = EXP_HEIGHT;

	clips_[2].x = EXP_WIDTH * 2;
	clips_[2].y = 0;
	clips_[2].w = EXP_WIDTH;
	clips_[2].h = EXP_HEIGHT;

	clips_[3].x = EXP_WIDTH * 3;
	clips_[3].y = 0;
	clips_[3].w = EXP_WIDTH;
	clips_[3].h = EXP_HEIGHT;
}

void ExplosionObject::showExplosion() {
	if (frame_ >= 4) {
		frame_ = 0;
	}
	SDLCommonFunc::ApplySurfaceClips(this->p_object, g_screen, (clips_ + frame_), rect_.x, rect_.y);
}

