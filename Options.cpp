#include "Options.h"
#include "BasicButton.h"

#include <iostream>

Options::Options()
{	
}

void Options::Init()
{
	SDL_Color letters = { 55, 76, 93, 255 };
	SDL_Color background = { 139, 145, 153, 255 };
	SDL_Color border = { 78,109,133,255 };
	texts.push_back(Text(L"Количество особей", 150, 50, 40, 500, letters, background, border));
	texts.push_back(Text(L"Количество еды", 150, 150, 40, 500, letters, background, border));
	texts.push_back(Text(L"Стоимость размножения", 150, 250, 40, 500, letters, background, border));
	texts.push_back(Text(L"Благоприятность окружения", 150, 350, 40, 500, letters, background, border));
	texts.push_back(Text(L"start number", 380, 100, 30, 40, letters, background, border));
	texts.push_back(Text(L"food count", 380, 200, 30, 40, letters, background, border));
	texts.push_back(Text(L"Reproduction cost", 380, 300, 30, 40, letters, background, border));
	texts.push_back(Text(L"env", 380, 400, 30, 40, letters, background, border));

	buttons.push_back(new BasicButton(150, 500, 500, 85, L"Назад", EN_MAIN_MENU));	
	buttons.push_back(new BasicButton(430, 100, 30, 30, L"+", EN_INCREASE_POPULATION));
	buttons.push_back(new BasicButton(430, 200, 30, 30, L"+", EN_INCREASE_FOOD));
	buttons.push_back(new BasicButton(430, 300, 30, 30, L"+", EN_INCREASE_REP_COST));
	buttons.push_back(new BasicButton(430, 400, 30, 30, L"+", EN_INCREASE_ENV));
	buttons.push_back(new BasicButton(340, 100, 30, 30, L"-", EN_DECREASE_POPULATION));
	buttons.push_back(new BasicButton(340, 200, 30, 30, L"-", EN_DECREASE_FOOD));
	buttons.push_back(new BasicButton(340, 300, 30, 30, L"-", EN_DECREASE_REP_COST));
	buttons.push_back(new BasicButton(340, 400, 30, 30, L"-", EN_DECREASE_ENV));
	buttons.push_back(new BasicButton(290, 100, 40, 30, L"--", EN_FAST_DECREASE_POPULATION));
	buttons.push_back(new BasicButton(290, 200, 40, 30, L"--", EN_FAST_DECREASE_FOOD));
	buttons.push_back(new BasicButton(470, 100, 40, 30, L"++", EN_FAST_INCREASE_POPULATION));
	buttons.push_back(new BasicButton(470, 200, 40, 30, L"++", EN_FAST_INCREASE_FOOD));
}

int Options::Run(Window& window, StartData& data)
{
	Init();
	int x, y;
	bool pressed;
	int k = 0;
	while (true)
	{
		window.Clear(247, 255, 255);
		if (window.GetInput(x, y, pressed))
		{
			DeInit();
			return -1;
		}
		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			switch (buttons[i]->CheckCollision(x, y, pressed))
			{
			case EN_INCREASE_ENV:
				data.IncEnv();
				break;
			case EN_INCREASE_FOOD:
				data.IncFoodCount();
				break;
			case EN_INCREASE_POPULATION:
				data.IncStartNumber();
				break;							
			case EN_DECREASE_ENV:
				data.DecEnv();
				break;
			case EN_DECREASE_FOOD:
				data.DecFoodCount();
				break;
			case EN_DECREASE_POPULATION:
				data.DecStartNumber();
				break;
			case EN_INCREASE_REP_COST:
				data.IncRepCost();
				break;
			case EN_DECREASE_REP_COST:
				data.DecRepCost();
				break;
			case EN_FAST_INCREASE_FOOD:
				data.FastIncFoodCount();
				break;
			case EN_FAST_DECREASE_FOOD:
				data.FastDecFoodCount();
				break;
			case EN_FAST_INCREASE_POPULATION:
				data.FastIncStartNumber();
				break;
			case EN_FAST_DECREASE_POPULATION:
				data.FastDecStartNumber();
				break;
			case EN_MAIN_MENU:
				DeInit();
				return EN_MAIN_MENU;
			}
			window.Draw(*buttons[i]);
		}
		for (unsigned int i = 0; i < texts.size(); i++)
		{
			switch (i)
			{
			case 4:
				texts[i].SetText(data.GetStartNumber());
				break;
			case 5:
				texts[i].SetText(data.GetFoodCount());
				break;
			case 6:
				texts[i].SetText(data.GetRepCost(), 1);
				break;
			case 7:
				texts[i].SetText(data.GetEnv(), 1);
				break;
			}
			window.Draw(texts[i]);
		}
		window.Update();
		Sleep(10);
	}
}

void Options::DeInit()
{
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
	texts.clear();
}

Options::~Options()
{
	
}
