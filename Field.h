#pragma once
#include "Scene.h"
#include "Entity.h"
#include "Food.h"
#include "Button.h"
#include "Text.h"
#include "Graph.h"

class Field : public Scene
{
private:
	Graph pop_graph;
	Graph speed_graph;
	Graph view_range_graph;

	int died, tick_count;

	double pop_avg;
	double speed_avg;
	double view_range_avg;

	std::vector<Button*> buttons;
	std::vector<Text> lables;
	std::vector<Entity> population;
	std::vector<Food> food;

	void Init(StartData& data);
	void DeInit();
	void DeInitSoft();
public:
	Field();
	int Run(Window& window, StartData& data);
};

