#pragma once
#include"BaseObject.h"
#include"Common_Function.h"
#include <vector>
#include"AmoObject.h"


#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52


class MainObject : public BaseObject {
private:
	int m_x;
	int m_y;
	std::vector<AmoObject*> p_amo_list;
public:
	MainObject();
	~MainObject();

	void setAmoList(std::vector<AmoObject*> amo_list) {
		this->p_amo_list = amo_list;
	}
	std::vector<AmoObject*> getAmoList() {
		return p_amo_list;
	}
	void handleMove();
	void handleInputAction(SDL_Event event);
	void Fire();
	void removeAmo(const int& index);
};

