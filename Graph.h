#pragma once
#include <vector>

#include "Text.h"
#include "Drawable.h"
class Graph : public Drawable
{
	std::vector<double> values;
	SDL_Rect base;
	Text number;
	bool isBaseLine;
	double baseLine;

	double max;
public:
	Graph(int x, int y, int w, int h, double baseline = 0, bool isBase = false);
	void Push(double a);
	void Draw(SDL_Renderer* renderer, TTF_Font* font = nullptr);
	void Reset();
};

