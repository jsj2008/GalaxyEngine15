#pragma once
#include "GUI_Interactable.h"
#include <string>

class Button :
	public GUI_Interactable
{
public:
	Button();
	~Button();

	bool Draw();

private:
	std::string buttonText;
};

