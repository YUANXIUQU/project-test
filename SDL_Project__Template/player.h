#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "sprite.h"


class player :public Sprite
{
public:
	player();
	player(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h);
	void update();
};

#endif