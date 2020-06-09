#pragma once
#include "Button.h"
class BasicButton :	public Button
{
private:
	int retVal;
	int OnClickEvent();
public:
	BasicButton(const BasicButton& a);
	BasicButton(int x, int y, int w, int h, const wchar_t* text, int retVal);
	~BasicButton() { if (texture) SDL_DestroyTexture(texture); }
};

