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
	// Draw in 2D
	testCam.Ortho(true);

	// Set up the camera angle
	testQuad.SetMatrix(testCam.VPMatrix());

	// Set up test quads
	testQuad.Draw_f(.5, .5);
}

void GameMain::SetUpTestCameraAndMaterial()
{
	// 2D camera setup
	int x, y;
	video.GetWindowDims(x, y);

	testCam = GameCamera();
	testCam.setFOV(45.0f);
	testCam.setAspectRatio(x / (float)y);
	testCam.setZPlanes(.1f, 1000.0f);
	testCam.SetScreen((float)x, (float)y);
	testCam.setOrthoMode(OM_SCREEN);

	// Make material
	testMat = Material(new ShaderPair("quadShader"), "..\\res\\tex1.png");	

	// Make quad
	testQuad = TextureQuad(200, 500, &testMat);
	testMat.SetRepeat(true);
	testQuad.SetOrigin(100, 250);
}
