#pragma once
#include "math_3d.h"
#include "video_includes.h"
#include "logger.h"

#include "Button.h"

#include <GLFW/glfw3.h>
#include <vector>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	bool DoTick();	// Updates to be completed per tick
	void UpdateMousePosition(double x, double y);

private:
	std::vector<GUI_Interactable*> guiInteractables;
	Vector2f mousePosition;
};

