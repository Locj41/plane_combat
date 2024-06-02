#pragma once

#include<Windows.h>
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#undef main

extern SDL_Surface* g_object;
extern SDL_Surface* g_screen;
extern SDL_Surface* g_background;
extern SDL_Event g_event;
extern Mix_Chunk* g_sound_bullet[2];
extern Mix_Chunk* g_sound_exp[2];


const int BACKGROUND_WIDTH = 4800;
const int BACKGROUND_HEIGHT = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREAT = 3;



namespace SDLCommonFunc {
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
	bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);	
	void ApplySurfaceClips(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
}

