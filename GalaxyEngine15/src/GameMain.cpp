#include "..\include\GameMain.h"
#include "..\include\logger.h"

GameMain::GameMain()
{
}

GameMain::~GameMain()
{
}


/*
bool LoadGame()
-------------------------------------
Initializes all the game resources and returns true if it all goes OK. Returns false
if anything fails.
*/

bool GameMain::LoadGame()
{
	// Init video
	video = VideoManager();

	// Start GLFW
	if (!video.Startup())
		return false;
	
	// Init input
	input = InputHandler();

	// Show the main window
	if (!video.CreateAndShowWindow())
		return false;

	// Set some video settings
	video.DepthTesting(true);

	return true;
}


/*
bool Run()
-------------------------------------
The main game loop. Calculates delta time, input change, and draws everything
Returns true once everything has finished OK
*/

bool GameMain::Run()
{
	bool gameRunning = true;
	double previous = glfwGetTime();

	while (gameRunning)
	{
		//	Delta time variables
		//---------------------------------------------------
		double mouseX, mouseY;
		double current = glfwGetTime();
		double delta = current - previous;
		previous = current;

		//	GLFW Updates
		//---------------------------------------------------
		glfwPollEvents();
		glfwGetCursorPos(video.GetWindow(), &mouseX, &mouseY);

		//	Input Updates
		//----------------------------------------------------
		input.UpdateMousePosition(mouseX, mouseY);		// Update mouse position
		input.DoTick();									// Check the rest of the input

		// Quit if ESC is pressed
		if (glfwGetKey(video.GetWindow(), GLFW_KEY_ESCAPE))
			gameRunning = false;
	}

	// Everything went ok
	return true;
}
