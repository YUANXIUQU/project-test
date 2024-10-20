#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Mix_Music* bkg_music;
	Mix_Chunk* catch_sound;
	Mix_Chunk* miss_sound;
	TTF_Font* font;
	int initialize();
public:
	Game();
	~Game();
	void GameLoop();

};
#endif