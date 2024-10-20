#include<SDL.h>
#include "bkg.h"

bkg::bkg() : Sprite() {}

bkg::bkg(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h) :
	Sprite(_ren, _file, _x, _y, _w, _h)
{

}