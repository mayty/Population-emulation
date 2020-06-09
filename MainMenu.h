#pragma once
#include "Scene.h"
#include "Button.h"

#include <vector>

class MainMenu :
	public Scene
{
private:
	std::vector<Button*> buttons;

	void Init();
	void DeInit();
public:
	MainMenu();
	virtual int Run(Window& window, StartData& data);
	~MainMenu();
};

