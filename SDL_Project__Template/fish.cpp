#include "fish.h"
#include "sprite.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "SDL_main.h"
fish::fish(){}

fish::fish(SDL_Renderer* _ren, char* _image, int _w, int _h)
{
	//spawn fish at random speeds and number (less than or equal to 5)
	x = 0;
	scores = 0;
	srand(time(NULL));
	number = 1 + rand() % 5;
	lives = 10;
	for (int i = 0;i < number;i++)
	{
		y = rand() % 300;
		images.push_back(new Sprite(_ren, _image, 0, y, _w, _h));
		speed = 1 + rand() % 5;
		speeds.push_back(speed);
	}
}

fish::~fish() 
{ 
	for (int i = 0;i < images.size();i++)
	{
		delete images[i];
	}
	
}

void fish::update(std::vector<spear*>& _spears, SDL_Renderer* _ren, char* _image, int _w, int _h,
Mix_Chunk* catch_sound, Mix_Chunk* miss_sound)
{
	for (int i = 0;i < images.size();i++) // player lose live when fish escape
	{
		images[i]->SetX(speeds[i]+images[i]->GetX());
		if (images[i]->GetX() > 1024)
		{
			images[i]->SetX(0);          //fish escaped will start swimming from left again 
			Mix_PlayChannel(-1, miss_sound, 0);
			lives--;
		}

		for (int c = 0; c < _spears.size(); c++) //check for collision for deleting fish images and counting scores
		{
			if (images[i]->IfCollide(_spears[c]) == true)
			{
				images[i] = nullptr;
				images.erase(std::remove(images.begin(), images.end(), nullptr), images.end());
				speeds.erase(speeds.begin() + i);
				scores += 1;
				_spears[c]->Setresult(true);
				Mix_PlayChannel(-1, catch_sound, 0);
				break;
			}
		}
		
	}

	for (int c = 0; c < _spears.size();c++) // player lose live when misses a shot (when spear is completely outside of screen)
	{
		if (_spears[c]->GetY() <= -70)
		{
			Mix_PlayChannel(-1, miss_sound, 0);
			lives--;
		}
	}

	if (images.size() == 0) //respawn fish when one group of fish are killed 
	{
		delay -= 1;
		if (delay < 0)
		{
			x = 0;
			srand(time(NULL));
			number = 1 + rand() % 5;

			for (int i = 0;i < number;i++)
			{
				y = rand() % 300;
				images.push_back(new Sprite(_ren, _image, 0, y, _w, _h));
				speed = 1 + rand() % 5;
				speeds.push_back(speed);
			}
		}
	}
	else
	{
		delay = 100;
	}
	
}

void fish::draw()
{
	for (int i = 0;i < images.size();i++)
	{
		images[i]->Draw();
	}
}