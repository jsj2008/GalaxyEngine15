#pragma once

#include "video_includes.h"

class VideoManager
{
public:
	VideoManager();
	~VideoManager();

	// Start the GLFW engine
	bool Startup();

	// Create and show the window
	bool CreateAndShowWindow(char* title = "Galaxy Engine 15", int x = 800, int y = 600);
	void ReloadWindow();

	GLFWwindow* GetWindow() { return window; };

	// Enable and disable depth testing
	void DepthTesting(bool doDepthTesting);

	// Buffer swap
	void OpenFrame();
	void CloseFrame();

	// Reload the matrices when the window resizes
	void ResizeWindow(GLFWwindow* win, int w, int h);

	void GetWindowDims(int& width, int& height);

	void Shutdown();

private:
	bool init;

	GLFWwindow* window;
	GLFWmonitor* primaryMon;
	const GLFWvidmode* videoMode;

	int windowWidth, windowHeight;

	bool InitalizeEngine();

	static void glfw_error_cb(int error, const char* description);
	void LoadVideoAssets();
	void CreateFramebuffer();

};

