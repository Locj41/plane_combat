#include "MainObject.h"



MainObject::MainObject() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	m_x = 0;
	m_y = 0;
}

MainObject::~MainObject() {
	;
}

void MainObject::handleInputAction(SDL_Event event, Mix_Chunk* bullet_sound[2]) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			m_y -= HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_DOWN:
			m_y += HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_LEFT:
			m_x -= WIDTH_MAIN_OBJECT / 4;
			break;
		case SDLK_RIGHT:
			m_x += WIDTH_MAIN_OBJECT / 4;
			break;

		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			m_y += HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_DOWN:
			m_y -= HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_LEFT:
			m_x += WIDTH_MAIN_OBJECT / 4;
			break;
		case SDLK_RIGHT:
			m_x -= WIDTH_MAIN_OBJECT / 4;
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		AmoObject* p_amo = new AmoObject();
		if (event.button.button == SDL_BUTTON_LEFT) {
			p_amo->setWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->load("laser.png");
			p_amo->set_type(AmoObject::AmoType::LASER);
			Mix_PlayChannel(-1, bullet_sound[0],0);
		}
		else if (event.button.button == SDL_BUTTON_RIGHT) {
			p_amo->setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->load("sphere.png");
			p_amo->set_type(AmoObject::AmoType::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}

		p_amo->setRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this->rect_.h*0.5 + 10);
		p_amo->set_is_move(true);
		p_amo->set_x_val_(20);
		p_amo_list.push_back(p_amo);
	}
	else if (event.type == SDL_MOUSEBUTTONUP) {
		;
	}
}

void MainObject::handleMove() {
	rect_.x += m_x;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH) {
		rect_.x -= m_x;
	}

	rect_.y += m_y;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200) {
		rect_.y -= m_y;
	}
}

void MainObject::Fire() {
	for (int i = 0; i < p_amo_list.size(); i++) {
		AmoObject* amo = p_amo_list.at(i);
		if (amo != NULL) {
			if (amo->get_is_move()) {
				amo->show(g_screen);
				amo->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				p_amo_list.erase(p_amo_list.begin() + i);
				delete amo;
				amo = NULL;
			}
		}
	}
}

void MainObject::removeAmo(const int& index) {
	p_amo_list.at(index)->set_is_move(false);
}