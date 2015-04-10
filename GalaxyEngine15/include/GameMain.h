#pragma once
#include "video_includes.h"
#include "VideoManager.h"
#include "InputHandler.h"
#include "logger.h"

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

private:
	// Main window handler
	VideoManager video;
	InputHandler input;
};

