#pragma once
#include "Drawable.h"
class Food : public Drawable
{
	int x, y;
	double energy;
public:
	Food(int minX, int maxX, int minY, int maxY);
	void Draw(SDL_Renderer* renderer, TTF_Font* font = nullptr);
	const int getX();
	const int getY();
	double getEnergy();
};

