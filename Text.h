#pragma once
#include "Drawable.h"
#include <string>
class Text :
	public Drawable
{
	SDL_Texture* texture;
	SDL_Color letters_color;
	SDL_Color background_color;
	SDL_Color border_color;
	SDL_Rect base;
	std::wstring text;
public:
	Text(int value, int x0, int y0, int h, int w, SDL_Color letters, SDL_Color background, SDL_Color border);
	Text(std::wstring str, int x0, int y0, int h, int w, SDL_Color letters, SDL_Color background, SDL_Color border);
	Text(const Text& other);
	void Draw(SDL_Renderer* renderer, TTF_Font* font);
	void SetText(int a);
	void SetText(double a, int len);
	void SetText(const wchar_t* val);
	void DeInit();
	~Text();
};

