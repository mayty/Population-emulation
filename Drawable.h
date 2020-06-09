#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Drawable
{
public:
	virtual void Draw(SDL_Renderer* renderer, TTF_Font* font = nullptr) = 0;
};

