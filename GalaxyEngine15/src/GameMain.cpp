#include "..\include\GameMain.h"
#include "..\include\logger.h"

GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

bool GameMain::LoadGame()
{
	video = VideoManager();

	// Start GLFW
	if (!video.Startup())
		return false;

	// Show the main window
	if (!video.CreateAndShowWindow())
		return false;

	// Set some video settings
	video.DepthTesting(true);

	return true;
}

bool GameMain::Run()
{
	bool gameRunning = true;
	double previous = glfwGetTime();

	while (gameRunning)
	{
		double current = glfwGetTime();
		double delta = current - previous;
		previous = current;

		// Update
		glfwPollEvents();

		// Quit if ESC is pressed
		if (glfwGetKey(video.GetWindow(), GLFW_KEY_ESCAPE))
			gameRunning = false;
	}

	// Everything went ok
	return true;
}