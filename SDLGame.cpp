#include"Common_Function.h"
#include"MainObject.h"
#include"ThreatObject.h"
#include "ExplosionObject.h"

SDL_Surface* g_object = NULL;
SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event g_event;
Mix_Chunk* g_sound_bullet[2];
Mix_Chunk* g_sound_exp[2];


bool Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL) {
		return false;
	}
	if (Mix_OpenAudio(20000, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}
	//read audio file
	g_sound_bullet[0] = Mix_LoadWAV("machinegun.wav");
	g_sound_bullet[1] = Mix_LoadWAV("fireball.wav");
	g_sound_exp[0] = Mix_LoadWAV("af.wav");
	g_sound_exp[1] = Mix_LoadWAV("explosion.wav");
	if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL) {
		return false;
	}
	return true;
}


int main(int args, char* argv[]) {
	int bkgn_x = 0;

	bool is_run_screen = true;
	bool is_quit = false;
	if (Init() == false) {
		return 0;
	}
	//make backgroung
	g_background = SDLCommonFunc::LoadImage("bg4800.png");
	if (g_background == NULL) {
		return 0;
	}
	
	//make plane
	MainObject* plane_object = new MainObject();
	plane_object->setRect(100, 200);
	bool relsut = plane_object->load("plane_fly.png");
	if (!relsut) {
		return 0;
	}

	//init explosion
	ExplosionObject* exp_main = new ExplosionObject();
	bool ret = exp_main->load("exp_main.png");
	if (!ret) {	
		return 0;
	}
	exp_main->setClips();

	//make threat
	ThreatObject* p_threats = new ThreatObject[NUM_THREAT];
	for (int t = 0; t < NUM_THREAT; t++) {
		ThreatObject* p_threat = (p_threats + t);
		bool ret = p_threat->load("af1.png");
		if (!ret) {
			return 0;
		}
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - 200) {
			rand_y = SCREEN_HEIGHT * 0.3;
		}
		p_threat->setRect(SCREEN_WIDTH + t * 300, rand_y);
		p_threat->set_x_val_(2.5);

		//make amo for threat
		AmoObject* sphere_amo = new AmoObject();
		p_threat->initAmo(sphere_amo);
	}


	while (!is_quit) {
		//apply background
		//cach 1:
		/*bkgn_x -= 1;
		SDLCommonFunc::ApplySurface(g_background, g_screen, bkgn_x, 0);
		SDLCommonFunc::ApplySurface(g_background, g_screen, bkgn_x + SCREEN_WIDTH, 0);
		if (bkgn_x <= -SCREEN_WIDTH) {
			bkgn_x = 0;
		}*/
		/*SDLCommonFunc::ApplySurface(g_background, g_screen, 0, 0);*/

		if (is_run_screen) {
			bkgn_x -= 1;
			if (bkgn_x <= -(BACKGROUND_WIDTH - SCREEN_WIDTH)) {
				is_run_screen = false;
			}
			else
			{
				SDLCommonFunc::ApplySurface(g_background, g_screen,bkgn_x, 0);
			}
		}
		else {
			SDLCommonFunc::ApplySurface(g_background, g_screen, bkgn_x, 0);
		}

		while (SDL_PollEvent(&g_event)) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
			plane_object->handleInputAction(g_event, g_sound_bullet);
		}
			plane_object->handleMove();	
			plane_object->show(g_screen);
			plane_object->Fire();

			//run threat
			for (int i = 0; i < NUM_THREAT; i++) {
				p_threats[i].handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threats[i].show(g_screen);
				p_threats[i].makeAmo(SCREEN_WIDTH, SCREEN_HEIGHT);
				//check collision plane vs ally plane
				bool is_collision_crash = SDLCommonFunc::checkCollision(plane_object->getRect(),
					p_threats[i].getRect());

				//bullet of ally plane vs plane
				std::vector<AmoObject*> th_amo_list = p_threats[i].getAmoList();
				for (int t_amo = 0; t_amo < th_amo_list.size(); t_amo++) {
					AmoObject* th_amo = th_amo_list.at(t_amo);
					if (th_amo) {
						bool is_collision = SDLCommonFunc::checkCollision(
							th_amo->getRect(), plane_object->getRect()
						);
						if (is_collision || is_collision_crash) {
							for (int ex = 0; ex < 4; ex++) {
								int x_pos = (plane_object->getRect().x + plane_object->getRect().w * 0.5)
									- EXP_WIDTH * 0.5;
								int y_pos = (plane_object->getRect().y + plane_object->getRect().h * 0.5)
									- EXP_HEIGHT * 0.5;
								exp_main->setFame(ex);
								exp_main->setRect(x_pos, y_pos);
								exp_main->showExplosion();
								Mix_PlayChannel(-1, g_sound_exp[1], 0);
								SDL_Delay(10);
								if (SDL_Flip(g_screen) == -1) {
									return 0;
								}
							}
							if (MessageBox(NULL, L"Game Over!", L"Info", MB_OK)) {
								SDLCommonFunc::CleanUp();
								delete plane_object;
								delete[] p_threats;
								delete exp_main;
								exp_main = NULL;
								plane_object = NULL;
								p_threats = NULL;
								SDL_Quit();
								return 0;
							};
						}
					}
				}
				//bullet of plane vs ally plane
				std::vector<AmoObject*> amo_list = plane_object->getAmoList();
					for (int amo = 0; amo < amo_list.size(); amo++) {
						AmoObject* p_amo = amo_list.at(amo);
						if (p_amo) {
							bool is_coll = SDLCommonFunc::checkCollision(amo_list[amo]->getRect(),
								p_threats[i].getRect());
							if (is_coll) {
								for (int ex = 0; ex < 4; ex++) {
									int x_pos = (p_threats[i].getRect().x + p_threats[i].getRect().w * 0.5)
										- EXP_WIDTH * 0.5;
									int y_pos = (p_threats[i].getRect().y + p_threats[i].getRect().h * 0.5)
										- EXP_HEIGHT * 0.5;
									exp_main->setFame(ex);
									exp_main->setRect(x_pos, y_pos);
									exp_main->showExplosion();
								}
								//xoa amo
								plane_object->removeAmo(amo);
								Mix_PlayChannel(-1, g_sound_exp[0], 0);
								//dua threat ve vi tri ban dau
								p_threats[i].resetThreat();
							}
						}
					}
				}					
			if (SDL_Flip(g_screen) == -1) {
				return 0;
			}		
	}

	SDLCommonFunc::CleanUp();
	delete exp_main;
	delete plane_object;
	delete[] p_threats;
	exp_main = NULL;
	plane_object = NULL;
	p_threats = NULL;
	SDL_Quit();



	return 0;
}

