#pragma once
#include "Drawable.h"
#include <string>
#include "ReturnValues.h"

class Button: public Drawable
{
	virtual int OnClickEvent() { return EN_NONE; }
protected:
	SDL_Texture* texture;
	std::wstring text;
	SDL_Color background, letters, border;
	float activeK;
	float idleK;
	SDL_Rect base;
	SDL_Rect dest;
	bool isActive;
public:
	void Draw(SDL_Renderer* renderer, TTF_Font* font);	
	virtual int CheckCollision(int x, int y, bool pressed);	
	virtual ~Button();
};

