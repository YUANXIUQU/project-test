#include "player.h"
#include <SDL.h>

player::player() :Sprite() {}

player::player(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h) :
	Sprite(_ren, _file, _x, _y, _w, _h)
{

}

void player::update()
{
	const Uint8* key = SDL_GetKeyboardState(0);
	if (key[SDL_SCANCODE_A])
	{
		position.x -= 5;
	}
	if (key[SDL_SCANCODE_D])
	{
		position.x += 5;
	}
	if (GetX() <= 0)
	{
		SetX(1024 - GetW());
	}
	if (GetX() >= 1024)
	{
		SetX(0);
	}
}