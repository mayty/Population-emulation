#pragma once
#include <vector>
#include "Window.h"
#include "StartData.h"
#include "Scene.h"
#include <SDL_ttf.h>
#include "ReturnValues.h"
#include <random>
#include <ctime>

class Engine
{
	Window window;

	Scene* OptionsScene;
	Scene* MainMenuScene;
	Scene* FieldScene;
	Scene* save;

	StartData data;
public:
	Engine();
	void Run();
	~Engine();
};

