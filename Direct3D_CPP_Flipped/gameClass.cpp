#include "gameClass.h"

//init pointer to null.
gameClass::gameClass(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	graphics = 0;
	dt = 0;
	inputDirectOther = 0;
	heart3 = XMMatrixScaling(0.07f, 0.07f, 0.0f) * XMMatrixTranslation(-0.85f, 0.82f, 0.0f);
	heart2 = XMMatrixScaling(0.07f, 0.07f, 0.0f) * XMMatrixTranslation(-0.65f, 0.82f, 0.0f);
	heart1 = XMMatrixScaling(0.07f, 0.07f, 0.0f) * XMMatrixTranslation(-0.45f, 0.82f, 0.0f);
	menyMat = XMMatrixScaling(0.7f, 0.7f, 0.0f);
	winMat = XMMatrixScaling(0.7f, 0.7f, 0.0f);

	countEnemy = 0;

	player = 0;
	camera = 0;
	platform = 0;
	pickup = 0;
	background = 0;
	movementInput = 0;
	moveTest = 2.0f;

	limboMat = XMMatrixScaling(0.7f, 0.7f, 0.0f);

	gameStateMeny = true;
	gameStateLevel = false;
	gameStateLimbo = false;
	gameStateWin = false;
	done = false;
	
	GUIheart1 = 0;
	GUIheart2 = 0;
	GUIheart3 = 0;
}

//empty copycontructor. not used but if we define it it will be empty. if we do not the compiler will generate one and it might not be emtpy.
gameClass::gameClass(const gameClass& other)
{

}

//do our cleanup in shutdown instead. some exit messages might not call the decontstructor = memory leaks.
gameClass::~gameClass()
{

}

bool gameClass::initialize(int ShowWnd)
{
	int width;
	int height;
	bool result;

	//init the width and height of screen to 0 before sending them in the func
	width = height = 0;

	//init window api
	if (!initializeWindow(ShowWnd, width, height))
	{
		MessageBox(NULL, L"Error initWindow()",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//init dir input
	inputDirectOther = new directInput;
	if (!inputDirectOther)
	{
		MessageBox(NULL, L"Error inputDirectOther obj creation",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = inputDirectOther->initialize(hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error inputDirectOther obj init",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//create grphics class. handle rendering our graphics for app
	graphics = new graphicsClass;
	if (!graphics)
	{
		MessageBox(NULL, L"Error graphics obj creation",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//init graphics obj
	result = graphics->initialize(width, height, hwnd, hInstance);
	if (!result)
	{
		MessageBox(NULL, L"Error graphics init",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//init deltatime
	dt = new deltatime;
	if (!dt)
	{
		MessageBox(NULL, L"Error graphics deltatime creation",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//init dir input
	movementInput = new directInput;
	if (!movementInput)
	{
		MessageBox(NULL, L"Error inputDirectOther obj creation",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = movementInput->initialize(hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error inputDirectOther obj init",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//create camera obj
	camera = new cameraClass;
	if (!camera)
	{
		MessageBox(NULL, L"Error create camera obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	camera->setPosition(0.0f, 0.0f, -15.0f, 0.0f);


	///OBJ
	//player test
	player = new playerClass;
	if (!player)
	{
		MessageBox(NULL, L"Error create enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = player->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	player->getObj()->setMaterialName("playerMovement.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), player->getObj()->getMaterialName());
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "ShovelSpriteSheet.png");

	XMVECTOR tempBboxMax;
	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(player->getObj()->getBoundingBoxMax()) + 3 };
	player->getWeapon()->setBboxMaxWeaponRight(tempBboxMax);
	player->getWeapon()->setBboxMinWeaponRight(player->getObj()->getBoundingBoxMax());
	
	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(player->getObj()->getBoundingBoxMin()) - 3 };
	player->getWeapon()->setBboxMaxWeaponLeft(player->getObj()->getBoundingBoxMin());
	player->getWeapon()->setBboxMinWeaponLeft(tempBboxMax);


	//enemy
	enemy = new enemyClass;
	if (!enemy)
	{
		MessageBox(NULL, L"Error create enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = enemy->initlialize(graphics->getD3D()->GetDevice(), "skeletonBoi.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	enemy->getObj()->setMaterialName("skeletonTexture.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), enemy->getObj()->getMaterialName());
	enemy->getObj()->setType(3);

	//background test
	background = new backgroundClass;
	if (!background)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = background->initlialize(graphics->getD3D()->GetDevice(), "backGround1.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	background->getObj()->setMaterialName("texture3.jpg");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), background->getObj()->getMaterialName());

	//pickup test
	pickup = new pickupClass;
	if (!pickup)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = pickup->initlialize(graphics->getD3D()->GetDevice(), "vaseUV.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	pickup->getObj()->setMaterialName("texture2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), pickup->getObj()->getMaterialName());
	pickup->getTranslationMatStart(pickupStartPosMoveMat);

	//GUI
	GUIheart1 = new GUItestClass;
	if (!GUIheart1)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = GUIheart1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	GUIheart1->getObj()->setWorldMatrix(heart1);
	GUIheart1->getObj()->setMaterialName("cubeTexture1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), GUIheart1->getObj()->getMaterialName());

	GUIheart2 = new GUItestClass;
	if (!GUIheart2)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = GUIheart2->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	GUIheart2->getObj()->setWorldMatrix(heart2);
	GUIheart2->getObj()->setMaterialName("cubeTexture1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), GUIheart2->getObj()->getMaterialName());

	GUIheart3 = new GUItestClass;
	if (!GUIheart3)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = GUIheart3->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	GUIheart3->getObj()->setWorldMatrix(heart3);
	GUIheart3->getObj()->setMaterialName("cubeTexture1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), GUIheart3->getObj()->getMaterialName());

	//platform 
	platform = new platformClass;
	if (!platform)
	{
		MessageBox(NULL, L"Error create platform obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = platform->initlialize(graphics->getD3D()->GetDevice(), "platformsCol1.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	platform->getObj()->setMaterialName("texture4.jpg");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), platform->getObj()->getMaterialName());

	addObjectToObjHolder(background->getObj());
	addObjectToObjHolder(platform->getObj());


	//MENY
	meny = new GUItestClass;
	if (!meny)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = meny->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	meny->getObj()->setWorldMatrix(menyMat);
	meny->getObj()->setMaterialName("menyTexture.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), meny->getObj()->getMaterialName());
	addObjectToObjHolderMeny(meny->getObj());

	//LIMBO
	limbo = new GUItestClass;
	if (!limbo)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limbo->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limbo->getObj()->setWorldMatrix(limboMat);
	limbo->getObj()->setMaterialName("limboTexture.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limbo->getObj()->getMaterialName());

	addObjectToObjHolderLimbo(limbo->getObj());

	//LIMBO
	win = new GUItestClass;
	if (!win)
	{
		MessageBox(NULL, L"Error create win obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = win->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init win obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	win->getObj()->setWorldMatrix(winMat);
	win->getObj()->setMaterialName("winTexture.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), win->getObj()->getMaterialName());

	addObjectToObjHolderWin(win->getObj());

	return true;
}

//dows the cleanup. realeases graphics, intput and window obj
void gameClass::shutdown()
{
	if (graphics)
	{
		graphics->shutdown();
		delete graphics;
		graphics = 0;
	}

	if (inputDirectOther)
	{
		inputDirectOther->shutdown();
		delete inputDirectOther;
		inputDirectOther = 0;
	}

	if(dt)
	{
		delete dt;
		dt = 0;
	}

	if (camera)
	{
		delete camera;
		camera = 0;
	}
	if (movementInput)
	{
		movementInput->shutdown();
		delete movementInput;
		movementInput = 0;
	}
	if (enemy)
	{
		enemy->shutdown();
		delete enemy;
		enemy = 0;
	}
	if (background)
	{
		background->shutdown();
		delete background;
		background = 0;
	}
	if (pickup)
	{
		pickup->shutdown();
		delete pickup;
		pickup = 0;
	}
	if (player)
	{
		player->shutdown();
		delete player;
		player = 0;
	}
	if (platform)
	{
		platform->shutdown();
		delete platform;
		platform = 0;
	}
	if (GUIheart1)
	{
		GUIheart1->shutdown();
		delete GUIheart1;
		GUIheart1 = 0;
	}
	if (GUIheart2)
	{
		GUIheart2->shutdown();
		delete GUIheart2;
		GUIheart2 = 0;
	}
	if (GUIheart3)
	{
		GUIheart3->shutdown();
		delete GUIheart3;
		GUIheart3 = 0;
	}
	if (meny)
	{
		meny->shutdown();
		delete meny;
		meny = 0;
	}
	if (limbo)
	{
		limbo->shutdown();
		delete limbo;
		limbo = 0;
	}
	if (win)
	{
		win->shutdown();
		delete win;
		win = 0;
	}

	shutdownWindow();

	/////////////////MENY


	return;
}

//run until quit. frame called each loop, handles application process.
//while not done
//	check for windows system messages
//	process system messages
//	process app loop
//	check if user wanted to quit during the frame processing

void gameClass::run()
{
	MSG msg;
	//bool done;
	bool result;
	int fakeTimer = 0;
	//initialize the msg structure
	ZeroMemory(&msg, sizeof(MSG));

	//Loop until there is a quit msg from the user or window
	//done = false;
	while (!done)
	{	

		//handle the wnd msg
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))			//(pointer to msg structure the recives msg info, handle to wnd whose msg ar to be retrives(if null from any wnd), if 0 and the next parameter alse is 0 it return all viable msg beause no range filter is prformed, spec hoe msg is to be handles(PM_REMOVE = msg is removed after processing)).
		{
			TranslateMessage(&msg);								//vintual key to character msg
			DispatchMessage(&msg);								//disp to window proc
		}

		//if msg is to quit
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{

			if (gameStateLevel)
			{
				//otherwise to the fram proc
				result = frameGame(dt->getDeltaTime());
				dt->updateDeltaTime();

				if (!result)
				{
					fakeTimer = 500;
				}

			}
			else if(gameStateMeny)
			{
				
				result = frameMeny(dt->getDeltaTime());
				dt->updateDeltaTime();

				if (!result && fakeTimer <= 0)
				{
					done = true;
				}
				else
				{
					fakeTimer -= 1;
				}

				if (inputDirectOther->isEnterPressed())
				{
					gameStateLevel = true;
				}
			}
			else if (gameStateLimbo)
			{
				result = frameLimbo(dt->getDeltaTime());
				dt->updateDeltaTime();

				if (fakeTimer <= 0)
				{
					fakeTimer -= 1;
				}
			}
			else if (gameStateWin)
			{
				result = frameWin(dt->getDeltaTime());
				dt->updateDeltaTime();

				if (fakeTimer <= 0)
				{
					fakeTimer -= 1;
				}
			}
		}
	}
	return;
}

bool gameClass::frameWin(double dt)
{
	bool result;

	result = inputDirectOther->frame(dt);
	if (!result)
	{
		return false;
	}

	//constant MATRICES
	updateConstantMatrices();

	graphics->beginScene();
	for (int i = 0; i < objHolderWin.size(); i++)
	{
		result = graphics->frame(objHolderWin[i], view, proj, objHolderWin[i]->getType(), objHolderWin[i]->getMaterialName(), camera->getPosition());
		if (!result)
		{
			return false;
		}
	}
	graphics->endScene();

	
	if (inputDirectOther->isEscapePressed() == true)
	{
		gameStateLevel = false;
		gameStateLimbo = false;
		gameStateWin = false;
		gameStateMeny = true;
		return false;
	}

	return true;
}

bool gameClass::frameLimbo(double dt)
{
	bool result;

	result = inputDirectOther->frame(dt);
	if (!result)
	{
		return false;
	}

	//constant MATRICES
	updateConstantMatrices();

	graphics->beginScene();
	for (int i = 0; i < objHolderLimbo.size(); i++)
	{
		result = graphics->frame(objHolderLimbo[i], view, proj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), camera->getPosition());
		if (!result)
		{
			return false;
		}
	}
	graphics->endScene();

	if (inputDirectOther->isEnterPressed() == true)
	{
		gameStateLevel = true;
		gameStateLimbo = false;
		gameStateMeny = false;
		return false;
	}
	if (inputDirectOther->isEscapePressed() == true)
	{
		gameStateLevel = false;
		gameStateLimbo = false;
		gameStateMeny = true;
		return false;
	}

	return true;
}

//where all the processing for our app is done here. right now it checks if user has precces anything. if its escape then quit. if no then we call our graphics obj to do its frame processing and render the graphics for the frame
bool gameClass::frameGame(double dt)
{
	//DO STUFFS
	bool result;

	result = inputDirectOther->frame(dt);
	if (!result)
	{
		return false;
	}


	//constant MATRICES
	updateConstantMatrices();

	//enemy stuff
	if (enemy->getIsActive() && !enemy->getCheckIfObjHolder())
	{	
		addObjectToObjHolder(enemy->getObj());
		enemy->setCheckIfObjHolder(true);
		player->setIfInObjHolder(false);
	}
	if (enemy->getIsActive())
	{
		updateEnemy(dt);
	}

	////background stff
	staticBackground();

	//platform
	updatePlatform();

	//pickup stuff
	updatePickup();

	//player stuff
	updatePlayer(dt);

	//set camera to follow player
	updateCamera();

	//om enemy rör på sig
	updateCollision(dt);
	
	if (!player->getIfInObjHolder())
	{
		addObjectToObjHolder(player->getObj());
		player->setIfInObjHolder(true);
	}

	//GUI
	if (updateGUI(dt, GUIheart1))
	{
		player->setPlayerHP(player->getPlayerHP() + 1);
	}
	else if (updateGUI(dt, GUIheart2))
	{
		player->setPlayerHP(player->getPlayerHP() + 1);
	}
	else if (updateGUI(dt, GUIheart3))
	{
		player->setPlayerHP(player->getPlayerHP() + 1);
	}

	if (!GUIheart1->getIsDestroy() && !GUIheart1->getCheckIfObjHolder())
	{
		addObjectToObjHolder(GUIheart1->getObj());
		GUIheart1->setCheckIfObjHolder(true);
	}
	if (!GUIheart2->getIsDestroy() && !GUIheart2->getCheckIfObjHolder())
	{
		addObjectToObjHolder(GUIheart2->getObj());
		GUIheart2->setCheckIfObjHolder(true);
	}
	if (!GUIheart3->getIsDestroy() && !GUIheart3->getCheckIfObjHolder())
	{
		addObjectToObjHolder(GUIheart3->getObj());
		GUIheart3->setCheckIfObjHolder(true);
	}

	if (!pickup->getIsDestry() && !pickup->getCheckIfObjHolder())
	{
		addObjectToObjHolder(pickup->getObj());
		pickup->setCheckIfObjHolder(true);
	}
	if (pickup->getIsDestry() && pickup->getCheckIfObjHolder())
	{
		removeObjFromObjHolder(pickup->getObj());
		pickup->setCheckIfObjHolder(false);
	}
	


	//for render
	graphics->beginScene();
	for(int i = 0; i < objHolder.size(); i++)
	{
		if (objHolder[i]->getType() == 2)
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), camera->getPosition(), player->getFrameCount(), player->getCurrentFrame(), player->getCurrentAnimation(), player->getFlipped());
			if (!result)

			{
				return false;
			}
		}

		else
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), camera->getPosition());
			if (!result)

			{
				return false;
			}
		}
	}
	graphics->endScene();

	if (enemy->getEnemyHP() == 0)
	{
		player->resetPlayer();
		pickup->resetPickup();
		enemy->resetEnemy();
		GUIheart1->resetGUI();
		GUIheart2->resetGUI();
		GUIheart3->resetGUI();

		gameStateLevel = false;
		gameStateMeny = false;
		gameStateLimbo = false;
		gameStateWin = true;
		return false;
	}

	if (player->getPlayerHP() == 0)
	{
		player->resetPlayer();
		pickup->resetPickup();
		enemy->resetEnemy();
		GUIheart1->resetGUI();
		GUIheart2->resetGUI();
		GUIheart3->resetGUI();

		gameStateLevel = false;
		gameStateMeny = false;
		gameStateWin = false;
		gameStateLimbo = true;
		return false;
	}

	if (inputDirectOther->isEscapePressed() == true)
	{
		player->resetPlayer();
		pickup->resetPickup();
		enemy->resetEnemy();
		GUIheart1->resetGUI();
		GUIheart2->resetGUI();
		GUIheart3->resetGUI();

		gameStateLevel = false;
		gameStateMeny = true;
		gameStateWin = false;
		gameStateLimbo = false;
		return false;
	}

	return true;
}

bool gameClass::frameMeny(double dt)
{
	bool result;

	result = inputDirectOther->frame(dt);
	if (!result)
	{
		return false;
	}

	//constant MATRICES
	updateConstantMatrices();

	graphics->beginScene();
	for (int i = 0; i < objHolderMeny.size(); i++)
	{
		result = graphics->frame(objHolderMeny[i], view, proj, objHolderMeny[i]->getType(), objHolderMeny[i]->getMaterialName(), camera->getPosition());
		if (!result)

		{
			return false;
		}
	}
	graphics->endScene();

	if (inputDirectOther->isEscapePressed() == true)
	{
		return false;
	}

	return true;
}

//func that we directs window msg into. 
LRESULT CALLBACK gameClass::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, msg, wparam, lparam);

}

//build window we render to. return width and height so we can use them leater. FULL_SCREEN global says if we want fullscreen or not.
bool gameClass::initializeWindow(int ShowWnd, int& width, int& height)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;		//The DEVMODE data structure contains information about the initialization and environment of a printer or a display device.
	int posX;
	int posY;

	//get external pointer top the obj
	appHandle = this;						///CHECK WHAT IS GOING ON HERE
	//get intance of this app
	//hInstance = GetModuleHandle(NULL);
	//give app name
	appName = L"Game";

	//Setup window class wiht default settings
	wc.cbSize = sizeof(WNDCLASSEX);    //Size of our windows class
	wc.style = CS_HREDRAW | CS_VREDRAW;    //class styles
	wc.lpfnWndProc = WndProc;    //Default windows procedure function
	wc.cbClsExtra = NULL;    //Extra bytes after our wc structure
	wc.cbWndExtra = NULL;    //Extra bytes after our windows instance
	wc.hInstance = hInstance;    //Instance to current application
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);    //Title bar Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);    //Default mouse Icon
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    //Window bg color
	wc.lpszMenuName = NULL;    //Name of the menu attached to our window
	wc.lpszClassName = appName;    //Name of our windows class
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); //Icon in your taskbar


	//reg window class for subsequent use in calls to the createWindow or createWindowEx func.
	//RegisterClassEx(&wc);
	if (!RegisterClassEx(&wc))    //Register our windows class
	{
		//if registration failed, display error
		MessageBox(NULL, L"Error registering window class",
			L"Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//det the resulotion of the user desktop screen
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	//setup the screen settings depending on wherther its running in fullscreen or windowd mode
	if (FULL_SCREEN)
	{
		//if fullscreen set the screen to max size of the user desctop and 32bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)height;
		dmScreenSettings.dmBitsPerPel = 32;		//color res , bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;	//spes if certain members of deMode have been initialized.

		//change dispalysettings to fullscreen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);	//change disp settings of default display device to the spacified graphics mode

		//set pos of window to top left corner
		posX = posY = 0;
	}
	else
	{
		//if windoed then set it to 800x600
		width = 800;
		height = 600;

		//place window in the middle of sreen
		posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	}

	//create the window and handle to it
	hwnd = CreateWindowEx(NULL, appName, appName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating windoiw class",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//bring window up on screen and sit it as main focus
	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);
	//SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//hide mouse cursor
	//ShowCursor(false);

	return true;
}

//return screensettings backj to normal and releases window and handler(s)
void gameClass::shutdownWindow()
{
	//show the mouse cursor again
	ShowCursor(true);

	//fix the display settings if leavinf fullscreen mode
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//remoce the indow
	DestroyWindow(hwnd);
	hwnd = NULL;

	//remove the app instance
	UnregisterClass(appName, hInstance);
	hInstance = NULL;

	return;
}

//windows send its msg to this func. we say it send it msg to mesgHandler insteand in out gameClass
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		//check if window is being destroyd
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		//check if closed
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		//all other msg send to msg handler in gameClass
		default:
		{
			return appHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}



void gameClass::getMoveMat(XMMATRIX& mat)
{
	mat = moveMatTest;
}

void gameClass::setMoveMat(float x)
{
	moveMatTest = XMMatrixTranslation(x, 0.0f, 0.0f);
}

void gameClass::addObjectToObjHolder(objectClass* obj)
{
	objHolder.push_back(obj);
}

void gameClass::removeObjFromObjHolder(objectClass * obj)
{
	//vec.erase(vec.begin() + i);
	for (int i = 0; i < objHolder.size(); i++)
	{
		if (objHolder[i] == obj)
		{
			objHolder.erase(objHolder.begin() + i);
		}
	}

}

void gameClass::addObjectToObjHolderLimbo(objectClass * obj)
{
	objHolderLimbo.push_back(obj);
}

void gameClass::removeObjFromObjHolderLimbo(objectClass * obj)
{
	//vec.erase(vec.begin() + i);
	for (int i = 0; i < objHolderLimbo.size(); i++)
	{
		if (objHolderLimbo[i] == obj)
		{
			objHolderLimbo.erase(objHolderLimbo.begin() + i);
		}
	}
}

void gameClass::addObjectToObjHolderMeny(objectClass* obj)
{
	objHolderMeny.push_back(obj);
}

void gameClass::removeObjFromObjHolderMeny(objectClass * obj)
{
	//vec.erase(vec.begin() + i);
	for (int i = 0; i < objHolderMeny.size(); i++)
	{
		if (objHolderMeny[i] == obj)
		{
			objHolderMeny.erase(objHolderMeny.begin() + i);
		}
	}

}

void gameClass::addObjectToObjHolderWin(objectClass * obj)
{
	objHolderWin.push_back(obj);
}

void gameClass::removeObjFromObjHolderWin(objectClass * obj)
{
	//vec.erase(vec.begin() + i);
	for (int i = 0; i < objHolderWin.size(); i++)
	{
		if (objHolderWin[i] == obj)
		{
			objHolderWin.erase(objHolderWin.begin() + i);
		}
	}
}

void gameClass::updateConstantMatrices()
{
	camera->createViewMatrix();
	camera->getViewMat(view);
	graphics->getD3D()->getProjMatrix(proj);
	graphics->getD3D()->getWorldMatrix(world);
}

void gameClass::updateEnemy(double dt)
{
	enemy->handleMovement(dt);
	enemy->getMoveMat(enemyMove);
	enemy->getObj()->setWorldMatrix(enemyMove);
	enemy->checkCollisions (checkCollisionPlatformTop(enemy->getObj(), enemyMove), 
							checkCollisionPlatformLeft(enemy->getObj(), enemyMove),
							checkCollisionPlatformRight(enemy->getObj(), enemyMove),
							checkCollisionPlatformBot(enemy->getObj(), enemyMove));
	enemy->getMoveMat(enemyMove);
	enemy->getObj()->setWorldMatrix(enemyMove);
}

void gameClass::updatePlayer(double dt)
{
	player->handleMovement(dt);
	player->updateAnimation(dt);
	player->getMoveMat(playerMove);
	player->getObj()->setWorldMatrix(playerMove);
	player->checkCollisions(checkCollisionPlatformTop(player->getObj(), playerMove),
							checkCollisionPlatformLeft(player->getObj(), playerMove),
							checkCollisionPlatformRight(player->getObj(), playerMove),
							checkCollisionPlatformBot(player->getObj(), playerMove));
	player->getMoveMat(playerMove);
	player->getObj()->setWorldMatrix(playerMove);
}

void gameClass::updateCamera()
{
	camera->updateTarget(XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)), XMVectorGetY(XMVector3Transform(player->getObj()->getPosition(), playerMove)));
	camera->updatePosition(XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)), XMVectorGetY(XMVector3Transform(player->getObj()->getPosition(), playerMove)));
}

void gameClass::staticBackground()
{
	backgroundMat = XMMatrixIdentity();
	background->getObj()->setWorldMatrix(backgroundMat);
}

bool gameClass::updateGUI(double dt, GUItestClass* obj)
{
	return obj->updateDestroyState(dt);
}

void gameClass::updatePlatform()
{
	platformMat = XMMatrixIdentity();
	platform->getObj()->setWorldMatrix(platformMat);
}

void gameClass::updatePickup()
{
	/*pickup->getObj()->updatePosition(pickupStartPosMoveMat);*/
	pickup->getObj()->setWorldMatrix(pickupStartPosMoveMat);
}
   
void gameClass::updateCollision(double dt)
{
	lengthBetween1 = XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove));
	lengthBetween2 = XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)) - XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyMove));

	enemy->setLengthBetween(lengthBetween1, lengthBetween2);

	if (enemy->getIsActive() && player->getFlipped() && player->getIfAttack() && 
		player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponLeft(), playerMove),
																 XMVector3Transform(player->getWeapon()->getBboxMaxWeaponLeft(), playerMove),
																 XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyMove), 
																 XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyMove)))
	{
		if(enemy->hurtState())
		{
			enemy->setEnemyHP(enemy->getEnemyHP() - 1);
			OutputDebugString(L"\nenemy lost hP!\n");
		}
		if (enemy->getEnemyHP() <= 0)
		{
			removeObjFromObjHolder(enemy->getObj());
			enemy->setIsActive(false);
			player->setIfInObjHolder(false);
		}
	}
	else if (enemy->getIsActive() && !player->getFlipped() && player->getIfAttack() 
		&& player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponRight(), playerMove),
																	XMVector3Transform(player->getWeapon()->getBboxMaxWeaponRight(), playerMove), 
																	XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyMove), 
																	XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyMove)))
	{
		if (enemy->hurtState())
		{
			enemy->setEnemyHP(enemy->getEnemyHP() - 1);
			OutputDebugString(L"\nenemy lost hP!\n");
		}
		if (enemy->getEnemyHP() <= 0)
		{
			removeObjFromObjHolder(enemy->getObj());
			enemy->setIsActive(false);
		}
	}
	
	enemy->timeCountdown(dt);

	if (enemy->getIsActive() && player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), 
																					  XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove),
																					  XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyMove), 
																					  XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyMove)))
	{
		player->setPlayerHP(player->getPlayerHP());
		player->setPlayerHurt(true);
		OutputDebugString(L"\nplayer lost hP!\n");
		if (!GUIheart1->getIsDestroy() && GUIheart1->getCheckIfObjHolder())
		{
			GUIheart1->setIsDestroy(true);
			removeObjFromObjHolder(GUIheart1->getObj());
			GUIheart1->setCheckIfObjHolder(false);
		}
		else if (!GUIheart2->getIsDestroy() && GUIheart2->getCheckIfObjHolder() && GUIheart1->getIsDestroy())
		{
			GUIheart2->setIsDestroy(true);
			removeObjFromObjHolder(GUIheart2->getObj());
			GUIheart2->setCheckIfObjHolder(false);
		}
		else if (!GUIheart3->getIsDestroy() && GUIheart3->getCheckIfObjHolder() && GUIheart1->getIsDestroy() && GUIheart2->getIsDestroy())
		{
			GUIheart3->setIsDestroy(true);
			removeObjFromObjHolder(GUIheart3->getObj());
			GUIheart3->setCheckIfObjHolder(false);
		}
	}
	
	//if (lengthBetween1 <= XMVectorGetX(enemy->getTriggerCheck()) && lengthBetween1 >= 1.5f)
	//{
	//	//går åt vänster
	//	if (enemy->getFacing() && countEnemy <= 0)
	//	{
	//		enemy->setRotationCheck(true);
	//		countEnemy = 100;

	//	}
	//	else if(enemy->getFacing() && countEnemy >= 0)
	//	{
	//		countEnemy -= 1;
	//	}
	//	else
	//	{
	//		enemy->setRotationCheck(false);
	//		enemy->setFacing(false);
	//	}

	//	OutputDebugString(L"\nwalking\n");
	//	enemy->setMove(2.5f * dt);
	//}
	//if (lengthBetween2 <= XMVectorGetX(enemy->getTriggerCheck()) && lengthBetween1 <= 1.5f)
	//{
	//	//år höger
	//	if (!enemy->getFacing() && countEnemy <= 0)
	//	{
	//		enemy->setRotationCheck(true);
	//		countEnemy = 100;
	//	}
	//	else if (!enemy->getFacing() && countEnemy >= 0)
	//	{
	//		countEnemy -= 1;
	//	}
	//	else
	//	{
	//		enemy->setRotationCheck(false);
	//		enemy->setFacing(true);
	//	}

	//	enemy->setMove(-2.5f * dt);
	//}

	if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove),
															  XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove),
															  XMVector3Transform(pickup->getObj()->getBoundingBoxMin(), pickupStartPosMoveMat), 
															  XMVector3Transform(pickup->getObj()->getBoundingBoxMax(), pickupStartPosMoveMat)))
	{
		pickup->setIsDestroy(true);
	}
}

bool gameClass::checkCollisionPlatformTop(objectClass *obj, XMMATRIX objWorld)
{
	bool check = false;
	for (int i = 0; i < platform->getMeshCount(); i++)
	{
		if (obj->getCollisionClass()->checkCollisionTop(XMVector3Transform(obj->getBoundingBoxMin(), objWorld), XMVector3Transform(obj->getBoundingBoxMax(), objWorld), XMVector3Transform(platform->getObj()->getBoundingBoxMin(i), world), XMVector3Transform(platform->getObj()->getBoundingBoxMax(i), world)))
		{
			//OutputDebugString(L"\nCOLLISION PLATFORM TOP TRUE\n");
			check = true;
		}
	}
	if (check == false)
		return false;
	else
		return true;
}
bool gameClass::checkCollisionPlatformLeft(objectClass *obj, XMMATRIX objWorld)
{
	bool check = false;
	for (int i = 0; i < platform->getMeshCount(); i++)
	{
		if (obj->getCollisionClass()->checkCollisionLeft(XMVector3Transform(obj->getBoundingBoxMin(), objWorld), XMVector3Transform(obj->getBoundingBoxMax(), objWorld), XMVector3Transform(platform->getObj()->getBoundingBoxMin(i), world), XMVector3Transform(platform->getObj()->getBoundingBoxMax(i), world)))
		{
			//OutputDebugString(L"\nCOLLISION PLATFORM LEFT TRUE\n");
			check = true;
		}
	}
	if (check == false)
		return false;
	else
		return true;
}
bool gameClass::checkCollisionPlatformRight(objectClass *obj, XMMATRIX objWorld)
{
	bool check = false;
	for (int i = 0; i < platform->getMeshCount(); i++)
	{
		if (obj->getCollisionClass()->checkCollisionRight(XMVector3Transform(obj->getBoundingBoxMin(), objWorld), XMVector3Transform(obj->getBoundingBoxMax(), objWorld), XMVector3Transform(platform->getObj()->getBoundingBoxMin(i), world), XMVector3Transform(platform->getObj()->getBoundingBoxMax(i), world)))
		{
			//OutputDebugString(L"\nCOLLISION PLATFORM RIGHT TRUE\n");
			check = true;
		}
	}
	if (check == false)
		return false;
	else
		return true;
}
bool gameClass::checkCollisionPlatformBot(objectClass *obj, XMMATRIX objWorld)
{
	bool check = false;
	for (int i = 0; i < platform->getMeshCount(); i++)
	{
		if (obj->getCollisionClass()->checkCollisionBot(XMVector3Transform(obj->getBoundingBoxMin(), objWorld), XMVector3Transform(obj->getBoundingBoxMax(), objWorld), XMVector3Transform(platform->getObj()->getBoundingBoxMin(i), world), XMVector3Transform(platform->getObj()->getBoundingBoxMax(i), world)))
		{
			//OutputDebugString(L"\nCOLLISION PLATFORM BOT TRUE\n");
			check = true;
		}
	}
	if (check == false)
		return false;
	else
		return true;
}

void gameClass::setGameStateLevel(bool other)
{
	this->gameStateLevel = other;
}

void gameClass::setGameStateMeny(bool other)
{
	this->gameStateMeny = other;
}

void gameClass::setGameStateLimbo(bool other)
{
	this->gameStateLimbo = other;
}
