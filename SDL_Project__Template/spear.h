#pragma once

#ifndef _SPEAR_H_
#define _SPEAR_H_
#include "sprite.h"

class spear :public Sprite
{
public:
	spear();
	spear(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h);
	void update();
};

#endif