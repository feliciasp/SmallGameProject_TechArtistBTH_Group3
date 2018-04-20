//BASIC UNDERSTANDING AND HOW THINGS ARE "CALLED"
//
//-> betyder att vi går från en klass till en annan
//
//main->gameClass med gameloopen och i gameloopen finns en funktion som heter frame() och det är basicly vad som ska visas varje frame->graphics classen(har hand om grafiken)->
//och grafphicClass har en render funktion som basicalyy är renderfuntkionen som säger vad som ska randeras och i vilken ordning vi gör saker.
//I graphics render händer lite olika saker:
//grpahicsrender->d3dClass som initiliazerar direct3D
//graphicsclass->vår camera class som genereras vår view amtrix (uppdaterar)
//graphicsclass->objectClass som håller information om vårt objekt som vi vill rendera
//graphicsclas->shaderClass som faktiskt presenterar vårt obj på vår skärm
#define STB_IMAGE_IMPLEMENTATION	//for reading image

#include "gameClass.h"
#include <iostream>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	//minnesläckor

	gameClass* Game;
	bool result;

	Game = new gameClass(hInstance);									//create game object
	if (!Game)
	{
		return 0;
	}

	result = Game->initialize(nCmdShow);							//INITIALIZE GAME OBJECTR
	if (!result)
	{
		//If initialization failed, display an error message
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}
	else
	{
		Game->run();
	}

	Game->shutdown();										//shutdown and release obj
	delete Game;
	Game = 0;

	return 0;
}