#pragma once
#ifndef _BKG_H_
#define _BKG_H_
#include "sprite.h"

class bkg :public Sprite
{
public:
	bkg();
	bkg(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h);
};
#endif 
