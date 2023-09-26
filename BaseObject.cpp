#include"BaseObject.h"
#include"Common_Function.h"


BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object = NULL;
}

BaseObject::~BaseObject() {
	if (p_object != NULL) {
		SDL_FreeSurface(p_object);
	}
}

bool BaseObject::load(const char* file_path) {
	p_object = SDLCommonFunc::LoadImage(file_path);
	if (p_object == NULL) {
		return false;
	}
	return true;
}


void BaseObject::show(SDL_Surface* des) {
	if (p_object != NULL) {
		SDLCommonFunc::ApplySurface(p_object, des, rect_.x, rect_.y);

	}
}