#include "Button.h"

void Button::Draw(SDL_Renderer* renderer, TTF_Font* font)
{
	if (isActive)
		SDL_SetRenderDrawColor(renderer, (Uint8)(background.r * activeK + 0.5), (Uint8)(background.g * activeK + 0.5), (Uint8)(background.b * activeK + 0.5), 255);
	else
		SDL_SetRenderDrawColor(renderer, (Uint8)(background.r * idleK + 0.5), (Uint8)(background.g * idleK + 0.5), (Uint8)(background.b * idleK + 0.5), 255);
	SDL_RenderFillRect(renderer, &base);
	if (border.a)
	{
		SDL_SetRenderDrawColor(renderer, border.r, border.g, border.b, 255);
		SDL_RenderDrawRect(renderer, &base);
	}
	if (!texture)
	{
		if (font)
		{
			int w, h;
			SDL_Surface* buf = TTF_RenderUNICODE_Blended(font, (Uint16*)text.c_str(), letters);
			texture = SDL_CreateTextureFromSurface(renderer, buf);
			SDL_FreeSurface(buf);
			TTF_SizeUNICODE(font, (Uint16*)text.c_str(), &w, &h);
			double k = base.h / (double)h;
			dest.h = (int)(h * k + 0.5);
			dest.w = (int)(w * k + 0.5);
			dest.x = base.x - (dest.w - base.w) / 2;
			dest.y = base.y - (dest.h - base.h) / 2;
		}
	}
	if (texture)
	{
		SDL_RenderCopy(renderer, texture, NULL, &dest);
		SDL_RenderDrawPoint(renderer, -1, 0);
	}
}

int Button::CheckCollision(int x, int y, bool pressed)
{
	if (x < base.x || x > base.x + base.w)
	{
		isActive = false;
		return 0;
	}
	if (y < base.y || y > base.y + base.h)
	{
		isActive = false;
		return 0;
	}
	isActive = true;
	if (pressed)
		return OnClickEvent();
	else
		return 0;
}

Button::~Button()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}