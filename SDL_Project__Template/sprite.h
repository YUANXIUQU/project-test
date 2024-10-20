#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>



class Sprite
{
public:

	Sprite();
	Sprite(SDL_Renderer* _ren, char* _file, int _x, int _y, int _w, int _h); // constructor
	~Sprite();

	void SetX(int _x) { position.x = _x; }
	void SetY(int _y) { position.y = _y; }

	int GetX() { return position.x; }
	int GetY() { return position.y; }
	int GetW() { return position.w; }
	int GetH() { return position.h; }
	void Setresult(bool _test) {canbedestroyed = _test;}
	bool Getresult() { return canbedestroyed;}

	virtual void Draw();
	bool IfCollide(Sprite* other);
protected:
	SDL_Renderer* renderer;
	SDL_Rect position;
	SDL_Texture* image;
	bool canbedestroyed;
};

#endif
