#include <SDL.h>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "menu.h"


int main(int, char**)
{
	
	bool running = true;
	while (running == true)
	{
		menu* m = new menu();
		m->run((char*)"menu.png"); 
		if (m->getstate() == 1)
		{
			delete m; //whatever choices player made,it will firstly delete menu page
			Game* myGame = new Game();
			myGame->GameLoop();
			delete myGame;
		}
		else if (m->getstate() == 3)
		{
			delete m;
			menu* i = new menu();
			i->run((char*)"instruc.png");
			if (i->getstate() == 1)
			{
				delete i;
			}
		}
		else if (m->getstate() == 2)
		{
			delete m;
			running = false;
		}
	}
	
	return 0;
}  