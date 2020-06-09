#include "Text.h"
#include <Windows.h>
#include <iostream>


Text::Text(int value, int x0, int y0, int h, int w, SDL_Color letters, SDL_Color background, SDL_Color border)
{
	texture = nullptr;
	this->SetText(value);	
	base.x = x0;
	base.y = y0;
	base.h = h;
	base.w = w;
	this->letters_color = letters;
	this->background_color = background;
	this->border_color = border;
}

Text::Text(std::wstring str, int x0, int y0, int h, int w, SDL_Color letters, SDL_Color background, SDL_Color border)
{
	texture = nullptr;
	text = str;
	base.x = x0;
	base.y = y0;
	base.h = h;
	base.w = w;
	this->letters_color = letters;
	this->background_color = background;
	this->border_color = border;	
}

Text::Text(const Text& other)
{
	*this = other;
	texture = nullptr;
}

void Text::Draw(SDL_Renderer* renderer, TTF_Font* font)
{
	SDL_Rect dest;
	int w, h;
	double k;
	if (!texture && font)
	{
		SDL_Surface* buf = TTF_RenderUNICODE_Blended(font, (Uint16*)text.c_str(), letters_color);
		if (buf)
		{
			texture = SDL_CreateTextureFromSurface(renderer, buf);
			SDL_FreeSurface(buf);
			
		}
	}
	if (texture)
	{
		if (background_color.a)
		{
			SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 255);
			SDL_RenderFillRect(renderer, &base);
		}
		if (border_color.a)
		{
			SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, 255);
			SDL_RenderDrawRect(renderer, &base);
		}
		TTF_SizeUNICODE(font, (Uint16*)text.c_str(), &w, &h);
		k = base.h / (double)h;
		dest.h = (int)(h * k + 0.5);
		dest.w = (int)(w * k + 0.5);
		dest.x = base.x - (dest.w - base.w) / 2;
		dest.y = base.y;
		SDL_RenderCopy(renderer, texture, NULL, &dest);
		SDL_RenderDrawPoint(renderer, -1, 0);
	}
}

void Text::SetText(int a)
{
	text.clear();
	do
	{
		text.push_back(((Uint16)L'0' + (Uint16)a % 10));
		a /= 10;
	} while (a > 0);
	Uint16 buf;
	for (unsigned int i = 0; i < text.size() / 2; i++)
	{
		buf = text[i];
		text[i] = text[text.size() - 1 - i];
		text[text.size() - 1 - i] = buf;
	}
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::SetText(double a, int len)
{
	a += 0.00000000005;
	std::wstring prev = text;
	text.clear();
	int val = (int)a;
	do
	{
		text.push_back(L'0' + val % 10);
		val /= 10;
	} while (val != 0);
	Uint16 buf;
	for (unsigned int i = 0; i < text.size() / 2; i++)
	{
		buf = text[i];
		text[i] = text[text.size() - 1 - i];
		text[text.size() - 1 - i] = buf;
	}
	text.push_back(L'.');
	a -= (int)a;
	for (int i = 0; i < len; i++)
	{
		text.push_back(L'0' + (int)(a * 10));
		a *= 10;
		a -= (int)a;
	}
	if (texture && prev != text)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::SetText(const wchar_t* val)
{
	std::wstring buf = text;
	text = val;
	if (text != buf && texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::DeInit()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

Text::~Text()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}
