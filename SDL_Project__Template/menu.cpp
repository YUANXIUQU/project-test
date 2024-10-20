#include "menu.h"
#include "sprite.h"
#include "bkg.h"
#include <SDL.h>
#include <iostream>

menu::menu()
{
	initialize();
}

int menu::initialize()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("pause");
		return 0;
	}


	win = SDL_CreateWindow("menu", 100, 100, 1024, 600, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}


	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rend == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
}

menu::~menu()
{
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void menu::run(char* _file)
{
	SDL_Event e;
	bool running = true;
	const Uint8* key = SDL_GetKeyboardState(0);
	bkg* mbkg = new bkg(rend, _file, 0, 0, 1024, 600);

	while (running == true)
	{
		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
				running = false;
		}
		if (key[SDL_SCANCODE_1])
		{
			state = 1;
		    running = false;
		}
		else if (key[SDL_SCANCODE_2])
		{
			state = 2;
			running = false;
		}
		else if (key[SDL_SCANCODE_3])
		{
			state = 3;
			running = false;
		}

		SDL_RenderClear(rend);
		mbkg->Draw();
		SDL_RenderPresent(rend);
	}
	delete mbkg;
}