#include "Sprite.h"
#include <SDL.h>
#include <SDL_image.h>


Sprite::Sprite() {}

Sprite::Sprite(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h)
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	SDL_Surface* File = IMG_Load(_file);
	image = SDL_CreateTextureFromSurface(_ren, File);
	SDL_FreeSurface(File);

	canbedestroyed = false;
	position.x = _x;
	position.y = _y;
	position.w = _w;
	position.h = _h;

	renderer = _ren;
}

Sprite::~Sprite()
{
	if (image)
		SDL_DestroyTexture(image);
}

void Sprite::Draw()
{
	if (image)
		SDL_RenderCopy(renderer, image, NULL, &position);
}

bool Sprite::IfCollide(Sprite* other)
{
	return SDL_HasIntersection(&position, &other->position);
}