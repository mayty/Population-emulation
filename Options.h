#pragma once
#include "Scene.h"
#include "Button.h"
#include "Text.h"

#include <vector>

class Options : public Scene
{
	std::vector<Button*> buttons;
	std::vector<Text> texts;

	void Init();
	void DeInit();
public:
	Options();
	int Run(Window& window, StartData& data);
	~Options();
};

