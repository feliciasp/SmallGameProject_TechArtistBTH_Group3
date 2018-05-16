#include "gameClass.h"

//OutputDebugString(L"\nenemy lost hP!\n");

//init pointer to null.
gameClass::gameClass(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	graphics = 0;
	dt = 0;
	inputDirectOther = 0;
	heart5 = XMMatrixScaling(0.032f, 0.06f, 0.0f) * XMMatrixTranslation(-0.40f, 0.82f, 0.0f);
	heart4 = XMMatrixScaling(0.032f, 0.06f, 0.0f) * XMMatrixTranslation(-0.52f, 0.82f, 0.0f);
	heart3 = XMMatrixScaling(0.032f, 0.06f, 0.0f) * XMMatrixTranslation(-0.88f, 0.82f, 0.0f);
	heart2 = XMMatrixScaling(0.032f, 0.06f, 0.0f) * XMMatrixTranslation(-0.76f, 0.82f, 0.0f);
	heart1 = XMMatrixScaling(0.032f, 0.06f, 0.0f) * XMMatrixTranslation(-0.64f, 0.82f, 0.0f);
	menyMat = XMMatrixScaling(0.7f, 0.7f, 0.0f);
	winMat = XMMatrixScaling(0.7f, 0.7f, 0.0f);
	limboMat = XMMatrixIdentity();
	menyHighlightMat = XMMatrixScaling(0.38f, 0.07f, 0.0f) * XMMatrixTranslation(-0.027f, 0.16f, 0.0f);
	counterOverlay = 0;
	menyCheck = true;
	shopOverlayCount = -1;
	shopOverlayCountRow = 0;
	nrSpeedToBeUpgraded = 0;
	activeShopState = 0;
	ShopTabsCounter = 0;
	upgradeOvlerlayCounterWeapons = -1;
	tempXP = 0;

	costHPBeginning = 0;
	costSpeedBeginnning = 0;

	shopMat = XMMatrixScaling(0.85f, 0.85f, 0.85f) * XMMatrixTranslation(9.5f, 0.55f, 0.0f);
	shopOverlayMat = XMMatrixTranslation(0.0f, 0.0f, -0.01f) * shopMat;

	sound = 0;
	firstFrame = true;
	soundAvailable = true;

	countEnemy = 0;
	SpeedCost = 1;


	player = 0;
	camera = 0;
	platform = 0;
	expFragment = 0;
	ring = 0;
	background = 0;
	movementInput = 0;
	projectile = 0;
	moveTest = 2.0f;
	enemyFallingMat = XMMatrixIdentity();
	enemyTranslationMatrix = XMMatrixIdentity();
	heartHolder = 0;
	pickupHolder = 0;

	nrOfVisiblePickups = 0;

	projectileMoveMat = XMMatrixIdentity();


	gameStateMeny = true;
	gameStateLevel = false;
	gameStateLimbo = false;
	gameStateWin = false;
	done = false;

	GUIheart1 = 0;
	slot1 = 0;
	slot2 = 0;
	slot1Mat = XMMatrixScaling(0.015f, 0.03f, 0.0f) * XMMatrixTranslation(0.85f, 0.82f, 0.0f); 
	slot2Mat = XMMatrixScaling(0.015f, 0.03f, 0.0f) * XMMatrixTranslation(0.78f, 0.82f, 0.0f);
	ringDisplay = 0;
	ringDisplayMat = XMMatrixScaling(0.04f, 0.07f, 0.0f) * XMMatrixTranslation(-0.85f, 0.57f, 0.0f);
	xpDisplay = 0;
	xpDisplayMat = XMMatrixScaling(0.16f, 0.04f, 0.0f) * XMMatrixTranslation(0.05f, 0.82f, 0.0f);
	slot1xp = 0;
	slot1xpMat = XMMatrixScaling(0.015f, 0.03f, 0.0f) * XMMatrixTranslation(0.37f, 0.82f, 0.0f);
	slot2xpMat = XMMatrixScaling(0.015f, 0.03f, 0.0f) * XMMatrixTranslation(0.32f, 0.82f, 0.0f);

	slot1xpMatLimbo = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.80f, 0.748f, 0.0f);
	slot2xpMatLimbo = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.78f, 0.748f, 0.0f);
	slot1MatLimbo = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.44f, 0.748f, 0.0f);
	slot2MatLimbo = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.419f, 0.748f, 0.0f);

	healthUpgradeCountMat = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.60f, 0.509f, 0.0f);
	speedUpgradeCountMat = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.60f, 0.333f, 0.0f);

	totalCostPendingSlot2 = 0;
	totalCostPendingSlot1 = 0;
	totalCostPendingSlot2Mat = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.61f, -0.324f, 0.0f);
	totalCostPendingSlot1Mat = XMMatrixScaling(0.006f, 0.015f, 0.0f) * XMMatrixTranslation(0.63f, -0.324f, 0.0f);
	
	isUpgradeHPAactive = true;
	nrHPtoBeUpgraded = 0;
	healthCost = 1;
	upgradeCooldown = false;
	upgradeTimer = 0;

	enterReleased = true;
	arrowUpReleased = true;
	arrowUpReleased = true;
	arrowRightReleased = true;
	arrowLeftReleased = true;

	ringsInitialized = false;

	totalPendingCost = 0;
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


	//init dir input
	inputDirectOther = new directInput;
	if (!inputDirectOther)
	{
		MessageBox(NULL, L"Error inputDirectOther obj creation",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = inputDirectOther->initialize(hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error inputDirectOther obj init",
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
	result = movementInput->initialize(hInstance, hwnd, width, height);
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
	camera->setPosition(0.0f, 0.0f, -20.0f, 0.0f);

	//create sound obj
	sound = new SoundClass;
	if (!sound)
	{
		MessageBox(NULL, L"Error create sound obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = sound->initialize(hwnd);
	if (!result)
	{
		soundAvailable = false;
	}

	//OBJ
	//player test
	player = new playerClass;
	if (!player)
	{
		MessageBox(NULL, L"Error create player obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = player->initialize(graphics->getD3D()->GetDevice(), "playerPlane.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init player obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	player->getObj()->setMaterialName("playerMovement.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), player->getObj()->getMaterialName());
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "ShovelSpriteSheet.png");

	XMVECTOR tempBboxMax;
	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(player->getObj()->getBoundingBoxMax()) };
	player->getWeapon()->setBboxMaxWeaponRight(tempBboxMax);
	player->getWeapon()->setBboxMinWeaponRight(player->getObj()->getBoundingBoxMax());

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(player->getObj()->getBoundingBoxMin()) };
	player->getWeapon()->setBboxMaxWeaponLeft(player->getObj()->getBoundingBoxMin());
	player->getWeapon()->setBboxMinWeaponLeft(tempBboxMax);

	//Player Shadow Plane
	playerShadowPlane = new backgroundClass;
	if (!playerShadowPlane)
	{
		MessageBox(NULL, L"Error create shadowplane obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = playerShadowPlane->initlialize(graphics->getD3D()->GetDevice(), "Shadow.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init shadowplane obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	playerShadowPlane->getObj()->setMaterialName("Shadow.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), playerShadowPlane->getObj()->getMaterialName());

	//addObjectToObjHolder(playerShadowPlane->getObj());

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
	enemy->getTranslationMatStart(enemyMatPos);
	enemy->getObj()->setMaterialName("skeletonTexture.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), enemy->getObj()->getMaterialName());

	tempBboxMax = { XMVectorGetX(enemy->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(enemy->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(enemy->getObj()->getBoundingBoxMax()), XMVectorGetY(enemy->getObj()->getBoundingBoxMin()) };
	enemy->setBboxMaxWeaponRight(tempBboxMax);
	enemy->setBboxMinWeaponRight(tempBboxMin);

	tempBboxMax = { XMVectorGetX(enemy->getObj()->getBoundingBoxMin()), XMVectorGetY(enemy->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(enemy->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(enemy->getObj()->getBoundingBoxMin()) };
	enemy->setBboxMaxWeaponLeft(tempBboxMax);
	enemy->setBboxMinWeaponLeft(tempBboxMin);


	//background test
	background = new backgroundClass;
	if (!background)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = background->initlialize(graphics->getD3D()->GetDevice(), "1backgroundScene.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	background->getObj()->setMaterialName("texture3.jpg");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), background->getObj()->getMaterialName());

	//pickup test
	expFragment = new pickupClass;
	if (!expFragment)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = expFragment->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	expFragment->getObj()->setMaterialName("pixelFragmentSprite.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), expFragment->getObj()->getMaterialName());
	expFragment->getTranslationMatStart(pickupStartPosMoveMat);

	expFragment->setPickupType(3);
	expFragment->setRingType(1);

	ring = new pickupClass;
	if (!ring)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = ring->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ring->getObj()->setMaterialName("RingsSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), ring->getObj()->getMaterialName());
	ring->getTranslationMatStart(pickupStartPosMoveMat);

	//projectile test
	projectile = new projectileClass;
	if (!projectile)
	{
		MessageBox(NULL, L"Error create projectile obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = projectile->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init projectile obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	projectile->getObj()->setMaterialName("texture1.jpg");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), projectile->getObj()->getMaterialName());
	projectile->getTranslationMatStart(playerMove);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(player->getObj()->getBoundingBoxMax()) };
	projectile->setBoundingBoxMaxRight(tempBboxMax);
	projectile->setBoundingBoxMinRight(player->getObj()->getBoundingBoxMax());

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(player->getObj()->getBoundingBoxMin()) };
	projectile->setBoundingBoxMaxLeft(player->getObj()->getBoundingBoxMin());
	projectile->setBoundingBoxMinLeft(tempBboxMax);

	//GUI
	GUIheart1 = new GUItestClass;
	if (!GUIheart1)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = GUIheart1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	GUIheart1->getObj()->setWorldMatrix(heart1);
	GUIheart1->getObj()->setMaterialName("HP2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), GUIheart1->getObj()->getMaterialName());

	addHearthToHeartHolder(*GUIheart1, 1);
	addHearthToHeartHolder(*GUIheart1, 2);
	addHearthToHeartHolder(*GUIheart1, 3);
	addHearthToHeartHolder(*GUIheart1, 4);
	addHearthToHeartHolder(*GUIheart1, 5);


	heartHolder[0].setIsBought(true);
	heartHolder[0].getObj()->setWorldMatrix(heart3);
	heartHolder[1].getObj()->setWorldMatrix(heart2);
	heartHolder[2].getObj()->setWorldMatrix(heart1);
	heartHolder[3].getObj()->setWorldMatrix(heart4);
	heartHolder[4].getObj()->setWorldMatrix(heart5);



	//platform 
	platform = new platformClass;
	if (!platform)
	{
		MessageBox(NULL, L"Error create platform obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = platform->initlialize(graphics->getD3D()->GetDevice(), "1platformScene.bin");
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


	//GUI POLYGON COUNT
	slot1 = new GUItestClass;
	if (!slot1)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot1->getObj()->setWorldMatrix(slot1Mat);
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "0.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "4.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "5.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "6.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "7.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "8.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "9.png");
	slot1->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot1->getObj());
	
	//GUI POLYGON COUNT
	slot2 = new GUItestClass;
	if (!slot2)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot2->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot2->getObj()->setWorldMatrix(slot2Mat);
	slot2->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot2->getObj());
	
	//GUI RING HOLDER
	ringDisplay = new GUItestClass;
	if (!ringDisplay)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = ringDisplay->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ringDisplay->getObj()->setWorldMatrix(ringDisplayMat);
	//ringDisplay->getObj()->setMaterialName("sampleRing.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "sampleRing.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "sampleRing2.png");
	ringDisplay->setIsDestroy(true);
	ringDisplay->setCheckIfObjHolder(false);
	//addObjectToObjHolder(ringDisplay->getObj());

	//GUI RING HOLDER
	xpDisplay = new GUItestClass;
	if (!xpDisplay)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = xpDisplay->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	xpDisplay->getObj()->setWorldMatrix(xpDisplayMat);
	xpDisplay->getObj()->setMaterialName("xp0.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "xp0.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "xp1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "xp2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "xp3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "xp4.png");
	addObjectToObjHolder(xpDisplay->getObj());

	//GUI RING HOLDER
	slot1xp = new GUItestClass;
	if (!slot1xp)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot1xp->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot1xp->getObj()->setWorldMatrix(slot1xpMat);
	slot1xp->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot1xp->getObj());

	//GUI RING HOLDER
	slot2xp = new GUItestClass;
	if (!slot2xp)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot2xp->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot2xp->getObj()->setWorldMatrix(slot2xpMat);
	slot2xp->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot2xp->getObj());

	//////////////////////////
	//		MENY			//
	//////////////////////////

	meny = new GUItestClass;
	if (!meny)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = meny->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	meny->getObj()->setWorldMatrix(menyMat);
	meny->getObj()->setMaterialName("textureMeny.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), meny->getObj()->getMaterialName());

	menyHighlight = new GUItestClass;
	if (!menyHighlight)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = menyHighlight->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	menyHighlight->getObj()->setWorldMatrix(menyHighlightMat);
	menyHighlight->getObj()->setMaterialName("textureMenyOverlay.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), menyHighlight->getObj()->getMaterialName());
	addObjectToObjHolderMeny(menyHighlight->getObj());
	addObjectToObjHolderMeny(meny->getObj());


	//////////////////////////
	//////	 LIMBO		//////
	//////////////////////////

	limboPickupHolder = new pickupClass[2];

	//LIMBO BACK PLANE
	limboBackPlane = new backgroundClass;
	if (!limboBackPlane)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limboBackPlane->initlialize(graphics->getD3D()->GetDevice(), "LimboBackPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limboBackPlane->getObj()->setMaterialName("LimboBack.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboBackPlane->getObj()->getMaterialName());
	
	
	addObjectToObjHolderLimbo(limboBackPlane->getObj());

	//LIMBO Smith PLANE
	limboSmithPlane = new pickupClass;
	if (!limboSmithPlane)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limboSmithPlane->initlialize(graphics->getD3D()->GetDevice(), "LimboSmithPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limboSmithPlane->getObj()->setMaterialName("SmithSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboSmithPlane->getObj()->getMaterialName());

	limboPickupHolder[0].clone(*limboSmithPlane);
	limboPickupHolder[0].setFrameCount(2);
	limboPickupHolder[0].setAnimationCount(1);
	limboPickupHolder[0].setPickupType(5);

	addObjectToObjHolderLimbo(limboPickupHolder[0].getObj());

	//collisionPlane
	limboWalkingPlane = new platformClass;
	if (!limboWalkingPlane)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limboWalkingPlane->initlialize(graphics->getD3D()->GetDevice(), "LimboPlatform.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limboWalkingPlane->getObj()->setMaterialName("Shadow.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboWalkingPlane->getObj()->getMaterialName());

	addObjectToObjHolderLimbo(limboWalkingPlane->getObj());
	addObjectToObjHolderLimbo(player->getObj());

	//LIMBO FRONT PLANE
	limboFrontPlane = new backgroundClass;
	if (!limboFrontPlane)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limboFrontPlane->initlialize(graphics->getD3D()->GetDevice(), "LimboFrontPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limboFrontPlane->getObj()->setMaterialName("LimboFront.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboFrontPlane->getObj()->getMaterialName());

	addObjectToObjHolderLimbo(limboFrontPlane->getObj());

	//LIMBO Text PLANE
	limboTextPlane = new pickupClass;
	if (!limboTextPlane)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limboTextPlane->initlialize(graphics->getD3D()->GetDevice(), "LimboTextPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limboTextPlane->getObj()->setMaterialName("SmithText.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboTextPlane->getObj()->getMaterialName());

	limboPickupHolder[1].clone(*limboTextPlane);
	limboPickupHolder[1].setFrameCount(1);
	limboPickupHolder[1].setAnimationCount(1);
	limboPickupHolder[1].setPickupType(4);

	addObjectToObjHolderLimbo(limboPickupHolder[1].getObj());

	//LIMBO UPGRADE
	upgradeGUI = new GUItestClass;
	if (!upgradeGUI)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = upgradeGUI->initlialize(graphics->getD3D()->GetDevice(), "LimboUpgradePlane.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	upgradeGUI->getObj()->setWorldMatrix(XMMatrixIdentity());
	upgradeGUI->getObj()->setMaterialName("WeaponsBase.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeGUI->getObj()->getMaterialName());
	upgradeGUI->getObj()->setMaterialName("StatsBase.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeGUI->getObj()->getMaterialName());
	upgradeGUI->setIsDestroy(true);
	upgradeGUI->getObj()->setType(3);

	
	//addObjectToObjHolderLimbo(upgradeGUI->getObj());

	//LIMBO UPGRADE OVERLAY
	upgradeOverlay = new GUItestClass;
	if (!upgradeOverlay)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = upgradeOverlay->initlialize(graphics->getD3D()->GetDevice(), "LimboUpgradePlane.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	upgradeOverlay->getObj()->setWorldMatrix(XMMatrixIdentity());
	upgradeOverlay->getObj()->setMaterialName("StatsSelected2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("CancelSelected.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("TabArrows.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("ConfirmSelected.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("LeftArrowSelected1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("Selected1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("Selected2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("Selected3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "Owned1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "Owned2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "Owned3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "Owned4.png");

	upgradeOverlay->getObj()->setMaterialName("Selected4.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->getObj()->setMaterialName("StatsSelected1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getMaterialName());
	upgradeOverlay->setIsDestroy(true);
	upgradeOverlay->getObj()->setType(3);
	//addObjectToObjHolderLimbo(upgradeOverlay->getObj());


	//
	//HEalth count
	healthUpgradeCount = new GUItestClass;
	if (!healthUpgradeCount)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = healthUpgradeCount->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	healthUpgradeCount->getObj()->setWorldMatrix(healthUpgradeCountMat);
	healthUpgradeCount->getObj()->setMaterialName("0.png");
	healthUpgradeCount->setIsDestroy(true);

	//speed count
	speedUpgradeCount = new GUItestClass;
	if (!speedUpgradeCount)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = speedUpgradeCount->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	speedUpgradeCount->getObj()->setWorldMatrix(speedUpgradeCountMat);
	speedUpgradeCount->getObj()->setMaterialName("0.png");
	speedUpgradeCount->setIsDestroy(true);


	//TOTAL COST PENDING
	totalCostPendingSlot1 = new GUItestClass;
	if (!totalCostPendingSlot1)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = totalCostPendingSlot1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	totalCostPendingSlot1->getObj()->setWorldMatrix(totalCostPendingSlot1Mat);
	totalCostPendingSlot1->getObj()->setMaterialName("0.png");
	totalCostPendingSlot1->setIsDestroy(true);

	//speed count
	totalCostPendingSlot2 = new GUItestClass;
	if (!totalCostPendingSlot2)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = totalCostPendingSlot2->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	totalCostPendingSlot2->getObj()->setWorldMatrix(totalCostPendingSlot2Mat);
	totalCostPendingSlot2->getObj()->setMaterialName("0.png");
	totalCostPendingSlot2->setIsDestroy(true);

	////////////////////////
	//WIN				////
	////////////////////////
	win = new GUItestClass;
	if (!win)
	{
		MessageBox(NULL, L"Error create win obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = win->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
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
	initializeRings();

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

	if (dt)
	{
		delete dt;
		dt = 0;
	}

	if (camera)
	{
		delete camera;
		camera = 0;
	}
	if (xpDisplay)
	{
		xpDisplay->shutdown();
		delete xpDisplay;
		xpDisplay = 0;
	}


	if (sound)
	{
		sound->shutdown();
		delete sound;
		sound = 0;
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
	if (ringDisplay)
	{
		ringDisplay->shutdown();
		delete ringDisplay;
		ringDisplay = 0;
	}
	if (expFragment)
	{
		expFragment->shutdown();
		delete expFragment;
		expFragment = 0;
	}
	if (slot2xp)
	{
		slot2xp->shutdown();
		delete slot2xp;
		slot2xp = 0;
	}
	if (slot1xp)
	{
		slot1xp->shutdown();
		delete slot1xp;
		slot1xp = 0;
	}
	if (speedUpgradeCount)
	{
		speedUpgradeCount->shutdown();
		delete speedUpgradeCount;
		speedUpgradeCount = 0;
	}
	if (healthUpgradeCount)
	{
		healthUpgradeCount->shutdown();
		delete healthUpgradeCount;
		healthUpgradeCount = 0;
	}
	if (ring)
	{
		ring->shutdown();
		delete ring;
		ring = 0;
	}
	if (pickupHolder)
	{
		for (int i = 0; i < nrOfVisiblePickups; i++)
		{
			pickupHolder[i].shutdown();
		}
		delete[] pickupHolder;
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
	if (heartHolder)
	{
		for (int i = 0; i < 5; i++)
		{
			heartHolder[i].shutdown();
		}

		delete[] heartHolder;
	}
	if (totalCostPendingSlot2)
	{
		totalCostPendingSlot2->shutdown();
		delete totalCostPendingSlot2;
		totalCostPendingSlot2 = 0;
	}
	if (totalCostPendingSlot1)
	{
		totalCostPendingSlot1->shutdown();
		delete totalCostPendingSlot1;
		totalCostPendingSlot1 = 0;
	}
	if (meny)
	{
		meny->shutdown();
		delete meny;
		meny = 0;
	}
	if (limboFrontPlane)
	{
		limboFrontPlane->shutdown();
		delete limboFrontPlane;
		limboFrontPlane = 0;
	}
	if (limboBackPlane)
	{
		limboBackPlane->shutdown();
		delete limboBackPlane;
		limboBackPlane = 0;
	}
	if (limboSmithPlane)
	{
		limboSmithPlane->shutdown();
		delete limboSmithPlane;
		limboSmithPlane = 0;
	}
	if (limboTextPlane)
	{
		limboTextPlane->shutdown();
		delete limboTextPlane;
		limboTextPlane = 0;
	}

	if (limboPickupHolder)
	{
		for (int i = 0; i < 2; i++)
		{
			limboPickupHolder[i].shutdown();
		}
		delete[] limboPickupHolder;
		limboPickupHolder = 0;
	}
	if (win)
	{
		win->shutdown();
		delete win;
		win = 0;
	}
	if (slot1)
	{
		slot1->shutdown();
		delete slot1;
		slot1 = 0;
	}
	if (slot2)
	{
		slot2->shutdown();
		delete slot2;
		slot2 = 0;
	}
	if (upgradeOverlay)
	{
		upgradeOverlay->shutdown();
		delete upgradeOverlay;
		upgradeOverlay = 0;
	}
	if (upgradeGUI)
	{
		upgradeGUI->shutdown();
		delete upgradeGUI;
		upgradeGUI = 0;
	}

	if (limboWalkingPlane)
	{
		limboWalkingPlane->shutdown();
		delete limboWalkingPlane;
		limboWalkingPlane = 0;
	}
	if (projectile)
	{
		projectile->shutdown();
		delete projectile;
		projectile = 0;
	}

	if (playerShadowPlane)
	{
		playerShadowPlane->shutdown();
		delete playerShadowPlane;
		playerShadowPlane = 0;
	}
	if (menyHighlight)
	{
		menyHighlight->shutdown();
		delete menyHighlight;
		menyHighlight = 0;
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
			else if (gameStateMeny)
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
		result = graphics->frame(objHolderWin[i], view, proj, objHolderWin[i]->getType(), objHolderWin[i]->getMaterialName(), camera->getPosition(), 0);
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

		if (soundAvailable)
			sound->playAmbient(0);
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

	checkReleasedKeys();

	//constant MATRICES
	updateConstantMatrices();
	graphics->getD3D()->getOrtoProjMat(ortoProj);

	//enviroment
	updateLimboBackground();

	//GUI
	updateSlotXp(slot1xpMatLimbo, slot2xpMatLimbo);
	updateGUIPolygon(slot1MatLimbo, slot2MatLimbo);
	updateCountersShop();
	pendingCostUpdate();

	//updateShopMats
	updateShopWorldMat();

	//player
	updatePlayer(limboWalkingPlane, dt);

	for (int i = 0; i < 2; i++)
	{
		limboPickupHolder[i].updateAnimation(dt);
	}

	//shop
	updateShop(dt, upgradeGUI, upgradeOverlay);

	graphics->beginScene();

	int pickupCheck = 0;
	for (int i = 0; i < objHolderLimbo.size(); i++)
	{
		if (objHolderLimbo[i]->getType() == 2)
		{
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), camera->getPosition(), 0, player->getFrameCount(), player->getCurrentFrame(), player->getCurrentAnimation(), player->getFlipped());
			if (!result)

			{
				return false;
			}
		}

		else if (objHolderLimbo[i]->getType() == 4)
		{
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), camera->getPosition(), 0, limboPickupHolder[pickupCheck].getFrameCount(), limboPickupHolder[pickupCheck].getCurrentFrame());
			pickupCheck++;
			if (!result)
			{
				return false;
			}
		}

		else if (objHolderLimbo[i]->getType() == 3) {
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), camera->getPosition(), 2);
			if (!result)
			{
				return false;
			}

		}

		else
		{
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), camera->getPosition(), 0);
			if (!result)

			{
				return false;
			}
		}
	}
	graphics->endScene();

	if (player->getMoveValY() < -30.0f)
	{
		gameStateLevel = true;
		gameStateLimbo = false;
		gameStateMeny = false;
		player->resetPlayer();
		upgradeGUI->setIsDestroy(true);

		upgradeOverlay->setIsDestroy(true);
		setShopOverlayCounter(0);
		setShopOverlayCounterRow(0);
		activeShopState = 0;

		if (soundAvailable)
			sound->playAmbient(1);

		std::ofstream myfile;
		myfile.open("readThis.txt");
		myfile << std::to_string(player->getMaxHP()) + "\n";
		myfile << std::to_string(player->getSpeedVal()) + "\n";
		myfile << std::to_string(SpeedCost) + "\n";
		myfile << std::to_string(healthCost) + "\n";
		myfile.close();


		return false;
	}
	if (inputDirectOther->isEscapePressed() == true)
	{
		gameStateLevel = false;
		gameStateLimbo = false;
		gameStateMeny = true;
		player->resetPlayer();
		upgradeGUI->setIsDestroy(true);

		upgradeOverlay->setIsDestroy(true);
		setShopOverlayCounter(0);
		setShopOverlayCounterRow(0);
		activeShopState = 0;

		if (soundAvailable)
			sound->playAmbient(0);

		return false;
	}

	return true;
}

//where all the processing for our app is done here. right now it checks if user has precces anything. if its escape then quit. if no then we call our graphics obj to do its frame processing and render the graphics for the frame
bool gameClass::frameGame(double dt)
{
	//DO STUFFS
	bool result;

	checkReleasedKeys();

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

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		if (!pickupHolder[i].getIsDestry() && !pickupHolder[i].getCheckIfObjHolder())
		{
			addObjectToObjHolder(pickupHolder[i].getObj());
			pickupHolder[i].setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);
		}
	}

	if (pickupHolder)
	{
		//pickup stuff
		updatePickup(dt);
	}

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		if (pickupHolder[i].getIsDestry() && pickupHolder[i].getCheckIfObjHolder())
		{
			removeObjFromObjHolder(pickupHolder[i].getObj());
			pickupHolder[i].setCheckIfObjHolder(false);
			nrOfVisiblePickups--;
			removePickupFromPickupHolder(pickupHolder[i], nrOfVisiblePickups);
			i = 0;
		}
	}

	//player stuff
	updatePlayer(platform, dt);

	//projectile stuff
	if (!projectile->getIsDestroyed() && !projectile->getCheckIfObjHolder() && player->getFireballCast())
	{
		addObjectToObjHolder(projectile->getObj());
		projectile->setCheckIfObjHolder(true);
		player->setIfInObjHolder(false);
		//Set start pos and direction
		projectile->setTranslationMatStart(playerMove);
		if (player->getFlipped() == true)
		{
			projectile->setGoesRight(false);
		}
	}

	if (!projectile->getIsDestroyed() && projectile->getCheckIfObjHolder() && player->getFireballCast())
	{
		updateProjectile(dt);
	}

	//update player shadow
	updatePlayerShadow();

	//update plygonscout GUI
	updateRingDisplay();
	updateXpDisplayMat();
	updateSlotXp(slot1xpMat, slot2xpMat);
	updateGUIPolygon(slot1Mat, slot2Mat);

	//set camera to follow player
	updateCamera();

	//om enemy hör på sig
	updateCollision(dt);

	if (!player->getIfInObjHolder())
	{
		addObjectToObjHolder(player->getObj());
		player->setIfInObjHolder(true);
	}

	//initialize starting HP
	//breaks here because player HP is 3 when it's suppose to be 2.
	//every hearth that is created will forfill this criteria
	for (int i = 0; i < player->getPlayerHP(); i++)
	{
		if (!heartHolder[i].getIsDestry() && !heartHolder[i].getCheckIfObjHolder() && heartHolder[i].getIsBought())
		{
			addObjectToObjHolder(heartHolder[i].getObj());
			heartHolder[i].setCheckIfObjHolder(true);
			OutputDebugString(L"\nheart was created2!\n");
		}
	}


	//for render
	int pickupTypeChecker = 0;
	graphics->beginScene();
	for (int i = 0; i < objHolder.size(); i++)
	{
		if (objHolder[i]->getType() == 2)
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), camera->getPosition(), 0, player->getFrameCount(), player->getCurrentFrame(), player->getCurrentAnimation(), player->getFlipped());
			if (!result)

			{
				return false;
			}
		}

		else if (objHolder[i]->getType() == 4)
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), camera->getPosition(), 0, pickupHolder[pickupTypeChecker].getFrameCount(), pickupHolder[pickupTypeChecker].getCurrentFrame());
			if (!result)
			{
				return false;
			}
			pickupTypeChecker++;
		}

		else if (objHolder[i]->getType() == 3) {
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), camera->getPosition(), enemy->getHurt());
			if (!result)
			{
				return false;
			}

		}

		else
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), camera->getPosition(), 0);
			if (!result)

			{
				return false;
			}
		}
	}
	graphics->endScene();


	/*if (enemy->getEnemyHP() == 0)
	{
	player->resetPlayer();
	pickupHolder[0].resetPickup();
	enemy->resetEnemy();
	projectile->resetProjectile();
	for (int i = 0; i < 3; i++)
	{
	heartHolder[i].resetGUI();
	}

	gameStateLevel = false;
	gameStateMeny = false;
	gameStateLimbo = false;
	gameStateWin = true;
	return false;
	}*/

	if (player->getPlayerHP() == 0)
	{
		player->resetPlayer();
		camera->reset();
		if (pickupHolder)
		{
			for (int i = 0; i < nrOfVisiblePickups; i++)
			{
				pickupHolder[i].resetPickup();
			}
		}
		initializeRings();
		enemy->resetEnemy();
		projectile->resetProjectile();
		for (int i = 0; i < 5; i++)
		{
			heartHolder[i].resetGUI();
		}
		slot1->setIsDestroy(true);
		slot2->setIsDestroy(true);
		slot1xp->setIsDestroy(true);
		slot2xp->setIsDestroy(true);
		ringDisplay->setIsDestroy(true);
		gameStateLevel = false;
		gameStateMeny = false;
		gameStateWin = false;
		gameStateLimbo = true;

		if (soundAvailable)
			sound->playAmbient(2);
		
		return false;
	}

	if (inputDirectOther->isEscapePressed() == true)
	{
		player->resetPlayer();
		if (pickupHolder)
		{
			for (int i = 0; i < nrOfVisiblePickups; i++)
			{
				pickupHolder[i].resetPickup();
			}
		}
		ringDisplay->setIsDestroy(true);
		initializeRings();
		enemy->resetEnemy();
		slot1->setIsDestroy(true);
		slot2->setIsDestroy(true);
		slot1xp->setIsDestroy(true);
		slot2xp->setIsDestroy(true);
		projectile->resetProjectile();

		camera->reset();

		for (int i = 0; i < 5; i++)
		{
			heartHolder[i].resetGUI();
		}

		gameStateLevel = false;
		gameStateMeny = true;
		gameStateWin = false;
		gameStateLimbo = false;

		if (soundAvailable)
			sound->playAmbient(0);

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

	if (firstFrame && soundAvailable)
	{
	sound->playAmbient(0);
	firstFrame = false;
	}

	checkReleasedKeys();
	//constant MATRICES
	updateConstantMatrices();

	//overlay
	updateOverlay();

	graphics->beginScene();
	for (int i = 0; i < objHolderMeny.size(); i++)
	{
		result = graphics->frame(objHolderMeny[i], view, proj, objHolderMeny[i]->getType(), objHolderMeny[i]->getMaterialName(), camera->getPosition(), 0);
		if (!result)

		{
			return false;
		}
	}
	graphics->endScene();

	if (inputDirectOther->isEnterPressed() &&  counterOverlay == 0)
	{
		gameStateLevel = true;
		if (soundAvailable)
			sound->playAmbient(1);
		player->setPlayerHP(1);
		player->setMaxHP(1);
		player->setSpeedVal(10);
	}

	if (inputDirectOther->isEnterPressed() && counterOverlay == 1)
	{
		gameStateLevel = true;
		std::string line;
		int arr[4] = { 0,0 };
		int i = 0;
		std::ifstream myfile("readThis.txt");
		if (myfile.is_open())
		{
			OutputDebugString(L"\nMyFile!\n");
			while (std::getline(myfile, line))
			{
				arr[i] = std::stoi(line);
				i++;
			}
			myfile.close();
		}
		player->setPlayerHP(arr[0]);
		player->setMaxHP(player->getPlayerHP());
		player->setSpeedVal(arr[1]);
		SpeedCost = arr[2];
		healthCost = arr[3];
	}

	if (inputDirectOther->isEnterPressed() == true && counterOverlay == 3)
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
	return DefWindowProc(hwnd, umessage, wparam, lparam);
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

void gameClass::addHearthToHeartHolder(GUItestClass &heart, int playerHP)
{
	GUItestClass* tempArray = new GUItestClass[playerHP];

	for (int i = 0; i < playerHP - 1; i++)
	{
		tempArray[i] = heartHolder[i];
	}

	delete[] heartHolder;

	heartHolder = tempArray;
	heartHolder[playerHP - 1].clone(heart);
}

void gameClass::removeHearthFromHeartHolder(GUItestClass hearth, int playerHP)
{
	int index = -1;
	for (int i = 0; i < playerHP + 1; i++)
	{
		if (heartHolder[i].getObj() == hearth.getObj())
		{
			index = i;
		}
	}

	if (index != -1)
	{
		GUItestClass* tempArray = new GUItestClass[playerHP];
		int j = 0;
		for (int i = 0; i < playerHP - 1; i++)
		{
			if (i != index)
			{
				tempArray[j] = heartHolder[i];
				j++;
			}
		}

		delete[] heartHolder;
		heartHolder = tempArray;
	}
}

void gameClass::addPickupToPickupHolder(pickupClass &pickup, int nrOfVisiblePickups)
{
	pickupClass* tempArray = new pickupClass[nrOfVisiblePickups];

	for (int i = 0; i < nrOfVisiblePickups - 1; i++)
	{
		tempArray[i] = pickupHolder[i];
	}
	OutputDebugString(L"\npickup created!\n");

	delete[] pickupHolder;

	pickupHolder = tempArray;
	pickupHolder[nrOfVisiblePickups - 1].clone(pickup);
}

void gameClass::removePickupFromPickupHolder(pickupClass & pickup, int nrOfVisiblePickups)
{
	int index = -1;
	for (int i = 0; i < nrOfVisiblePickups + 1; i++)
	{
		if (pickupHolder[i].getObj() == pickup.getObj())
		{
			index = i;
		}
	}

	if (index != -1)
	{
		pickupClass* tempArray = new pickupClass[nrOfVisiblePickups];
		pickupHolder[index].shutdown();
		int j = 0;
		for (int i = 0; i < nrOfVisiblePickups + 1; i++)
		{
			if (i != index)
			{
				OutputDebugString(L"\nTransferring\n");
				tempArray[j] = pickupHolder[i];
				j++;
			}
		}

		delete[] pickupHolder;
		pickupHolder = tempArray;
	}
}

void gameClass::initializeRings()
{
	for (int i = 0; i < 1; i++)
	{
		srand(time(NULL));
		pickupClass ringTemp;
		ringTemp.clone(*ring);
		nrOfVisiblePickups++;
		addPickupToPickupHolder(ringTemp, nrOfVisiblePickups);
		pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(XMMatrixScaling(0.3f, 0.5f, 0.0f) * XMMatrixTranslation(-30.0f + (i * 10), 1.6f, 0.1f));
		pickupHolder[nrOfVisiblePickups - 1].setPickupType(3);
		pickupHolder[nrOfVisiblePickups - 1].setRingType(rand() % 2);
		if (pickupHolder[nrOfVisiblePickups - 1].getRingType() == 1)
		{
			OutputDebugString(L"\n1\n");
		}
		if (pickupHolder[nrOfVisiblePickups - 1].getRingType() == 0)
		{
			OutputDebugString(L"\n0\n");
		}
		pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
		pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
		ringTemp.shutdown();
	}
}

void gameClass::checkReleasedKeys()
{
	if (!inputDirectOther->isEnterPressed())
		enterReleased = true;
	if (!inputDirectOther->isArrowDownPressed())
		arrowDownReleased = true;
	if (!inputDirectOther->isArrowUpPressed())
		arrowUpReleased = true;
	if (!inputDirectOther->isArrowLeftPressed())
		arrowLeftReleased = true;
	if (!inputDirectOther->isArrowRightPressed())
		arrowRightReleased = true;
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
	enemy->updateFalling(dt);
	enemy->getObj()->setWorldMatrix(enemyMatPos);
	enemy->getTranslationMat(matMul);
	enemy->getFallingMat(enemyFallingMat);
	if (!enemy->getRoationCheck())
	{
		masterMovementEnemyMat = enemyFallingMat * matMul * enemyMatPos;
		enemyTranslationMatrix = enemyFallingMat * matMul * enemyMatPos;
	}
	else
	{
		masterMovementEnemyMat = XMMatrixRotationY(-3.1514f) * enemyFallingMat * matMul * enemyMatPos;
		enemyTranslationMatrix = enemyFallingMat * matMul * enemyMatPos;
	}
	enemy->getObj()->setWorldMatrix(masterMovementEnemyMat);
	///////////////
	enemy->checkCollisionsY(checkCollisionPlatformTop(platform, enemy->getObj(), enemyTranslationMatrix), checkCollisionPlatformBot(platform, enemy->getObj(), enemyTranslationMatrix));
	enemy->checkCollisionsX(checkCollisionPlatformLeft(platform, enemy->getObj(), enemyTranslationMatrix), checkCollisionPlatformRight(platform, enemy->getObj(), enemyTranslationMatrix));
	enemy->getObj()->setWorldMatrix(enemyMatPos);
	enemy->getTranslationMat(matMul);
	enemy->getFallingMat(enemyFallingMat);
	if (!enemy->getRoationCheck())
	{
		masterMovementEnemyMat = enemyFallingMat * matMul * enemyMatPos;
		enemyTranslationMatrix = enemyFallingMat * matMul * enemyMatPos;
	}
	else
	{
		masterMovementEnemyMat = XMMatrixRotationY(-3.1514f) * enemyFallingMat * matMul * enemyMatPos;
		enemyTranslationMatrix = enemyFallingMat * matMul * enemyMatPos;
	}
	enemy->getObj()->setWorldMatrix(masterMovementEnemyMat);
}

void gameClass::updatePlayer(platformClass* platform, double dt)
{
	player->handleMovement(dt);
	player->updateAnimation(dt);
	player->getMoveMat(playerMove);
	player->getObj()->setWorldMatrix(playerMove);
	player->checkCollisions(checkCollisionPlatformTop(platform, player->getObj(), playerMove), checkCollisionPlatformLeft(platform, player->getObj(), playerMove), checkCollisionPlatformRight(platform, player->getObj(), playerMove), checkCollisionPlatformBot(platform, player->getObj(), playerMove));
	player->getMoveMat(playerMove);
	player->getObj()->setWorldMatrix(playerMove);

}

void gameClass::updatePlayerShadow()
{

	//Om vi inte hopppar/faller
	if (player->getShowShadow() == true)
	{
		//Om skuggan inte redan finns
		if (playerShadowPlane->getIsInObjHolder() == false) {
			//Render shadow
			addObjectToObjHolder(playerShadowPlane->getObj());
			playerShadowPlane->setIsInObjHolder(true);

			//Then render player
			player->setIfInObjHolder(false);
			removeObjFromObjHolder(player->getObj());
		}
		//Update shadow position
		playerShadowPlane->getObj()->setWorldMatrix(playerMove);
		XMMATRIX offset = XMMatrixTranslation(0.0f, -1.315f, 0.0f);
		playerShadowPlane->getObj()->setWorldMatrix(playerMove * offset);
	}
	//Om skuggan inte ska synas
	else
	{
		//Ta bort skuggan

		playerShadowPlane->setIsInObjHolder(false);
		removeObjFromObjHolder(playerShadowPlane->getObj());
	}
}

void gameClass::updateCamera()
{
	float useThisX = XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)))/ 2);
	//float useThisX = XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + differenceX;

	float useThisY = XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)));
	//int useThisY = XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + differenceX;

	if (useThisX > -147 && useThisX <= 10)
	{
		camera->updatePosition(useThisX, useThisY);
		camera->updateTarget(useThisX, useThisY);
		camera->setTempX(useThisX);
		camera->setTempY(useThisY);
	}
	else if (XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)) <= -147)
	{
		camera->updatePosition(camera->getTempX(), useThisY);
		camera->updateTarget(camera->getTempX(), useThisY);
	}
	else if (XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)) <= 10)
	{
		camera->updatePosition(camera->getTempX(), useThisY);
		camera->updateTarget(camera->getTempX(), useThisY);
	}

}

void gameClass::staticBackground()
{
	backgroundMat = XMMatrixIdentity();
	background->getObj()->setWorldMatrix(backgroundMat);
}

void gameClass::updateGUIPolygon(XMMATRIX mat1, XMMATRIX mat2)
{
	if (player->getNrPolygons() == 0 || player->getNrPolygons() >= 10)
	{
		if(player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("0.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 1 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("1.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 2 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("2.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 3 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("3.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 4 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("4.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 5 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("5.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 6 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("6.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 7 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("7.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 8 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("8.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() == 9 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
			slot1->getObj()->setMaterialName("9.png");
		if (player->getNrPolygons() > 9)
		{
			int temp = player->getNrPolygons() % 10;
			std::string tempString = std::to_string(temp);
			slot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPolygons() > 9)
	{
		int temp = player->getNrPolygons() / 10;
		std::string tempString = std::to_string(temp);
		slot2->getObj()->setMaterialName(tempString + ".png");
	}
	slot1->getObj()->setWorldMatrix(mat1);
	slot2->getObj()->setWorldMatrix(mat2);
}

void gameClass::updateRingDisplay()
{
	ringDisplay->getObj()->setWorldMatrix(ringDisplayMat);
}

void gameClass::updateXpDisplayMat()
{
	if (tempXP == 0)
	{

		xpDisplay->getObj()->setMaterialName("xp0.png");

	}
	if (tempXP == 1)
	{

		xpDisplay->getObj()->setMaterialName("xp1.png");


	}
	if (tempXP == 2)
	{
		xpDisplay->getObj()->setMaterialName("xp2.png");
	}
	if (tempXP == 3)
	{
		xpDisplay->getObj()->setMaterialName("xp3.png");
	}
	if (tempXP == 4)
	{
		xpDisplay->getObj()->setMaterialName("xp4.png");
	}
	
	xpDisplay->getObj()->setWorldMatrix(xpDisplayMat);
}

void gameClass::updateSlotXp(XMMATRIX mat1, XMMATRIX mat2)
{
	if (player->getNrPixelFramgent() == 0 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("0.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 1 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("1.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 2 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("2.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 3 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("3.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 4 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("4.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 5 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("5.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 6 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("6.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 7 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("7.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 8 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("8.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (player->getNrPixelFramgent() == 9 || player->getNrPixelFramgent() >= 10)
	{
		if (player->getNrPixelFramgent() <= 9)
			slot1xp->getObj()->setMaterialName("9.png");
		if (player->getNrPixelFramgent() > 9)
		{
			int temp = player->getNrPixelFramgent() % 10;
			std::string tempString = std::to_string(temp);
			slot1xp->getObj()->setMaterialName(tempString + ".png");
		}
	}

	int temp = player->getNrPixelFramgent() / 10;
	std::string tempString = std::to_string(temp);
	slot2xp->getObj()->setMaterialName(tempString + ".png");
	
	slot1xp->getObj()->setWorldMatrix(mat1);
	slot2xp->getObj()->setWorldMatrix(mat2);
}

void gameClass::setCounterOverlay(int other)
{
	this->counterOverlay = other;
}

int gameClass::getCounterOverlay()
{
	return this->counterOverlay;
}

//MENY
void gameClass::updateOverlay()
{
	//MENY
	if (inputDirectOther->isArrowDownPressed() && arrowDownReleased && getCounterOverlay() < 3)
	{
		menyHighlightMat = menyHighlightMat * XMMatrixTranslation(0.0f, -0.21f, 0.0f);
		setCounterOverlay(getCounterOverlay() + 1);
		arrowDownReleased = false;
		if (soundAvailable)
			sound->playSFX(0, 0);
	}
	if (inputDirectOther->isArrowUpPressed() && arrowUpReleased && getCounterOverlay() > 0)
	{
		menyHighlightMat = menyHighlightMat * XMMatrixTranslation(0.0f, 0.21f, 0.0f);
		setCounterOverlay(getCounterOverlay() - 1);
		arrowUpReleased = false;
		if (soundAvailable)
			sound->playSFX(0, 0);
	}
	menyHighlight->getObj()->setWorldMatrix(menyHighlightMat);
}

void gameClass::updateLimboBackground()
{
	limboMat = XMMatrixIdentity();

	for (int i = 0; i < 2; i++)
	{
		limboPickupHolder[i].getObj()->setWorldMatrix(limboMat);
	}
	limboBackPlane->getObj()->setWorldMatrix(limboMat);
	limboFrontPlane->getObj()->setWorldMatrix(limboMat);
	limboWalkingPlane->getObj()->setWorldMatrix(limboMat);
}

void gameClass::updateCountersShop()
{
	if (activeShopState != 0)
	{
		healthUpgradeCount->setIsDestroy(true);
		speedUpgradeCount->setIsDestroy(true);
	}
	
	if (!healthUpgradeCount->getIsDestry())
	{
		if (nrHPtoBeUpgraded == 0)
		{
			healthUpgradeCount->getObj()->setMaterialName("0.png");
		}
		if (nrHPtoBeUpgraded == 1)
		{
			healthUpgradeCount->getObj()->setMaterialName("1.png");
		}
		if (nrHPtoBeUpgraded == 2)
		{
			healthUpgradeCount->getObj()->setMaterialName("2.png");
		}
		if (nrHPtoBeUpgraded == 3)
		{
			healthUpgradeCount->getObj()->setMaterialName("3.png");
		}
		if (nrHPtoBeUpgraded == 4)
		{
			healthUpgradeCount->getObj()->setMaterialName("4.png");
		}
		if (nrHPtoBeUpgraded == 5)
		{
			healthUpgradeCount->getObj()->setMaterialName("5.png");
		}
		if (nrHPtoBeUpgraded == 6)
		{
			healthUpgradeCount->getObj()->setMaterialName("6.png");
		}
		if (nrHPtoBeUpgraded == 7)
		{
			healthUpgradeCount->getObj()->setMaterialName("7.png");
		}
		if (nrHPtoBeUpgraded == 8)
		{
			healthUpgradeCount->getObj()->setMaterialName("8.png");
		}
		if (nrHPtoBeUpgraded == 9)
		{
			healthUpgradeCount->getObj()->setMaterialName("9.png");
		}

		healthUpgradeCount->getObj()->setWorldMatrix(healthUpgradeCountMat);
	}

	if (!speedUpgradeCount->getIsDestry())
	{
		if (nrSpeedToBeUpgraded == 0)
		{
			speedUpgradeCount->getObj()->setMaterialName("0.png");
		}
		if (nrSpeedToBeUpgraded == 1)
		{
			speedUpgradeCount->getObj()->setMaterialName("1.png");
		}
		if (nrSpeedToBeUpgraded == 2)
		{
			speedUpgradeCount->getObj()->setMaterialName("2.png");
		}
		if (nrSpeedToBeUpgraded == 3)
		{
			speedUpgradeCount->getObj()->setMaterialName("3.png");
		}
		if (nrSpeedToBeUpgraded == 4)
		{
			speedUpgradeCount->getObj()->setMaterialName("4.png");
		}
		if (nrSpeedToBeUpgraded == 5)
		{
			speedUpgradeCount->getObj()->setMaterialName("5.png");
		}
		if (nrSpeedToBeUpgraded == 6)
		{
			speedUpgradeCount->getObj()->setMaterialName("6.png");
		}
		if (nrSpeedToBeUpgraded == 7)
		{
			speedUpgradeCount->getObj()->setMaterialName("7.png");
		}
		if (nrSpeedToBeUpgraded == 8)
		{
			speedUpgradeCount->getObj()->setMaterialName("8.png");
		}
		if (nrSpeedToBeUpgraded == 9)
		{
			speedUpgradeCount->getObj()->setMaterialName("9.png");
		}
		speedUpgradeCount->getObj()->setWorldMatrix(speedUpgradeCountMat);
	}
}

void gameClass::pendingCostUpdate()
{
	if (totalPendingCost == 0 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("0.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 1 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("1.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 2 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("2.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 3 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("3.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 4 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("4.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 5 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("5.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 6 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("6.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 7 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("7.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 8 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("8.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost == 9 || totalPendingCost >= 10)
	{
		if (totalPendingCost <= 9)
			totalCostPendingSlot1->getObj()->setMaterialName("9.png");
		if (totalPendingCost > 9)
		{
			int temp = totalPendingCost % 10;
			std::string tempString = std::to_string(temp);
			totalCostPendingSlot1->getObj()->setMaterialName(tempString + ".png");
		}
	}
	if (totalPendingCost > 9)
	{
		int temp = totalPendingCost / 10;
		std::string tempString = std::to_string(temp);
		totalCostPendingSlot2->getObj()->setMaterialName(tempString + ".png");
	}
	if (totalPendingCost <= 9)
	{
		totalCostPendingSlot2->getObj()->setMaterialName("0.png");
	}
	totalCostPendingSlot1->getObj()->setWorldMatrix(totalCostPendingSlot1Mat);
	totalCostPendingSlot2->getObj()->setWorldMatrix(totalCostPendingSlot2Mat);
}

void gameClass::updateShopWorldMat()
{
	upgradeGUI->getObj()->setWorldMatrix(shopMat);
	//overlay updateTabArrows

	if (inputDirectOther->isArrowLeftPressed() && arrowLeftReleased && getShopOverlayCounter() == -1 && activeShopState > 0 && upgradeOvlerlayCounterWeapons == -1)
	{
		activeShopState -= 1;
		arrowLeftReleased = false;
	}
	if (inputDirectOther->isArrowRightPressed() && arrowRightReleased  && getShopOverlayCounter() == -1 && activeShopState < 1 && upgradeOvlerlayCounterWeapons == -1)
	{
		activeShopState += 1;
		arrowRightReleased = false;
	}

	if (activeShopState == 0)
	{
		speedUpgradeCount->setIsDestroy(false);
		healthUpgradeCount->setIsDestroy(false);
		totalCostPendingSlot1->setIsDestroy(false);
		totalCostPendingSlot2->setIsDestroy(false);
		upgradeGUI->getObj()->setMaterialName("StatsBase.png");
		if (inputDirectOther->isArrowDownPressed() && arrowDownReleased && getShopOverlayCounter() < 2)
		{
			setShopOverlayCounter(getShopOverlayCounter() + 1);
			arrowDownReleased = false;
		}
		if (inputDirectOther->isArrowUpPressed() && arrowUpReleased && getShopOverlayCounter() > -1)
		{
			setShopOverlayCounter(getShopOverlayCounter() - 1);
			arrowUpReleased = false;
		}
		if (inputDirectOther->isArrowLeftPressed() && arrowLeftReleased && getShopOverlayCounter() == 2 && getShopOverlayCounterRow() > 0)
		{
			setShopOverlayCounterRow(getShopOverlayCounterRow() - 1);
			arrowLeftReleased = false;
		}
		if (inputDirectOther->isArrowRightPressed() && arrowRightReleased && getShopOverlayCounter() == 2 && getShopOverlayCounterRow() < 1)
		{
			setShopOverlayCounterRow(getShopOverlayCounterRow() + 1);
			arrowRightReleased = false;
		}

		if (getShopOverlayCounter() == -1)
		{
			upgradeOverlay->getObj()->setMaterialName("TabArrows.png");
		}
		if (getShopOverlayCounter() == 0)
		{
			upgradeOverlay->getObj()->setMaterialName("StatsSelected1.png");
		}
		if (getShopOverlayCounter() == 1)
		{
			upgradeOverlay->getObj()->setMaterialName("StatsSelected2.png");
		}
		if (getShopOverlayCounter() == 2 && getShopOverlayCounterRow() == 0)
		{
			upgradeOverlay->getObj()->setMaterialName("ConfirmSelected.png");
		}
		if (getShopOverlayCounter() == 2 && getShopOverlayCounterRow() == 1)
		{
			upgradeOverlay->getObj()->setMaterialName("CancelSelected.png");
		}
	}
	if (activeShopState == 1)
	{
		speedUpgradeCount->setIsDestroy(true);
		healthUpgradeCount->setIsDestroy(true);
		totalCostPendingSlot1->setIsDestroy(true);
		totalCostPendingSlot2->setIsDestroy(true);
		upgradeGUI->getObj()->setMaterialName("WeaponsBase.png");
		if (inputDirectOther->isArrowDownPressed() && arrowDownReleased && upgradeOvlerlayCounterWeapons < 4)
		{
			upgradeOvlerlayCounterWeapons += 1;
			arrowDownReleased = false;
		}
		if (inputDirectOther->isArrowUpPressed() && arrowUpReleased && upgradeOvlerlayCounterWeapons > -1)
		{
			upgradeOvlerlayCounterWeapons -= 1;
			arrowUpReleased = false;
		}
		if (inputDirectOther->isArrowLeftPressed() && arrowLeftReleased && upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() > 0)
		{
			setShopOverlayCounterRow(getShopOverlayCounterRow() - 1);
			arrowLeftReleased = false;
		}
		if (inputDirectOther->isArrowRightPressed() && arrowRightReleased && upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() < 1)
		{
			setShopOverlayCounterRow(getShopOverlayCounterRow() + 1);
			arrowRightReleased = false;
		}

		if (upgradeOvlerlayCounterWeapons == -1)
		{
			upgradeOverlay->getObj()->setMaterialName("TabArrows.png");
		}
		if (upgradeOvlerlayCounterWeapons == 0)
		{
			if (player->getNrWeaponBought(0))
			{
				upgradeOverlay->getObj()->setMaterialName("Owned1.png");
			}
			if (!player->getNrWeaponBought(0))
			{
				upgradeOverlay->getObj()->setMaterialName("Selected1.png");
			}
		}
		if (upgradeOvlerlayCounterWeapons == 1)
		{
			if (player->getNrWeaponBought(1))
			{
				upgradeOverlay->getObj()->setMaterialName("Owned2.png");
			}
			if (!player->getNrWeaponBought(1))
			{
				upgradeOverlay->getObj()->setMaterialName("Selected2.png");
			}
		}
		if (upgradeOvlerlayCounterWeapons == 2)
		{
			if (player->getNrWeaponBought(2))
			{
				upgradeOverlay->getObj()->setMaterialName("Owned3.png");
			}
			if (!player->getNrWeaponBought(2))
			{
				upgradeOverlay->getObj()->setMaterialName("Selected3.png");
			}
		}
		if (upgradeOvlerlayCounterWeapons == 3)
		{
			if (player->getNrWeaponBought(3))
			{
				upgradeOverlay->getObj()->setMaterialName("Owned4.png");
			}
			if (!player->getNrWeaponBought(3))
			{
				upgradeOverlay->getObj()->setMaterialName("Selected4.png");
			}
		}
		if (upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() == 0)
		{
			upgradeOverlay->getObj()->setMaterialName("ConfirmSelected.png");
		}
		if (upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() == 1)
		{
			upgradeOverlay->getObj()->setMaterialName("CancelSelected.png");
		}
	}
	
	upgradeOverlay->getObj()->setWorldMatrix(shopOverlayMat);
}

bool gameClass::updateGUI(double dt, GUItestClass* obj)
{
	return obj->updateDestroyState(dt);
}

void gameClass::updateShop(double dt, GUItestClass* obj, GUItestClass* obj2)
{

	upgradeGUI->updateDestroy2(dt);
	upgradeOverlay->updateDestroy2(dt);
	slot1->updateDestroy2(dt);
	slot2->updateDestroy2(dt);
	slot1xp->updateDestroy2(dt);
	slot2xp->updateDestroy2(dt);
	speedUpgradeCount->updateDestroy2(dt);
	healthUpgradeCount->updateDestroy2(dt);
	totalCostPendingSlot1->updateDestroy2(dt);
	totalCostPendingSlot2->updateDestroy2(dt);

	if (!upgradeGUI->getIsDestry() && !upgradeGUI->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(upgradeGUI->getObj());
		upgradeGUI->setCheckIfObjHolder(true);
		costHPBeginning = healthCost;
		costSpeedBeginnning = SpeedCost;
		activeShopState = 0;
	}
	if (upgradeGUI->getIsDestry() && upgradeGUI->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(upgradeGUI->getObj());
		upgradeGUI->setCheckIfObjHolder(false);
	}
	if (!upgradeOverlay->getIsDestry() && !upgradeOverlay->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(upgradeOverlay->getObj());
		upgradeOverlay->setCheckIfObjHolder(true);
	}
	if (upgradeOverlay->getIsDestry() && upgradeOverlay->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(upgradeOverlay->getObj());
		upgradeOverlay->setCheckIfObjHolder(false);
	}
	
	if (!slot1->getIsDestry() && !slot1->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(slot1->getObj());
		slot1->setCheckIfObjHolder(true);
	}
	if (slot1->getIsDestry() && slot1->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(slot1->getObj());
		slot1->setCheckIfObjHolder(false);
	}
	if (!slot2->getIsDestry() && !slot2->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(slot2->getObj());
		slot2->setCheckIfObjHolder(true);
	}
	if (slot2->getIsDestry() && slot2->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(slot2->getObj());
		slot2->setCheckIfObjHolder(false);
	}

	if (!slot1xp->getIsDestry() && !slot1xp->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(slot1xp->getObj());
		slot1xp->setCheckIfObjHolder(true);
	}
	if (slot1xp->getIsDestry() && slot1xp->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(slot1xp->getObj());
		slot1xp->setCheckIfObjHolder(false);
	}
	if (!slot2xp->getIsDestry() && !slot2xp->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(slot2xp->getObj());
		slot2xp->setCheckIfObjHolder(true);
	}
	if (slot2xp->getIsDestry() && slot2xp->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(slot2xp->getObj());
		slot2xp->setCheckIfObjHolder(false);
	}

	if (!healthUpgradeCount->getIsDestry() && !healthUpgradeCount->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(healthUpgradeCount->getObj());
		healthUpgradeCount->setCheckIfObjHolder(true);
	}
	if (healthUpgradeCount->getIsDestry() && healthUpgradeCount->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(healthUpgradeCount->getObj());
		healthUpgradeCount->setCheckIfObjHolder(false);
	}
	if (!speedUpgradeCount->getIsDestry() && !speedUpgradeCount->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(speedUpgradeCount->getObj());
		speedUpgradeCount->setCheckIfObjHolder(true);
	}
	if (speedUpgradeCount->getIsDestry() && speedUpgradeCount->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(speedUpgradeCount->getObj());
		speedUpgradeCount->setCheckIfObjHolder(false);
	}

	if (!totalCostPendingSlot1->getIsDestry() && !totalCostPendingSlot1->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(totalCostPendingSlot1->getObj());
		totalCostPendingSlot1->setCheckIfObjHolder(true);
	}
	if (totalCostPendingSlot1->getIsDestry() && totalCostPendingSlot1->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(totalCostPendingSlot1->getObj());
		totalCostPendingSlot1->setCheckIfObjHolder(false);
	}
	if (!totalCostPendingSlot2->getIsDestry() && !totalCostPendingSlot2->getCheckIfObjHolder())
	{
		addObjectToObjHolderLimbo(totalCostPendingSlot2->getObj());
		totalCostPendingSlot2->setCheckIfObjHolder(true);
	}
	if (totalCostPendingSlot2->getIsDestry() && totalCostPendingSlot2->getCheckIfObjHolder())
	{
		removeObjFromObjHolderLimbo(totalCostPendingSlot2->getObj());
		totalCostPendingSlot2->setCheckIfObjHolder(false);
	}
	
	if (!upgradeGUI->getIsDestry())
	{
		if (activeShopState == 0)
		{
			//now you can upgrade your stuff
			if (shopOverlayCount == 0)
			{
				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isArrowRightPressed() && arrowRightReleased)
				{
					arrowRightReleased = false;
					if ((player->getNrPixelFramgent() - totalPendingCost) >= healthCost && nrHPtoBeUpgraded < 4 && player->getMaxHP() < 4)
					{
						totalPendingCost += healthCost;
						/*player->setNrPixelFragments(player->getNrPixelFramgent() - healthCost);*/
						nrHPtoBeUpgraded += 1;
						healthCost = healthCost * 2;
					}
				}

				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isArrowLeftPressed() && nrHPtoBeUpgraded > 0 && arrowLeftReleased)
				{
					arrowLeftReleased = false;
					healthCost = healthCost / 2;
					totalPendingCost -= healthCost;
					//player->setNrPixelFragments(player->getNrPixelFramgent() + healthCost);
					nrHPtoBeUpgraded -= 1;
				}

			}
			if (shopOverlayCount == 1)
			{
				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isArrowRightPressed() && arrowRightReleased)
				{
					arrowRightReleased = false;
					if ((player->getNrPixelFramgent() - totalPendingCost) >= SpeedCost)
					{
						totalPendingCost += SpeedCost;
						//player->setNrPixelFragments(player->getNrPixelFramgent() - SpeedCost);
						nrSpeedToBeUpgraded += 1;
						SpeedCost = SpeedCost * 2;
					}
				}

				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isArrowLeftPressed() && nrSpeedToBeUpgraded > 0 && arrowLeftReleased)
				{
					arrowLeftReleased = false;
					SpeedCost = SpeedCost / 2;
					totalPendingCost -= SpeedCost;
					//player->setNrPixelFragments(player->getNrPixelFramgent() + SpeedCost);
					nrSpeedToBeUpgraded -= 1;
				}
			}
			
		}
		if (activeShopState == 1)
		{
			if (upgradeOvlerlayCounterWeapons == 0)
			{
				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(0))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(0))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(0));
						player->setNrWeaponBought(0, true);
					}
				}
			}
			if (upgradeOvlerlayCounterWeapons == 1)
			{
				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(1))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(1))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(1));
						player->setNrWeaponBought(1, true);
					}
				}
			}
			if (upgradeOvlerlayCounterWeapons == 2)
			{
				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(2))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(2))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(2));
						player->setNrWeaponBought(2, true);
					}
				}
			}
			if (upgradeOvlerlayCounterWeapons == 3)
			{
				inputDirectOther->readKeyboard(dt);
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(3))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(3))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(3));
						player->setNrWeaponBought(3, true);
					}
				}
			}
		}


		//IF CONFIRMED IS PRESSED
		if (upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() == 0 || getShopOverlayCounter() == 2 && getShopOverlayCounterRow() == 0)
		{
			inputDirectOther->readKeyboard(dt);
			if (inputDirectOther->isEnterPressed() && enterReleased)
			{
				enterReleased = false;
				if (nrHPtoBeUpgraded > 0)
				{
						for (int i = 0; i < nrHPtoBeUpgraded; i++)
						{
							if (!heartHolder[player->getMaxHP() + i].getIsDestry() && !heartHolder[player->getMaxHP() + i].getCheckIfObjHolder())
							{
								addObjectToObjHolder(heartHolder[player->getMaxHP() + i].getObj());
								heartHolder[player->getMaxHP() + i].setCheckIfObjHolder(true);
								heartHolder[player->getMaxHP() + i].setIsBought(true);
								OutputDebugString(L"\nheart was created!\n");
							}
						}
					
				}
				if (nrHPtoBeUpgraded > 0)
				{
					player->setMaxHP(player->getMaxHP() + nrHPtoBeUpgraded);
					nrHPtoBeUpgraded = 0;
				}
				if (nrSpeedToBeUpgraded > 0)
				{
					for (int i = 0; i < nrSpeedToBeUpgraded; i++)
					{
						player->setSpeedVal(player->getSpeedVal() + 1.0f);
						OutputDebugString(L"\nSpeed was created!\n");
					}
					nrSpeedToBeUpgraded = 0;
				}
				
				player->setNrPixelFragments(player->getNrPixelFramgent() - totalPendingCost);

				activeShopState = 0;
				setShopOverlayCounter(-1);
				setShopOverlayCounterRow(0);
				upgradeOvlerlayCounterWeapons = -1;
				upgradeGUI->setIsDestroy(true);
				upgradeOverlay->setIsDestroy(true);
				slot1->setIsDestroy(true);
				slot2->setIsDestroy(true);
				slot1xp->setIsDestroy(true);
				slot2xp->setIsDestroy(true);
				speedUpgradeCount->setIsDestroy(true);
				healthUpgradeCount->setIsDestroy(true);
				totalCostPendingSlot1->setIsDestroy(true);
				totalCostPendingSlot2->setIsDestroy(true);
				activeShopState = -1;
				totalPendingCost = 0;
			}
		}
		//IF CANCEL IS PRESSED
		if (getShopOverlayCounter() == 2 && getShopOverlayCounterRow() == 1 || upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() == 1)
		{
			if (inputDirectOther->isEnterPressed() && enterReleased)
			{
				if (nrHPtoBeUpgraded > 0)
				{
					healthCost = costHPBeginning;
					nrHPtoBeUpgraded = 0;
				}
				if (nrSpeedToBeUpgraded > 0)
				{
					SpeedCost = costSpeedBeginnning;
					nrSpeedToBeUpgraded = 0;
				}
				enterReleased = false;
				activeShopState = 0;
				setShopOverlayCounter(-1);
				setShopOverlayCounterRow(0);
				upgradeOvlerlayCounterWeapons = -1;
				upgradeGUI->setIsDestroy(true);
				upgradeOverlay->setIsDestroy(true);
				slot1->setIsDestroy(true);
				slot2->setIsDestroy(true);
				slot1xp->setIsDestroy(true);
				slot2xp->setIsDestroy(true);
				speedUpgradeCount->setIsDestroy(true);
				healthUpgradeCount->setIsDestroy(true);
				totalCostPendingSlot1->setIsDestroy(true);
				totalCostPendingSlot2->setIsDestroy(true);
				activeShopState = -1;
				totalPendingCost = 0;
			}
		}
	}
	if (upgradeGUI->getIsDestry())
	{

		activeShopState = 0;
		setShopOverlayCounter(-1);
		setShopOverlayCounterRow(0);
		upgradeOvlerlayCounterWeapons = -1;
		totalPendingCost = 0;
		activeShopState = -1;
		if (nrHPtoBeUpgraded > 0)
		{
			healthCost = costHPBeginning;
			nrHPtoBeUpgraded = 0;
		}
		if (nrSpeedToBeUpgraded > 0)
		{
			SpeedCost = costSpeedBeginnning;
			nrSpeedToBeUpgraded = 0;
		}
		speedUpgradeCount->setIsDestroy(true);
		healthUpgradeCount->setIsDestroy(true);
		totalCostPendingSlot1->setIsDestroy(true);
		totalCostPendingSlot2->setIsDestroy(true);
	}
}

int gameClass::getShopOverlayCounter()
{
	return this->shopOverlayCount;
}

int gameClass::getShopOverlayCounterRow()
{
	return this->shopOverlayCountRow;
}

void gameClass::setShopOverlayCounterRow(int x)
{
	this->shopOverlayCountRow = x;
}

void gameClass::setShopOverlayCounter(int x)
{
	this->shopOverlayCount = x;
}

void gameClass::updatePlatform()
{
	platformMat = XMMatrixIdentity();
	platform->getObj()->setWorldMatrix(platformMat);
}

void gameClass::updatePickup(double dt)
{
	/*pickup->getObj()->updatePosition(pickupStartPosMoveMat);*/

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		XMMATRIX yOffset;
		pickupHolder[i].getTranslationMatStart(yOffset);
		pickupHolder[i].getObj()->setWorldMatrix(yOffset);
		pickupHolder[i].updateAnimation(dt);
	}
	if (!ringDisplay->getIsDestry() && !ringDisplay->getCheckIfObjHolder())

	{

		addObjectToObjHolder(ringDisplay->getObj());

		ringDisplay->setCheckIfObjHolder(true);

	}

	if (ringDisplay->getIsDestry() && ringDisplay->getCheckIfObjHolder())

	{

		removeObjFromObjHolder(ringDisplay->getObj());

		ringDisplay->setCheckIfObjHolder(false);

	}
}

void gameClass::updateProjectile(double dt)
{
	//Move projectile
	projectile->moveProjectile(dt);
	projectile->getTransX(projectileMoveMat);
	projectile->getObj()->setWorldMatrix(projectileMoveMat);

	//CD between fireballs
	projectile->setLifeTime(dt);
	if (projectile->getLifeTime() > 3.0f)
	{
		removeObjFromObjHolder(projectile->getObj());
		projectile->resetProjectile();
		player->setFireballCast(false);
	}

	//If collision with platforms -> remove projectile
	if (checkCollisionPlatformBot(platform, projectile->getObj(), projectileMoveMat) ||
		checkCollisionPlatformTop(platform, projectile->getObj(), projectileMoveMat) ||
		checkCollisionPlatformRight(platform, projectile->getObj(), projectileMoveMat) ||
		checkCollisionPlatformLeft(platform, projectile->getObj(), projectileMoveMat))
	{
		removeObjFromObjHolder(projectile->getObj());
		projectile->resetProjectile();
		player->setFireballCast(false);
	}
}

void gameClass::updateCollision(double dt)
{
	float enemyMove = enemy->getMove();

	lengthBetween1 = XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove));
	lengthBetween2 = XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)) - XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyTranslationMatrix));
	lengthBetweenEnemyStartAndEnemyCurrentPos1 = XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(enemy->getStartPos(), enemyTranslationMatrix));
	lengthBetweenEnemyStartAndEnemyCurrentPos2 = XMVectorGetX(XMVector3Transform(enemy->getStartPos(), enemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyTranslationMatrix));

	if (enemy->getIsActive() && player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponLeft(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponLeft(), playerMove), XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
	{
		if (enemy->hurtState())
		{
			//enemy->resetMove();
			//enemy->getTranslationMatStart(masterMovementEnemyMat);
			enemy->setEnemyHP(enemy->getEnemyHP() - 1);
			OutputDebugString(L"\nenemy lost hP!\n");
		}
		if (enemy->getEnemyHP() <= 0)
		{
			player->setNrPolysgons(player->getNrPolygons() + 1);
			removeObjFromObjHolder(enemy->getObj());
			enemy->setIsActive(false);
			for (int i = 0; i < 2; i++)
			{
				XMMATRIX offset = XMMatrixTranslation(i * 2, 1.2f, 0.1f);
				XMMATRIX scale = XMMatrixScaling(0.3f, 0.7f, 0.0f);
				pickupClass pickup2;
				pickup2.clone(*expFragment);
				nrOfVisiblePickups++;
				addPickupToPickupHolder(pickup2, nrOfVisiblePickups);
				pickup2.shutdown();
				pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
				pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * enemyTranslationMatrix * offset);
				pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
				pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
			}
			player->setIfInObjHolder(false);
		}
	}
	else if (enemy->getIsActive() && !player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponRight(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponRight(), playerMove), XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
	{
		if (enemy->hurtState())
		{
			//enemy->resetMove();
			//enemy->getTranslationMatStart(masterMovementEnemyMat);
			enemy->setEnemyHP(enemy->getEnemyHP() - 1);
			OutputDebugString(L"\nenemy lost hP!\n");
		}
		if (enemy->getEnemyHP() <= 0)
		{
			player->setNrPolysgons(player->getNrPolygons() + 1);
			removeObjFromObjHolder(enemy->getObj());
			enemy->setIsActive(false);
			for (int i = 0; i < 2; i++)
			{
				XMMATRIX offset = XMMatrixTranslation(i * 2, 1.2f, 0.1f);
				XMMATRIX scale = XMMatrixScaling(0.3f, 0.7f, 0.0f);
				pickupClass pickup2;
				pickup2.clone(*expFragment);
				nrOfVisiblePickups++;
				addPickupToPickupHolder(pickup2, nrOfVisiblePickups);
				pickup2.shutdown();
				pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
				pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * enemyTranslationMatrix * offset);
				pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
				pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
			}
			player->setIfInObjHolder(false);
		}
	}

	if (enemy->getIsActive() && player->getFireballCast() && !projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinLeft(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxLeft(), projectileMoveMat), XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
	{
		if (enemy->hurtState())
		{
			//enemy->resetMove();
			//enemy->getTranslationMatStart(masterMovementEnemyMat);
			enemy->setEnemyHP(enemy->getEnemyHP() - 1);
			OutputDebugString(L"\nenemy lost hP by Fireball!\n");
		}
		if (enemy->getEnemyHP() <= 0)
		{
			player->setNrPolysgons(player->getNrPolygons() + 1);
			removeObjFromObjHolder(enemy->getObj());
			enemy->setIsActive(false);
			for (int i = 0; i < 2; i++)
			{
				XMMATRIX offset = XMMatrixTranslation(i * 2, 1.2f, 0.1f);
				XMMATRIX scale = XMMatrixScaling(0.3f, 0.7f, 0.0f);
				pickupClass pickup2;
				pickup2.clone(*expFragment);
				nrOfVisiblePickups++;
				addPickupToPickupHolder(pickup2, nrOfVisiblePickups);
				pickup2.shutdown();
				pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
				pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * enemyTranslationMatrix * offset);
				pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
				pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
			}
			player->setIfInObjHolder(false);
		}
		removeObjFromObjHolder(projectile->getObj());
		projectile->resetProjectile();
		player->setFireballCast(false);
	}

	else if (enemy->getIsActive() && player->getFireballCast() && projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinRight(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxRight(), projectileMoveMat), XMVector3Transform(enemy->getObj()->getBoundingBoxMin(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemy->getObj()->getBoundingBoxMax(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
	{
		if (enemy->hurtState())
		{
			//enemy->resetMove();
			//enemy->getTranslationMatStart(masterMovementEnemyMat);
			enemy->setEnemyHP(enemy->getEnemyHP() - 1);
			OutputDebugString(L"\nenemy lost hP by Fireball!\n");
		}
		if (enemy->getEnemyHP() <= 0)
		{
			player->setNrPolysgons(player->getNrPolygons() + 1);
			removeObjFromObjHolder(enemy->getObj());
			enemy->setIsActive(false);
			for (int i = 0; i < 2; i++)
			{
				XMMATRIX offset = XMMatrixTranslation(i * 2, 1.2f, 0.1f);
				XMMATRIX scale = XMMatrixScaling(0.3f, 0.7f, 0.0f);
				pickupClass pickup2;
				pickup2.clone(*expFragment);
				nrOfVisiblePickups++;
				addPickupToPickupHolder(pickup2, nrOfVisiblePickups);
				pickup2.shutdown();
				pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
				pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * enemyTranslationMatrix * offset);
				pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
				pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
			}
			player->setIfInObjHolder(false);
		}
		removeObjFromObjHolder(projectile->getObj());
		projectile->resetProjectile();
		player->setFireballCast(false);
	}

	enemy->timeCountdown(dt);

	if (enemy->getIsActive() && lengthBetween1 <= XMVectorGetX(enemy->getTriggerCheck()) && lengthBetween1 >= 1.5f)
	{
		if (lengthBetween1 <= XMVectorGetX(enemy->getRangeVector()))
		{
			enemy->setMove(0.0f);
			if (enemy->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(enemy->getBboxMinWeaponLeft(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemy->getBboxMaxWeaponLeft(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) && !player->getInvulnurable())
			{
				if (enemy->attackCooldown())
				{
					OutputDebugString(L"Attacking");

					player->setPlayerHP(player->getPlayerHP() - 1);
					player->setPlayerHurt(true);
					player->setPlayerHurtFromLeft(true);
					if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())

					{

						heartHolder[player->getPlayerHP()].setIsDestroy(true);

						removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());

						heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);

					}
				}
			}
		}
		else
		{
			//går åt vänster
			if (enemy->getFacing() && countEnemy <= 0)
			{
				enemy->setRoationCheck(true);
				countEnemy = 100;
				enemy->setMove(0.0f);
			}
			else if (enemy->getFacing() && countEnemy >= 0)
			{
				countEnemy -= 1;
			}
			else
			{
				enemy->setRoationCheck(false);
				enemy->setFacing(false);
				enemy->updateAttackCooldownTimer(dt);
			}

			enemy->setMove(2.5f * dt);
			enemy->setTranslation(enemy->getMove());
		}
	}
	else if (enemy->getIsActive() && XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))) < XMVectorGetX(enemy->getStartPos()))
	{
		enemy->setMove(-1.5f * dt);
		enemy->setTranslation(enemy->getMove());
		//OutputDebugString(L"MOVING TO SPAWN");
	}


	if (enemy->getIsActive() && lengthBetween2 <= XMVectorGetX(enemy->getTriggerCheck()) && lengthBetween1 <= 1.5f)
	{
		//år höger
		if (lengthBetween2 <= XMVectorGetX(enemy->getRangeVector()) - 3)
		{
			enemy->setMove(0.0f);
			if (enemy->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(enemy->getBboxMinWeaponRight(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemy->getBboxMaxWeaponRight(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) && !player->getInvulnurable())
			{
				if (enemy->attackCooldown())
				{

					player->setPlayerHP(player->getPlayerHP() - 1);

					player->setPlayerHurt(true);
					player->setPlayerHurtFromRight(true);
					if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())

					{

						heartHolder[player->getPlayerHP()].setIsDestroy(true);

						removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());

						heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);

					}
				}
			}
		}
		else
		{
			if (!enemy->getFacing() && countEnemy <= 0)
			{
				enemy->setRoationCheck(true);
				countEnemy = 100;
				enemy->setMove(0.0f);
			}
			else if (!enemy->getFacing() && countEnemy >= 0)
			{
				countEnemy -= 1;
			}
			else
			{
				enemy->setRoationCheck(false);
				enemy->setFacing(true);
				enemy->updateAttackCooldownTimer(dt);
			}
			enemy->setTranslation(enemy->getMove());
			enemy->setMove(-2.5f * dt);
		}
	}
	else if (enemy->getIsActive() && XMVectorGetX(XMVector3Transform(enemy->getObj()->getPosition(), enemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))) > XMVectorGetX(enemy->getStartPos()))
	{
		enemy->setMove(1.5f * dt);
		enemy->setTranslation(enemy->getMove());
	}

	enemy->updateAttackCooldownTimer(dt);

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		//derp
		XMMATRIX yOffset;
		pickupHolder[i].getTranslationMatStart(yOffset);
		if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(pickupHolder[i].getObj()->getBoundingBoxMin(), yOffset), XMVector3Transform(pickupHolder[i].getObj()->getBoundingBoxMax(), yOffset)))
		{

			if (pickupHolder[i].getPickupType() == 1)
			{
				tempXP += 1;
				if (tempXP == 4)
				{
					player->setNrPixelFragments(this->player->getNrPixelFramgent() + 5);
					tempXP = 0;
				}
				pickupHolder[i].setIsDestroy(true);
			}

			if (pickupHolder[i].getPickupType() == 3 && inputDirectOther->isEnterPressed() && enterReleased) //type 3 means it's a RING
			{
				if (player->getHasRing())
				{
					pickupClass tRing;
					tRing.clone(*ring);
					nrOfVisiblePickups++;
					addPickupToPickupHolder(tRing, nrOfVisiblePickups);
					pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(3);
					pickupHolder[nrOfVisiblePickups - 1].setRingType(player->getRingType());
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(yOffset);
					tRing.shutdown();
					player->setIfInObjHolder(false);
				}
				this->player->setHasRing(true);
				this->player->setRingType(pickupHolder[i].getRingType());
				if (ringDisplay->getIsDestry() && !ringDisplay->getCheckIfObjHolder())
				{
					//OutputDebugString(L"\ENTRED IN THIS1!\n");
					addObjectToObjHolder(ringDisplay->getObj());
					ringDisplay->setIsDestroy(false);
					ringDisplay->setCheckIfObjHolder(true);
				}
				ringDisplay->setIsDestroy(false);
				if (!ringDisplay->getIsDestry() && ringDisplay->getCheckIfObjHolder())
				{
					//OutputDebugString(L"\ENTRED IN THIS2!\n");
					if (pickupHolder[i].getRingType() == 0)
					{
						ringDisplay->getObj()->setMaterialName("sampleRing.png");
					}
					if (pickupHolder[i].getRingType() == 1)
					{
						ringDisplay->getObj()->setMaterialName("sampleRing2.png");
					}
				}
				pickupHolder[i].setIsDestroy(true);
				enterReleased = false;
			}
		}
	}
}

bool gameClass::checkCollisionPlatformTop(platformClass* platform, objectClass *obj, XMMATRIX objWorld)
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
bool gameClass::checkCollisionPlatformLeft(platformClass* platform, objectClass *obj, XMMATRIX objWorld)
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
bool gameClass::checkCollisionPlatformRight(platformClass* platform, objectClass *obj, XMMATRIX objWorld)
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
bool gameClass::checkCollisionPlatformBot(platformClass* platform, objectClass *obj, XMMATRIX objWorld)
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