#pragma once
#ifndef _MENU_H_
#define _MENU_H_
#include "sprite.h"

class menu
{
protected:
	SDL_Window* win;
	SDL_Renderer* rend;
	int initialize();
	int state;
public:
	menu();
	void run(char* _file);
	int getstate() { return state; }
	~menu();	
};
#endif