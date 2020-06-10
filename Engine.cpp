#include "Engine.h"

mns::engine::engine()
	:window{ 800, 600, "window" }, default_state{ 0 }, exit_state{ 0 }
{
}

std::string mns::engine::get_last_error()
{
	return Window::get_last_error();
}

void mns::engine::set_default_state(int state)
{
	default_state = state;
}

void mns::engine::set_exit_state(int state)
{
	exit_state = state;
}

mns::engine::~engine()
{
}
