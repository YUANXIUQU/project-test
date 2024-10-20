#include "spear.h"
#include <SDL.h>

spear::spear() :Sprite() {}

spear::spear(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h) :
	Sprite(_ren, _file, _x, _y, _w, _h)
{
	
}

void spear::update()
{
	position.y -= 5;
}