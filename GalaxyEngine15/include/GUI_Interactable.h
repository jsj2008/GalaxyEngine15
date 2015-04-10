#pragma once
#include "GUI_Base.h"
class GUI_Interactable :
	public GUI_Base
{
public:
	GUI_Interactable();
	~GUI_Interactable();

	bool Draw();
	bool IsMouseOver(float x, float y);

};

