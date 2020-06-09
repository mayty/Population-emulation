#include "BasicButton.h"

int BasicButton::OnClickEvent()
{
	return retVal;
}

BasicButton::BasicButton(const BasicButton& a)
{
	texture = nullptr;
	text = a.text;
	base = a.base;
	background = a.background;
	letters = a.letters;
	border = a.border;
	idleK = a.idleK;
	activeK = a.activeK;
	isActive = false;
	retVal = a.retVal;
}

BasicButton::BasicButton(int x, int y, int w, int h, const wchar_t* text, int retVal)
{
	texture = nullptr;
	this->text = text;
	base.w = w;
	base.h = h;
	base.x = x;
	base.y = y;
	background = { 199, 207, 218, 255 };
	letters = { 78, 109, 133, 255 };
	border = { 78, 109, 133, 255 };
	activeK = 0.9f;
	idleK = 1.0;
	isActive = false;
	this->retVal = retVal;
}
