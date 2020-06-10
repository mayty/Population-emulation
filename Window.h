#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Drawable.h"

class Window
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	std::string title;
	static std::string error;
	int width;
	int height;
public:
	Window();
	Window(int width, int height, std::string title);

	bool fine();
	static std::string get_last_error();
	void Draw(Drawable& obj);
	void Update();
	void Clear(int r = 0, int g = 0, int b = 0);
	int GetInput(int& x0, int& y0, bool& pressed);

	int w() { return width; }
	int h() { return height; }

	SDL_Renderer* GetRenderer() { return renderer; }

	~Window();
};

