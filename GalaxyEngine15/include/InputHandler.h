#pragma once
#include "math_3d.h"
#include "video_includes.h"
#include "logger.h"

#include "GUI_Interactable.h"

#include <GLFW/glfw3.h>
#include <vector>
#include "GlobalCustomVariables.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	bool DoTick();	// Updates to be completed per tick
	void UpdateMousePosition(double x, double y);

private:
	// The window that this handler is attached to
	GLFWwindow* mainWindow;

	std::vector<GUI_Interactable*> guiInteractables;
	Vector2f mousePosition;
};

