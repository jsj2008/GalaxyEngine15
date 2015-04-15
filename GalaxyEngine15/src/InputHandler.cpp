#include "..\include\InputHandler.h"

InputHandler::InputHandler()
{
	LogMessage("Input handler init\n");
}


InputHandler::~InputHandler()
{
}


void InputHandler::UpdateMousePosition(double x, double y)
{
	mousePosition = Vector2f((float)x, (float)y);
}

bool InputHandler::DoTick()
{
	// Handle keyboard
	
	return true;
}