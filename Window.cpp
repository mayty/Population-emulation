#include "Window.h"
#include "ReturnValues.h"
#include <iostream>
#include <Windows.h>

std::string Window::error;

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
		error = SDL_GetError();
		throw std::exception{};
	}
	if (TTF_Init())
	{
		error = TTF_GetError();
		SDL_Quit();
		throw std::exception{};
	}	
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, NULL);
	if (!window)
	{
		error = SDL_GetError();
		SDL_Quit();
		TTF_Quit();
		throw std::exception{};
	}
	renderer = SDL_CreateRenderer(window, -1, NULL);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
		TTF_Quit();
		throw std::exception{};
	}
	if (!(font = TTF_OpenFont(font_name, 85)))
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
		TTF_Quit();
		throw std::exception{};
	}
	this->width = width;
	this->height = height;
	this->title = title;
}

bool Window::fine()
{
	return window && renderer && font;
}

std::string Window::get_last_error()
{
	return error;
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
			return (int)return_values::EXIT;
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
