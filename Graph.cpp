#include "Graph.h"

#include <iostream>

Graph::Graph(int x, int y, int w, int h, double baseLine, bool isBase)
	: number(L"", x, y, 20, w, { 255, 255, 255, 255 }, { 0,0,0,0 }, { 0,0,0,0 })
{
	this->baseLine = baseLine;
	isBaseLine = isBase;
	base.x = x;
	base.y = y + 20;
	base.h = h - 20;
	base.w = w;
	for (int i = 0; i < w; i++)
		values.push_back(0);
	max = 0;
}

void Graph::Push(double a)
{
	
	values.push_back(a);
	double buf = values[0];
	values.erase(values.begin());
	if (a > max)
		max = a;
	else if (buf == max)
	{
		max = 0;
		for (int i = 0; i < values.size(); i++)
			if (values[i] > max)
				max = values[i];
		if (max < baseLine && isBaseLine)
			max = baseLine;
	}

}

void Graph::Draw(SDL_Renderer* renderer, TTF_Font* font)
{
	if (max == 0)
		return;
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	for (int i = 0; i < values.size(); i++)
	{
		SDL_RenderDrawLine(renderer, base.x + i, base.y + base.h, base.x + i, base.y + base.h - (int)((values[i] / max) * base.h + 0.5) - 1);
		//SDL_RenderDrawPoint(renderer, base.x + i, base.y + base.h - (values[i] / (double)max) * base.h);
		//SDL_RenderDrawLine(renderer, base.x + i, base.y, base.x + i, base.y + base.h);
	}
	if (isBaseLine)
	{
		SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
		SDL_RenderDrawLine(renderer, base.x, base.y + base.h - (int)((baseLine / max) * base.h + 0.5), base.x + base.w, base.y + base.h - (int)((baseLine / max) * base.h + 0.5));
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < values.size(); i++)
	{
		//SDL_RenderDrawLine(renderer, base.x + i, base.y + base.h, base.x + i, base.y + base.h - (int)((values[i] / max) * base.h + 0.5) - 1);
		SDL_RenderDrawPoint(renderer, base.x + i, base.y + base.h - (int)((values[i] / max) * base.h + 0.5));
		//SDL_RenderDrawLine(renderer, base.x + i, base.y, base.x + i, base.y + base.h);
	}
	number.SetText(max, 2);
	number.Draw(renderer, font);	
}

void Graph::Reset()
{
	values.clear();
	for (int i = 0; i < base.w; i++)
		values.push_back(0);
	max = 0;
}
