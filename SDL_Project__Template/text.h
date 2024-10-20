#ifndef _TEXT_H_
#define _TEXT_H_
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <iostream>
class text
{
public:
	text();
	text(SDL_Renderer* _ren, TTF_Font* font,
		const std::string& _t, int _x, int _y, int _w, int _h);
	~text();
	void draw();
private:
	SDL_Rect position;
	SDL_Renderer* rend;
	SDL_Texture* texture;
};



#endif