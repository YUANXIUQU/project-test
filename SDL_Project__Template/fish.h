#pragma once
#ifndef _FISH_h_
#define _FISH_H_
#include <SDL.h>
#include <vector>
#include <iostream>
#include "Sprite.h"
#include "spear.h"
#include <SDL_mixer.h>
class fish
{
public:
	fish();
	fish(SDL_Renderer* _renderer, char* _imagefile, int _w, int _h);
	~fish();
	void update(std::vector<spear*>& _spears, SDL_Renderer* _ren, char* _image, int _w, int _h,
	Mix_Chunk* catch_sound,Mix_Chunk* miss_sound);
	void draw();
	void Setlives(int _lives) { lives = _lives; }
	int Getlives() { return lives; }
	int Getscores() { return scores; }
protected:
	std::vector<Sprite*> images;
	std::vector<int> speeds;
	int scores;
	int lives;
	int delay;
	int speed;
	int number;
	int x;
	int y;
	
	
};
#endif