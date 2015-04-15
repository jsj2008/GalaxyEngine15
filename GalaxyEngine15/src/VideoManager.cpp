#include "..\include\VideoManager.h"
#include "..\include\math_3d.h"
#include "..\include\logger.h"
#include "..\include\GlobalCustomVariables.h"

#define DEBUG_PRINT_VIDEO_VERSION

/*
Video Class
-----------------------------------------
Handles all the video initialization, graphics options, and drawing functions for the game.
*/

VideoManager::VideoManager(void)
{
	
}

VideoManager::~VideoManager(void)
{

}

bool VideoManager::Startup()
{
	if (InitalizeEngine())
	{
		// Get monitor information
		primaryMon = glfwGetPrimaryMonitor();
		videoMode = glfwGetVideoMode(primaryMon);
		return true;
	}

	return false;
}

bool VideoManager::InitalizeEngine()
{
	LogMessage("\n--------------------- Program Startup ----------------------\n");
	glfwSetErrorCallback(glfw_error_cb);

	if (!glfwInit())
	{
		LogError("GLFW INIT", "Could not start GLFW3");
		return false;
	}

	LogMessage("Starting GLFW: %s\n", glfwGetVersionString());

	return true;
}

void  VideoManager::glfw_error_cb(int error, const char* description)
{
	LogMessage("GLFW ERROR: code %i msg: %s\n", error, description);
}

//////////////////////////////////////////////////////////////////////////
// Window handling here
//////////////////////////////////////////////////////////////////////////

/*
void WindowResizeCB(GLFWwindow* window, int width, int height)
-----------------------------------------
Resizes all the view matrices
*/
void VideoManager::ResizeWindow(GLFWwindow* window, int width, int height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glfwSetWindowSize(window, width, height);

	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, width, height);						// Reset The Current Viewport
}

/*
void CreateAndShowWindow(char* title, int x, int y)
-----------------------------------------
Creates the window, graphics renderer, and begins OpenGL acceleration
*/
bool VideoManager::CreateAndShowWindow(char* title, int x, int y)
{
	if (init)
	{
		windowWidth = x;
		windowHeight = y;
		GlobalCustomVariables::SetScreenDims(x, y);

		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		//glfwWindowHint(GLFW_DECORATED,0);

		// Try creating the window object
		window = glfwCreateWindow(x, y, title, NULL, NULL);
		if (!window)
		{
			glfwTerminate();
		}

		// Create the window context
		glfwMakeContextCurrent(window);

		glewInit();

		// get version info
#ifdef DEBUG_PRINT_VIDEO_VERSION
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		LogMessage("Video card and OpenGL versions:\n%s\n%s\n\n", (char*)renderer, (char*)version);
#endif
		// Set some video settings
		DepthTesting(true);

		// Load resources
		LoadVideoAssets();

		if (window)
			return true;

		return false;
	}
	return false;
}

void VideoManager::LoadVideoAssets()
{

}

void VideoManager::GetWindowDims(int& width, int& height)
{
	width = windowWidth;
	height = windowHeight;
}

void VideoManager::DepthTesting(bool doDepthTesting)
{
	if (doDepthTesting)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

// Open the frame
void VideoManager::OpenFrame()
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Close the frame
void VideoManager::CloseFrame()
{
	GLenum errCode;
	errCode = glGetError();
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		LogError("GL Render Error:", (char*)gluErrorString(errCode));
	}

	glfwSwapBuffers(window);
}

void VideoManager::Shutdown()
{
	// Delete assets
	if (videoMode)
		videoMode = 0;
	if (primaryMon)
		primaryMon = 0;
	if (window)
		window = 0;

	windowWidth = windowHeight = 0;

	LogMessage("\nVideo shutdown success...");
}

