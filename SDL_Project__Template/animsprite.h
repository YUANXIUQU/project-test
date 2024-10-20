#pragma once
#ifndef _ANIMATE_SPRITE_H_
#define _ANIMATE_SPRITE_H_

#include <SDL.h>
#include "Sprite.h"
class animsprite : public Sprite
{
public:
	animsprite();
	animsprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h,
		int _cellsPerRow, int _cellsPerCol, int _speed);
	void update();
	void Draw();

private:
	int cellsInRow;
	int cellsInCol;
	int currentRow;
	int currentCol;
	SDL_Rect cellRect;
	int timer;
	int speed;
	bool loop;
};

#endif