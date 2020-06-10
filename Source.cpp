#include "Engine.h"
#include "ReturnValues.h"
#include "MainMenu.h"
#include "Options.h"
#include "Field.h"
#include <SDL.h>
#include <iostream>

int main(int argC, char** argV)
{
	try
	{
		mns::engine engine;
		engine.add_scene((int)return_values::FIELD, Field{});
		engine.add_scene((int)return_values::MAIN_MENU, MainMenu{});
		engine.add_scene((int)return_values::OPTIONS, Options{});
		engine.set_default_state((int)return_values::MAIN_MENU);
		engine.set_exit_state((int)return_values::EXIT);
		engine.run<Field, (int)return_values::SAVE, (int)return_values::LOAD>((int)return_values::FIELD);
	}
	catch (...)
	{
		std::cout << mns::engine::get_last_error();
	}

	return 0;
}