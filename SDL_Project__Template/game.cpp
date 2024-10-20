 #include <iostream>
#include <algorithm>
#include <SDL.h>
#include "Game.h"
#include "bkg.h"
#include "player.h"
#include "spear.h"
#include "fish.h"
#include "menu.h"
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include "text.h"
#include "animsprite.h"

Game::Game()
{
	initialize();
}


int Game::initialize()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("pause");
		return 0;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
		return false;
	}

	bkg_music = Mix_LoadMUS("bkg_s.wav");
	if (!bkg_music)
	{
		std::cout << "Error loading music: " << Mix_GetError() << std::endl;
		return false;
	}

	catch_sound = Mix_LoadWAV("catch.wav");
	if (!catch_sound)
	{
		std::cout << "Error loading sound: " << Mix_GetError() << std::endl;
		return false;
	}

	miss_sound = Mix_LoadWAV("lose_live.wav");
	if (!miss_sound)
	{
		std::cout << "Error loading sound: " << Mix_GetError() << std::endl;
		return false;
	}

	Mix_PlayMusic(bkg_music, -1);

	if (TTF_Init() < 0)
	{
		std::cout << "Error initializing SDL_ttf: "
			<< TTF_GetError() << std::endl;
	}

	window = SDL_CreateWindow("fishing", 100, 100, 1024, 600, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}


	font = TTF_OpenFont("arial.ttf", 24);
	if (!font)
	{
		std::cout << "Failed to load font:"
			<< TTF_GetError() << std::endl;
	}
	
	return true;  
}

Game::~Game()
{
	Mix_FreeMusic(bkg_music);
	Mix_FreeChunk(miss_sound);
	Mix_FreeChunk(catch_sound);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}


void Game::GameLoop()
{
	bool running = true;
	SDL_Event e;

	//create game objects
	bkg* ocean = new bkg(renderer, (char*)"bkg.bmp", 0, 0, 1024, 600);
	player* gun = new player(renderer, (char*)"gun.png", 487, 400, 100, 200);
	fish* fishes = new fish(renderer, (char*)"fish.png", 100, 50);
	std::vector<spear*> spears;
	std::vector<animsprite*> bubble;
	const Uint8* key = SDL_GetKeyboardState(NULL);
	int fireTimer = 0;
	bool game_over = false;
	fishes->Setlives(10);
	
	
	
	while (running == true)
	{
		float start = SDL_GetTicks();
		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_QUIT)
				running = false;
		}
		SDL_RenderClear(renderer);

		//update fish ,gun, spear,animation 
		fishes->update(spears, renderer, (char*)"fish.png", 100, 50, catch_sound,miss_sound);
		gun->update();
		fireTimer--;
		if (fireTimer<0 && key[SDL_SCANCODE_SPACE])
		{
			fireTimer = 10;
			spears.push_back(new spear(renderer, (char*)"s.png", gun->GetX()+(gun->GetW()/2), gun->GetY() - 70, 50, 70));
		}
		for (int i = 0;i < spears.size();i++)
		{
			spears[i]->update();
			if (spears[i]->Getresult()) //spears truely collides with fish
			{
				bubble.push_back(new animsprite(renderer, (char*)"bubble.png", spears[i]->GetX()-50, spears[i]->GetY()-50,
					141, 133, 3, 3, 5));
			}
			if (spears[i]->Getresult() || spears[i]->GetY() < -70)  //the spear truely collides with fish or is outside of screen so it can be deleted
			{
				spears.erase(spears.begin()+i);
			}
			
		}


		for (int c = 0;c < bubble.size(); c++)
		{
			bubble[c]->update();
			if (bubble[c]->Getresult() == true)
			{
				delete bubble[c];
				bubble.erase(bubble.begin() + c);
			}
		}

		//create text for lives and score display
		std::string t = "lives: " + std::to_string(fishes->Getlives());
		text* lives = new text(renderer, font, t, 1024 - 200,0, 100, 50);
		std::string score = "scores: " + std::to_string(fishes->Getscores());
		text* scores = new text(renderer, font, score, 1024 - 200, 50, 110, 50);

		//draw part
		ocean->Draw();
		fishes->draw();
		gun->Draw();
		lives->draw();
		scores->draw();
		for (int c = 0;c < spears.size();c++)
		{
			spears[c]->Draw();
		}
		for (int c = 0;c < bubble.size(); c++)
		{
			bubble[c]->Draw();
		}

		if (fishes->Getlives() <= 0)
		{
			std::string score_d = "total scores: " + std::to_string(fishes->Getscores()) +
				"  well done !!!";
			text* final_scores = new text(renderer, font, score_d, 512 - 300, 200, 600, 80);
			final_scores->draw();
			game_over = true;
		}

		SDL_RenderPresent(renderer);

		if (game_over == true)
		{
			SDL_Delay(3000);
			running = false;
		}

		//frame rate control
		float elapsedms = SDL_GetTicks() - start;
		if (elapsedms < 16.667)
		{
			SDL_Delay(16.667 - elapsedms);
		}
		
	}
	delete ocean;
	delete gun;
	for (int c = 0;c < spears.size();c++)
	{
		delete spears[c];
	}
	delete fishes;
	for (int c = 0;c < bubble.size();c++)
	{
		delete bubble[c];
	}
}