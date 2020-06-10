#include "MainMenu.h"
#include "BasicButton.h"

MainMenu::MainMenu()
{
}

void MainMenu::Init()
{
	buttons.push_back(new BasicButton(150, 100, 500, 85, L"Начать", EN_FIELD));
	buttons.push_back(new BasicButton(150, 255, 500, 85, L"Настройки", EN_OPTIONS));
	buttons.push_back(new BasicButton(150, 410, 500, 85, L"Выход", EN_EXIT));
}

int MainMenu::Run(Window& window, StartData& data)
{
	Init();
	int buf;
	int x, y;
	bool pressed;
	do
	{
		if (window.GetInput(x, y, pressed))
		{
			DeInit();
			return EN_EXIT;
		}
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			buf = buttons[i]->CheckCollision(x, y, pressed);
			window.Draw(*buttons[i]);
			if (buf != EN_NONE)
			{
				DeInit();
				return buf;
			}
		}		
		window.Update();
		window.Clear(247, 255, 255);
		Sleep(10);
	} while (true);
}

void MainMenu::DeInit()
{
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

MainMenu::~MainMenu()
{
	
}
