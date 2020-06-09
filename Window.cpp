#include "Window.h"
#include <iostream>

Window::Window()
{
	window = nullptr;
	renderer = nullptr;
	font = nullptr;
	width = 0;
	height = 0;
}

Window::Window(int width, int height, std::string title)
{
	const char* font_name = "comicSans.ttf";
	this->width = 0;
	this->height = 0;
	window = nullptr;
	renderer = nullptr;
	font = nullptr;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	if (TTF_Init())
	{
		std::cout << TTF_GetError() << std::endl;
		return;
	}	
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, NULL);
	if (!window)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, NULL);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	if (!(font = TTF_OpenFont(font_name, 85)))
	{
		std::cout << "Font load error" << std::endl;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		return;
	}
	this->width = width;
	this->height = height;
	this->title = title;
}

bool Window::Check()
{
	return window && renderer && font;
}

void Window::Draw(Drawable& obj)
{
	obj.Draw(renderer, font);
}

void Window::Update()
{
	SDL_RenderPresent(renderer);
}

void Window::Clear(int r, int g, int b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
}

int Window::GetInput(int& x0, int& y0, bool& pressed)
{
	static SDL_Event event;
	static bool prevState = false;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return -1;
		}
		int retVal = SDL_GetMouseState(&x0, &y0);
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
		{
			if (retVal & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				if (!prevState)
					pressed = true;
				else
					pressed = false;
				prevState = true;
			}
			else
			{
				pressed = false;
				prevState = false;
			}
		}
		else
			pressed = false;
	}
	else
		pressed = false;
	return 0;
}

Window::~Window()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	if (font)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
	SDL_Quit();
	TTF_Quit();
}
