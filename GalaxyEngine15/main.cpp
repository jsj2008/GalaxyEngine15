////////////////////////////////////////////
//        Galaxy Engine
//        Program Entrypoint
//        4/5/2015 
////////////////////////////////////////////

#include "include\GameMain.h"
#include "include\logger.h"

int main(int argc, char **argv)
{

	// Make a game object and start it up!
	GameMain game;
	
	if (game.LoadGame())
	{
		game.Run();
	}
	else
	{
		LogMessage("Something went wrong during the init process...");
	}

	return 0;
}