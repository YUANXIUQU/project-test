#include "text.h"

text::text(){}
text::text(SDL_Renderer* _ren,TTF_Font* font,
	const std::string& _t, int _x, int _y, int _w, int _h)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, _t.c_str(), {255,255,255});
	texture = SDL_CreateTextureFromSurface(_ren, surface);
	SDL_FreeSurface(surface);
	position.x = _x;
	position.y = _y;
	position.w = _w;
	position.h = _h;
	rend = _ren;
}
text::~text()
{
	delete texture;
}

void text::draw()
{
	SDL_RenderCopy(rend, texture, nullptr, &position);
}