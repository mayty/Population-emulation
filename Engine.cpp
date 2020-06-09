#include "Engine.h"

#include "MainMenu.h"
#include "Options.h"
#include "Field.h"

#include <iostream>

Engine::Engine()
	:window(800, 600, "window")
{
	OptionsScene = nullptr;
	MainMenuScene = nullptr;
	FieldScene = nullptr;
	save = nullptr;
	if (!window.Check())
	{
		return;
	}
	MainMenuScene = new MainMenu();
	OptionsScene = new Options();
	FieldScene = new Field();
}

void Engine::Run()
{
	if (!window.Check())
	{
		system("pause");
		return;
	}
	srand(time(NULL));
	int returnValue = EN_MAIN_MENU;
	while (returnValue != EN_EXIT)
	{
		switch (returnValue)
		{
		case EN_MAIN_MENU:
			if (MainMenuScene)
			{
				returnValue = MainMenuScene->Run(window, data);
			}
			else
			{
				returnValue = EN_EXIT;
			}
			break;
		case EN_OPTIONS:
			if (OptionsScene)
			{
				returnValue = OptionsScene->Run(window, data);
			}
			else
			{
				returnValue = EN_MAIN_MENU;
			}
			break;
		case EN_FIELD:
			if (FieldScene)
				returnValue = FieldScene->Run(window, data);
			else
			{
				returnValue = EN_MAIN_MENU;
			}
			break;
		case EN_SAVE:
			if (save)
				delete save;
			save = new Field(*(Field*)FieldScene);
			returnValue = EN_FIELD;
			break;
		case EN_LOAD:
			if (save)
			{
				if (FieldScene)
				{
					delete FieldScene;
					FieldScene = new Field(*(Field*)save);
				}
			}
			returnValue = EN_FIELD;
			break;
		default:
			returnValue = EN_MAIN_MENU;
		}
	}
}

Engine::~Engine()
{
	if (MainMenuScene)
	{
		delete MainMenuScene;
		MainMenuScene = nullptr;
	}
	if (OptionsScene)
	{
		delete OptionsScene;
		OptionsScene = nullptr;
	}
	if (FieldScene)
	{
		delete FieldScene;
		FieldScene = nullptr;
	}
}
