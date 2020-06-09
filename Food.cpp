#include "Food.h"

#include <random>

Food::Food(int minX, int maxX, int minY, int maxY)
{
	x = minX + rand() % (maxX - minX);
	y = minY + rand() % (maxY - minY);
	energy = 50;
}

void Food::Draw(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Rect base;
	base.h = 10;
	base.w = 10;
	base.x = x - base.w / 2;
	base.y = y - base.h / 2;
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &base);
}

const int Food::getX()
{
	return x;
}

const int Food::getY()
{
	return y;
}

double Food::getEnergy()
{
	return energy;
}
