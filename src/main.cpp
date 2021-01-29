

#include "Game.h"
#include <iostream>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 && !_CONSOLE
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char *argv[])
#endif
{
	Game game;

	try
	{
		game.initApp();
		game.getRoot()->startRendering();
		game.closeApp();
	}
	catch (Ogre::Exception& e)
	{

		std::cout << "An exception has occured: " <<
			e.getFullDescription().c_str() << std::endl;
	}

	return 0;
}
