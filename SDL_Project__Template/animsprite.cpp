#include "animsprite.h"

animsprite::animsprite():Sprite(){}


animsprite::animsprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h,
	int _cellsInRow, int _cellsInCol, int _speed):
	Sprite(_renderer, _file, _x, _y, _w, _h)
{
	cellsInRow = _cellsInRow;
	cellsInCol = _cellsInCol;

	currentRow = 0;
	currentCol = 0;

	cellRect.x = 0;
	cellRect.y = 0;
	cellRect.w = _w;
	cellRect.h = _h;

	timer = 0;
	speed = _speed;
}


void animsprite::update()
{
	timer++;
	if (timer >= speed)
	{
		timer = 0;
		currentCol++;
		if (currentCol > cellsInRow - 1)
		{
			currentCol = 0;
			currentRow++;
			if (currentRow > cellsInRow - 1)
			{
				currentRow = 0;
				canbedestroyed = true;
			}
		}
	}
}

void animsprite::Draw()
{
	cellRect.x = currentCol * cellRect.w;
	cellRect.y = currentRow * cellRect.h;
	SDL_RenderCopy(renderer, image, &cellRect, &position);
}