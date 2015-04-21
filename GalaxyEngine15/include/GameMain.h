#pragma once
#include "video_includes.h"
#include "VideoManager.h"
#include "InputHandler.h"
#include "logger.h"
#include "GameCamera.h"
#include "GlobalCustomVariables.h"
#include "ShaderManager.h"
#include "Button.h"

/* 
GameMain.h
-------------------------------------
Class that handles the game loop, main menu, top-level resource loading
*/

class GameMain
{
public:
	GameMain();
	~GameMain();

	bool LoadGame();
	bool Run();

	void doTestDraw();
	void SetUpTestCameraAndMaterial();

private:
	// Main window handler
	VideoManager video;
	InputHandler input;

//  Test members
//  ------------------
	GameCamera  testCam;
	Material    testMat;
	Button		testButton;
};

