#pragma once
#include "Window.h"
#include "StartData.h"
#include <Windows.h>
#include "ReturnValues.h"

class Scene
{
public:
	virtual int Run(Window& window, StartData& data) = 0;
	virtual ~Scene() {};
};
