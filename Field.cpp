#include "Field.h"
#include "BasicButton.h"

#include <iostream>



Field::Field()
	:pop_graph(640, 80, 160, 100), speed_graph(640, 200, 160, 100, 1.0, true), view_range_graph(640, 320, 160, 100, 50.0, true)
{
	died = 0;
	pop_avg = 0;
	speed_avg = 0;
	tick_count = 0;
	view_range_avg = 0;
}

void Field::Init(StartData& data)
{
	if (!population.size())
	{
		for (int i = 0; i < data.GetStartNumber(); i++)
			population.push_back(Entity(20, 620, 100, 500, data.GetRepCost()));

		for (int j = 0; j < data.GetFoodCount() * 2; j++)
			food.push_back(Food(120, 520, 200, 400));

		died = 0;
		tick_count = 0;
		pop_graph.Reset();
		speed_graph.Reset();
		view_range_graph.Reset();
		pop_avg = 0;
		speed_avg = 0;
		view_range_avg = 0;
	}
	buttons.push_back(new BasicButton(700, 0, 100, 40, L"Назад", EN_MAIN_MENU));
	buttons.push_back(new BasicButton(500, 0, 200, 40, L"Повторить", EN_FIELD));
	buttons.push_back(new BasicButton(350, 0, 150, 40, L"Пауза", EN_PAUSE));
	buttons.push_back(new BasicButton(760, 560, 40, 40, L"+", EN_INC_RATE));
	buttons.push_back(new BasicButton(720, 560, 40, 40, L"-", EN_DEC_RATE));
	buttons.push_back(new BasicButton(300, 560, 40, 40, L"S", EN_SAVE));
	buttons.push_back(new BasicButton(340, 560, 40, 40, L"L", EN_LOAD));
	SDL_Color letters = { 55, 76, 93, 255 };
	SDL_Color background = { 139, 145, 153, 255 };
	SDL_Color border = { 78,109,133,255 };
	lables.push_back(Text(L"Population", 0, 0, 40, 100, letters, background, border));
	lables.push_back(Text(L"Frame_time", 0, 560, 40, 40, letters, background, border));
	lables.push_back(Text(L"Avg speed", 100, 0, 40, 100, letters, background, border));
	lables.push_back(Text(L"Died", 0, 40, 40, 100, letters, background, border));
	lables.push_back(Text(L"Avg view", 100, 40, 40, 100, letters, background, border));
	lables.push_back(Text(L"Ticks", 40, 560, 40, 150, letters, background, border));
	lables.push_back(Text(L"Unlim", 720, 520, 40, 80, letters, background, border));
}

enum text_indexes {population_count = 0, frame_compute_time, avg_speed, dead_count, avg_view, ticks_elapsed, tps_disp};

int Field::Run(Window& window, StartData& data)
{
	Init(data);
	SDL_Rect base = {0, 80, 640, 440};
	std::vector<int> fpses = {25, 50, 100, 200, 1001 };
	static int fps_ind = fpses.size() - 1;
	int frame_time = 1000 / fpses[fps_ind];
	int act_fr_t = 0;

	int graph_step = 5;

	int feed_interval = 200;
	double total_speed = 0;
	double total_view = 0;
	for (unsigned int i = 0; i < population.size(); i++)
	{
		total_speed += population[i].GetSpeed();
		total_view += population[i].GetView();
	}
	
	Uint32 cTime, pTime = SDL_GetTicks();
	static bool active = true;
	int x, y;
	bool pressed;
	bool ended = false;
	while (true)
	{
		if (window.GetInput(x, y, pressed))
		{
			DeInit();
			return EN_EXIT;
		}

		for (unsigned int i = 0; i < buttons.size(); i++)
		{
			switch (buttons[i]->CheckCollision(x, y, pressed))
			{
			case EN_MAIN_MENU:
				DeInitSoft();
				return EN_MAIN_MENU;
			case EN_FIELD:
				DeInit();
				return EN_FIELD;
			case EN_PAUSE:
				active = !active;
				break;
			case EN_INC_RATE:
				fps_ind++;
				if (fps_ind >= fpses.size())
					fps_ind = fpses.size() - 1;
				frame_time = 1000 / fpses[fps_ind];
				break;
			case EN_DEC_RATE:
				fps_ind--;
				if (fps_ind < 0)
					fps_ind = 0;
				frame_time = 1000 / fpses[fps_ind];
				break;
			case EN_SAVE:
				DeInitSoft();
				return EN_SAVE;
			case EN_LOAD:
				DeInitSoft();
				return EN_LOAD;
			}
		}

		if (active && !ended && population.size())
		{
			tick_count++;
			if (!(tick_count % feed_interval))
			{
				for (int i = 0; i < data.GetFoodCount(); i++)
					food.push_back(Food(20, 620, 100, 500));
			}
			if (!(tick_count % graph_step))
			{
				pop_graph.Push(pop_avg / graph_step);
				speed_graph.Push(speed_avg / graph_step);
				view_range_graph.Push(view_range_avg / graph_step);
				pop_avg = 0;
				view_range_avg = 0.0;
				speed_avg = 0.0;
			}
			for (unsigned int i = 0; i < population.size(); i++)
			{
				switch (population[i].Update(food, data.GetEnv()))
				{
				case 1:
					total_speed -= population[i].GetSpeed();
					total_view -= population[i].GetView();
					population.erase(population.begin() + i);
					died++;
					i--;
					break;
				case 2:
					population.push_back(Entity(population[i], 0.1));
					total_speed += population[population.size() - 1].GetSpeed();
					total_view += population[population.size() - 1].GetView();
					break;
				}
			}
			pop_avg += population.size();
			if (population.size() == 0)
			{
				ended = true;
				pop_graph.Push(0);
				speed_graph.Push(0);
				view_range_graph.Push(0);
			}
			else
			{
				speed_avg += total_speed / population.size();
				view_range_avg += total_view / population.size();
			}
		}
		
		if (lables.size())
		{
			lables[population_count].SetText(population.size());
			lables[frame_compute_time].SetText(act_fr_t);
			if (population.size() > 0)
			{
				lables[avg_speed].SetText(total_speed / population.size(), 3);
				lables[avg_view].SetText(total_view / population.size(), 2);
			}
			else
			{
				lables[avg_speed].SetText(0);
				lables[avg_view].SetText(0);
			}
			lables[dead_count].SetText(died);
			lables[ticks_elapsed].SetText(tick_count);
			if (fps_ind == fpses.size() - 1)
			{
				lables[tps_disp].SetText(L"Unlim");
			}
			else
			{
				lables[tps_disp].SetText(fpses[fps_ind]);
			}
		}
		
		if (active)
		{
			window.Clear(70, 70, 70);
			SDL_SetRenderDrawColor(window.GetRenderer(), 50, 50, 50, 255);
			SDL_RenderFillRect(window.GetRenderer(), &base);
			for (unsigned int i = 0; i < food.size(); i++)
				window.Draw(food[i]);
			for (unsigned int i = 0; i < population.size(); i++)
				window.Draw(population[i]);
			window.Draw(pop_graph);
			window.Draw(speed_graph);
			window.Draw(view_range_graph);
		}
		for (unsigned int i = 0; i < lables.size(); i++)
			window.Draw(lables[i]);
		for (unsigned int i = 0; i < buttons.size(); i++)
			window.Draw(*(buttons[i]));
		
		
		cTime = SDL_GetTicks();
		act_fr_t = (cTime - pTime);
		if (act_fr_t < frame_time)
		{
			Sleep(frame_time - act_fr_t);
		}
		pTime = SDL_GetTicks();
		window.Update();
	}
}

void Field::DeInit()
{
	pop_graph.Reset();
	speed_graph.Reset();
	view_range_graph.Reset();
	population.clear();
	food.clear();
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
	lables.clear();
}

void Field::DeInitSoft()
{
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
	lables.clear();
}
