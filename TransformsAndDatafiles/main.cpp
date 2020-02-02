#define USE_GLFW 1
#ifdef USE_GLFW
	#include "GLFW_EngineCore.h"
#endif


#include "AwesomeGame.h"

int main(int argc, char* argv[])
{
	IEngineCore* engineCore;

#ifdef USE_GLFW
	engineCore = new GLFW_EngineCore;
#endif

	if (!engineCore->initWindow(800, 600, "Game"))
		return -1;

	AwesomeGame myFirstGame;

	engineCore->runEngine(myFirstGame);

	return 0;
}
