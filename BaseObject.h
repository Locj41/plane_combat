#pragma once
#include<SDL.h>
#include"Common_Function.h"

class BaseObject {
protected:
	SDL_Rect rect_;
	SDL_Surface* p_object;
public:

	BaseObject();
	~BaseObject();
	void show(SDL_Surface* des);
	bool load(const char* file_name);
	void setRect(const int& x, const int& y) {
		this->rect_.x = x;
		this->rect_.y = y;
	};
	SDL_Rect getRect() const{
		return this->rect_;
	}
	SDL_Surface* getObject() {
		return this->p_object;
	}

};