#include "..\include\GameMain.h"

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

	// Testing function
	SetUpTestCameraAndMaterial();

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

		testButton.Update();

		// Draw to the screen
		video.OpenFrame();
			doTestDraw();
		video.CloseFrame();
	}

	// Everything went ok
	return true;
}

void GameMain::doTestDraw()
{
	// Update the global view matrix
	GlobalCustomVariables::SetViewMatrix(testCam.VPMatrix());

	testButton.Draw();
}

void GameMain::SetUpTestCameraAndMaterial()
{
	ShaderManager::AddShader("quadShader", SHADER_UV_TEXTURE);

	ShaderManager::BuildShaders();

	// 2D camera setup
	testCam = GameCamera();
	testCam.setFOV(45.0f);
	testCam.setAspectRatio(ScreenWidth / (float)ScreenHeight);
	testCam.setZPlanes(.1f, 1000.0f);
	testCam.SetScreen((float)ScreenWidth, (float)ScreenHeight);
	testCam.setOrthoMode(OM_SCREEN);
	testCam.Ortho(true);

	testButton.Init(300, 30);
	testButton.SetOriginF(.5, .5);
	testButton.SetPositionF(.66f, .33f);
}
