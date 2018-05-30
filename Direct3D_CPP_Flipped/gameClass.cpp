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
	menyHighlightMat = XMMatrixScaling(0.01f, 0.02f, 0.0f) * XMMatrixTranslation(-0.147f, 0.045f, 0.0f);
	counterOverlay = 0;
	menyCheck = true;
	shopOverlayCount = -1;
	shopOverlayCountRow = 0;
	nrSpeedToBeUpgraded = 0;
	activeShopState = 0;
	ShopTabsCounter = 0;
	upgradeOvlerlayCounterWeapons = -1;
	tempXP = 0;
	fireBoss2Mat = XMMatrixIdentity();
	nrOfEnemysBossHasSpawned = 0;
	bossTimerForRainingFire = 0;

	bossTimer = 0;

	costHPBeginning = 0;
	costSpeedBeginnning = 0;

	shopMat = XMMatrixScaling(0.85f, 0.85f, 0.85f) * XMMatrixTranslation(9.5f, 0.55f, 0.0f);
	shopOverlayMat = XMMatrixTranslation(0.0f, 0.0f, -0.01f) * shopMat;

	sound = 0;
	firstFrame = true;
	soundAvailable = true;

	countEnemy = 0;
	SpeedCost = 1;

	spawnEnemys = 0;

	player = 0;
	camera = 0;
	platform = 0;
	expFragment = 0;
	ring = 0;
	background = 0;
	floor = 0;
	walls = 0;
	pillars = 0;
	foregroundWalls = 0;
	movementInput = 0;
	projectile = 0;
	enemyFire = 0;
	shieldBubble = 0;
	moveTest = 2.0f;
	tempEnemyIfAirThenFallMatrix = XMMatrixIdentity();
	tempBossIfAirThenFallMatrix = XMMatrixIdentity();
	tempEnemyTranslationMatrix = XMMatrixIdentity();
	tempBossTranslationMatrix = XMMatrixIdentity();


	tempBossStartingPositionMatrix = XMMatrixIdentity();
	tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame = XMMatrixIdentity();
	tempMasterMovementBossMat = XMMatrixIdentity();
	

	heartHolder = 0;
	pickupHolder = 0;
	enemyHolder = 0;
	portalPlane = 0;

	nrOfVisiblePickups = 0;
	nrOfVisibleEnemies = 0;

	projectileMoveMat = XMMatrixIdentity();

	canPLayCDDisplay = false;

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
	polygonDispMat = XMMatrixScaling(0.026f, 0.05f, 0.0f) * XMMatrixTranslation(0.70f, 0.82f, 0.0f);
	ringDisplay = 0;
	ringDisplayMat = XMMatrixScaling(0.04f, 0.07f, 0.0f) * XMMatrixTranslation(-0.85f, 0.57f, 0.0f);
	xpDisplay = 0;
	xpDisplayMat = XMMatrixScaling(0.21f, 0.04f, 0.0f) * XMMatrixTranslation(0.005f, 0.82f, 0.0f);
	slot1xp = 0;
	slot1xpMat = XMMatrixScaling(0.015f, 0.03f, 0.0f) * XMMatrixTranslation(0.29f, 0.82f, 0.0f);
	slot2xpMat = XMMatrixScaling(0.015f, 0.03f, 0.0f) * XMMatrixTranslation(0.25f, 0.82f, 0.0f);

	slot1xpMatLimbo = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.80f, 0.748f, 0.0f);
	slot2xpMatLimbo = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.777f, 0.748f, 0.0f);
	slot1MatLimbo = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.44f, 0.748f, 0.0f);
	slot2MatLimbo = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.418f, 0.748f, 0.0f);

	healthUpgradeCountMat = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.62f, 0.505f, 0.0f);
	speedUpgradeCountMat = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.62f, 0.329f, 0.0f);

	totalCostPendingSlot2 = 0;
	totalCostPendingSlot1 = 0;
	totalCostPendingSlot2Mat = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.636f, -0.41f, 0.0f);
	totalCostPendingSlot1Mat = XMMatrixScaling(0.009f, 0.017f, 0.0f) * XMMatrixTranslation(0.66f, -0.41f, 0.0f);

	isUpgradeHPAactive = true;
	nrHPtoBeUpgraded = 0;
	healthCost = 1;
	upgradeCooldown = false;
	upgradeTimer = 0;

	enterReleased = true;
	arrowUpReleased = true;
	arrowUpReleased = true;
	arrowRightReleased = true;
	WRealeased = true;
	arrowLeftReleased = true;

	ringsInitialized = false;

	totalPendingCost = 0;

	isTextInPickupHolder2 = false;
	isTextInPickupHolder = false;
	isTextDestroy = true;
	isTextDestroy2 = true;

	portalMat = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	bossdoor = 0;
	bossIce = 0;
	bossFire = 0;

	//////BOSS
	bossDoorInObjHolder = false;
	bossDoorDestoryed = true;
	bossIsInCombat = false;
	ifBossIsSpawning = false;
	bossBattleEntered = false;


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
	camera->setPosition(0.0f, 0.0f, -150.0f, 0.0f);

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

	player->getObj()->setMaterialName("playerSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), player->getObj()->getMaterialName());
	player->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), player->getObj()->getNormalMapName());

	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "ShovelSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "GoldShovelSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "SwordSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "BloodShovelSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "DarkShovelSpriteSheet.png");

	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "StrawhatSpriteSheet.png");

	XMVECTOR tempBboxMax;
	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(player->getObj()->getBoundingBoxMax()) };
	player->getWeapon()->setBboxMaxWeaponRight(tempBboxMax);
	player->getWeapon()->setBboxMinWeaponRight(player->getObj()->getBoundingBoxMax());

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(player->getObj()->getBoundingBoxMin()) };
	player->getWeapon()->setBboxMaxWeaponLeft(player->getObj()->getBoundingBoxMin());
	player->getWeapon()->setBboxMinWeaponLeft(tempBboxMax);
	player->setPlayAnimation(false);
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

	playerShadowPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), playerShadowPlane->getObj()->getNormalMapName());
	//addObjectToObjHolder(playerShadowPlane->getObj());

	//enemy
	enemy = new enemyClass;
	if (!enemy)
	{
		MessageBox(NULL, L"Error create enemy1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = enemy->initlialize(graphics->getD3D()->GetDevice(), "skeletonAnimated.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//COPY A MATRIX IN ENEMY THAT HOLD THE SPAWN POINT
	enemy->getTranslationMatStart(tempEnemyStartingPositionMatrix);
	enemy->setTranslation(0.0f);
	enemy->getObj()->setMaterialName("skeletonTexture.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), enemy->getObj()->getMaterialName());

	enemy->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), enemy->getObj()->getNormalMapName());

	tempBboxMax = { XMVectorGetX(enemy->getObj()->getBoundingBoxMax()) + 1, XMVectorGetY(enemy->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(enemy->getObj()->getBoundingBoxMax()), XMVectorGetY(enemy->getObj()->getBoundingBoxMin()) };
	enemy->setBboxMaxWeaponRight(tempBboxMax);
	enemy->setBboxMinWeaponRight(tempBboxMin);

	tempBboxMax = { XMVectorGetX(enemy->getObj()->getBoundingBoxMin()), XMVectorGetY(enemy->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(enemy->getObj()->getBoundingBoxMin()) - 1, XMVectorGetY(enemy->getObj()->getBoundingBoxMin()) };
	enemy->setBboxMaxWeaponLeft(tempBboxMax);
	enemy->setBboxMinWeaponLeft(tempBboxMin);

	//enemy range
	enemy2 = new enemyClass;
	if (!enemy2)
	{
		MessageBox(NULL, L"Error create enemy2 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = enemy2->initlialize(graphics->getD3D()->GetDevice(), "rangedEnemy.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy2 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//COPY A MATRIX IN ENEMY THAT HOLD THE SPAWN POINT
	enemy2->getTranslationMatStart(tempEnemyStartingPositionMatrix);
	enemy2->setTranslation(0.0f);
	enemy2->getObj()->setMaterialName("RangedTest2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), enemy2->getObj()->getMaterialName());

	enemy2->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), enemy2->getObj()->getNormalMapName());

	tempBboxMax = { XMVectorGetX(enemy2->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(enemy2->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(enemy2->getObj()->getBoundingBoxMax()), XMVectorGetY(enemy2->getObj()->getBoundingBoxMin()) };
	enemy2->setBboxMaxWeaponRight(tempBboxMax);
	enemy2->setBboxMinWeaponRight(tempBboxMin);

	tempBboxMax = { XMVectorGetX(enemy2->getObj()->getBoundingBoxMin()), XMVectorGetY(enemy2->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(enemy2->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(enemy2->getObj()->getBoundingBoxMin()) };
	enemy2->setBboxMaxWeaponLeft(tempBboxMax);
	enemy2->setBboxMinWeaponLeft(tempBboxMin);

	//spawnEnemys test
	spawnBoss = new backgroundClass;
	if (!spawnBoss)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = spawnBoss->initlialize(graphics->getD3D()->GetDevice(), "bossSpawn.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	spawnBoss->getObj()->setMaterialName("pixelFragmentSprite.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), spawnBoss->getObj()->getMaterialName());

	spawnBoss->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), spawnBoss->getObj()->getNormalMapName());

	//enemy range
	boss = new enemyClass;
	if (!boss)
	{
		MessageBox(NULL, L"Error create enemy3 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = boss->initlialize(graphics->getD3D()->GetDevice(), "boss.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy3 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//COPY A MATRIX IN ENEMY THAT HOLD THE SPAWN POINT

	boss->setStartMat(XMVectorGetX(spawnBoss->getObj()->getPosition()), XMVectorGetY(spawnBoss->getObj()->getPosition()));
	boss->setStartPos(XMVectorGetX(spawnBoss->getObj()->getPosition()), XMVectorGetY(spawnBoss->getObj()->getPosition()), XMVectorGetZ(spawnBoss->getObj()->getPosition()));

	boss->getObj()->setMaterialName("BossTest1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), boss->getObj()->getMaterialName());
	boss->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), boss->getObj()->getNormalMapName());

	tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame = XMMatrixIdentity();
	tempMasterMovementBossMat = XMMatrixIdentity();
	boss->getObj()->setType(3);

	tempBboxMax = { XMVectorGetX(boss->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(boss->getObj()->getBoundingBoxMax())};
	tempBboxMin = { XMVectorGetX(boss->getObj()->getBoundingBoxMax()), XMVectorGetY(boss->getObj()->getBoundingBoxMin())};
	boss->setBboxMaxWeaponRight(tempBboxMax);
	boss->setBboxMinWeaponRight(tempBboxMin);

	tempBboxMax = { XMVectorGetX(boss->getObj()->getBoundingBoxMin()), XMVectorGetY(boss->getObj()->getBoundingBoxMax()) };
	tempBboxMin = { XMVectorGetX(boss->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(boss->getObj()->getBoundingBoxMin()) };
	boss->setBboxMaxWeaponLeft(tempBboxMax);
	boss->setBboxMinWeaponLeft(tempBboxMin);

	addObjectToObjHolder(boss->getObj());
	boss->setCheckIfObjHolder(true);
	boss->setIsActive(true);
	boss->setEnemyHP(100);

	//background test
	background = new backgroundClass;
	if (!background)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = background->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	background->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), background->getObj()->getMaterialName());

	background->getObj()->setNormalMapName("WallTexture_NORMAL.png");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), background->getObj()->getNormalMapName());

	//////////////////BACKGROUND
	////////////////////////////

	//background test
	spiderweeb = new backgroundClass;
	result = spiderweeb->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	spiderweeb->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), spiderweeb->getObj()->getMaterialName());
	spiderweeb->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), spiderweeb->getObj()->getNormalMapName());

	barrel = new backgroundClass;
	result = barrel->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	barrel->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), barrel->getObj()->getMaterialName());
	barrel->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), barrel->getObj()->getNormalMapName());

	candle = new backgroundClass;
	result = candle->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	candle->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), candle->getObj()->getMaterialName());
	candle->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), candle->getObj()->getNormalMapName());

	plank = new backgroundClass;
	result = plank->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	plank->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), plank->getObj()->getMaterialName());
	plank->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), plank->getObj()->getNormalMapName());

	painting1 = new backgroundClass;
	result = painting1->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	painting1->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), painting1->getObj()->getMaterialName());
	painting1->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), painting1->getObj()->getNormalMapName());

	painting2 = new backgroundClass;
	result = painting2->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	painting2->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), painting2->getObj()->getMaterialName());
	painting2->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), painting2->getObj()->getNormalMapName());

	ironmaiden = new backgroundClass;
	result = ironmaiden->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	ironmaiden->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), ironmaiden->getObj()->getMaterialName());
	ironmaiden->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), ironmaiden->getObj()->getNormalMapName());

	sewer = new backgroundClass;
	result = sewer->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	sewer->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), sewer->getObj()->getMaterialName());
	sewer->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), sewer->getObj()->getNormalMapName());

	bannerCarpet = new backgroundClass;
	result = bannerCarpet->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	bannerCarpet->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bannerCarpet->getObj()->getMaterialName());
	bannerCarpet->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bannerCarpet->getObj()->getNormalMapName());

	crate = new backgroundClass;
	result = crate->initlialize(graphics->getD3D()->GetDevice(), "2dummyBackground.bin");
	crate->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), crate->getObj()->getMaterialName());
	crate->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), crate->getObj()->getNormalMapName());



	////////////////////////////
	////////////////////////////


	floor = new backgroundClass;
	result = floor->initlialize(graphics->getD3D()->GetDevice(), "BackgroundFloors.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init floor obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	floor->getObj()->setMaterialName("Floor_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), floor->getObj()->getMaterialName());

	floor->getObj()->setNormalMapName("Floor_NORMAL.png");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), floor->getObj()->getNormalMapName());

	walls = new backgroundClass;
	result = walls->initlialize(graphics->getD3D()->GetDevice(), "BackgroundWalls.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init wall obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	walls->getObj()->setMaterialName("WallTexture_DIFFUSE.png");

	walls->getObj()->setNormalMapName("WallTexture_NORMAL.png");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), walls->getObj()->getNormalMapName());

	pillars = new backgroundClass;
	result = pillars->initlialize(graphics->getD3D()->GetDevice(), "DungeonPillars.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pillar obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	pillars->getObj()->setMaterialName("Pillar_Moss_BaseColor.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), pillars->getObj()->getMaterialName());

	pillars->getObj()->setNormalMapName("Pillar_Normal.png");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), pillars->getObj()->getNormalMapName());

	foregroundWalls = new backgroundClass;
	result = foregroundWalls->initlialize(graphics->getD3D()->GetDevice(), "ForegroundWalls.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init foreground walls obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	foregroundWalls->getObj()->setMaterialName("Floor_DIFFUSE.png");

	foregroundWalls->getObj()->setNormalMapName("Floor_NORMAL.png");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), foregroundWalls->getObj()->getNormalMapName());
	//spawnEnemys

	//background test
	ladders = new backgroundClass;
	if (!ladders)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = ladders->initlialize(graphics->getD3D()->GetDevice(), "2Ladders.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ladders->getObj()->setMaterialName("ladder_PNG14808.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), ladders->getObj()->getMaterialName());

	ladders->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), ladders->getObj()->getNormalMapName());

	//spawnEnemys test
	spawnEnemys = new backgroundClass;
	if (!spawnEnemys)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = spawnEnemys->initlialize(graphics->getD3D()->GetDevice(), "enemySpawns2.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	spawnEnemys->getObj()->setMaterialName("pixelFragmentSprite.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), spawnEnemys->getObj()->getMaterialName());

	spawnEnemys->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), spawnEnemys->getObj()->getNormalMapName());


	//pickupSpawn test
	pickupSpawn = new backgroundClass;
	if (!pickupSpawn)
	{
		MessageBox(NULL, L"Error create background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = pickupSpawn->initlialize(graphics->getD3D()->GetDevice(), "pickupSpawn.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	pickupSpawn->getObj()->setMaterialName("pixelFragmentSprite.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), pickupSpawn->getObj()->getMaterialName());

	pickupSpawn->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), pickupSpawn->getObj()->getNormalMapName());

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

	expFragment->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), expFragment->getObj()->getNormalMapName());

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
	ring->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), ring->getObj()->getNormalMapName());

	//shieldBubble
	shieldBubble = new pickupClass;
	if (!shieldBubble)
	{
		MessageBox(NULL, L"Error create shieldBubble obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = shieldBubble->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init shieldBubble obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	shieldBubble->getObj()->setMaterialName("ShieldSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "ShieldSpriteSheet.png");
	shieldBubble->setFrameCount(6);
	shieldBubble->getObj()->setFrameCount(6);
	shieldBubble->setAnimationCount(1);
	shieldBubble->getObj()->setAnimationCount(1);
	shieldBubble->setPickupType(6);

	shieldBubble->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), shieldBubble->getObj()->getNormalMapName());

	///////////////////////////
	coldownDisplay = new pickupClass;
	if (!coldownDisplay)
	{
		MessageBox(NULL, L"Error create pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = coldownDisplay->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	coldownDisplay->getObj()->setMaterialName("MagicFireFadeSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "MagicBlueFadeSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "MagicFireFadeSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "ShieldFadeSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "Transparent.png");
	coldownDisplay->setIsDestroy(false);
	coldownDisplay->setCheckIfObjHolder(false);
	coldownDisplay->setFrameCount(5);
	coldownDisplay->getObj()->setFrameCount(5);
	coldownDisplay->setTranslationMatStart(XMMatrixScaling(0.4, 0.9, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) + 1.0f, 0.0f));

	coldownDisplay->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), coldownDisplay->getObj()->getNormalMapName());

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
	projectile->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingGreenSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "MagicBlueSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "CancelSelectedWeapons.png");
	
	projectile->getTranslationMatStart(playerMove);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(player->getObj()->getBoundingBoxMax()) };
	projectile->setBoundingBoxMaxRight(tempBboxMax * 0.3f);
	projectile->setBoundingBoxMinRight(player->getObj()->getBoundingBoxMax() * 0.3f);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(player->getObj()->getBoundingBoxMin()) };
	projectile->setBoundingBoxMaxLeft(player->getObj()->getBoundingBoxMin() * 0.3f);
	projectile->setBoundingBoxMinLeft(tempBboxMax * 0.3f);
	projectile->setFrameCount(4);
	projectile->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), projectile->getObj()->getNormalMapName());

	//projectile test
	enemyFire = new projectileClass;
	if (!enemyFire)
	{
		MessageBox(NULL, L"Error create enemyFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = enemyFire->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init enemyFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	enemyFire->getObj()->setMaterialName("FIREBALL.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), enemyFire->getObj()->getMaterialName());
	enemyFire->setIsDestroyed(false);
	enemyFire->setCheckIfObjHolder(false);
	enemyFire->getTranslationMatStart(tempEnemyTranslationMatrix);
	enemyFire->setFrameCount(2);
	enemyFire->setProjectileType(1);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(player->getObj()->getBoundingBoxMax()) };
	enemyFire->setBoundingBoxMaxRight(tempBboxMax * 0.3f);
	enemyFire->setBoundingBoxMinRight(player->getObj()->getBoundingBoxMax() * 0.3f);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(player->getObj()->getBoundingBoxMin()) };
	enemyFire->setBoundingBoxMaxLeft(player->getObj()->getBoundingBoxMin() * 0.3f);
	enemyFire->setBoundingBoxMinLeft(tempBboxMax * 0.3f);

	enemyFire->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), enemyFire->getObj()->getNormalMapName());

	//projectile test
	bossFire = new projectileClass;
	if (!bossFire)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossFire->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossFire->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossFire->getObj()->getMaterialName());
	bossFire->setProjectileType(1);
	bossFire->setIsDestroyed(false);
	bossFire->setCheckIfObjHolder(false);
	bossFire->getTranslationMatStart(tempBossTranslationMatrix);
	bossFire->setFrameCount(4);

	tempBboxMax = { XMVectorGetX(boss->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(boss->getObj()->getBoundingBoxMax()) };
	bossFire->setBoundingBoxMaxRight(tempBboxMax * 0.3f);
	bossFire->setBoundingBoxMinRight(boss->getObj()->getBoundingBoxMax() * 0.3f);

	tempBboxMax = { XMVectorGetX(boss->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(boss->getObj()->getBoundingBoxMin()) };
	bossFire->setBoundingBoxMaxLeft(boss->getObj()->getBoundingBoxMin() * 0.3f);
	bossFire->setBoundingBoxMinLeft(tempBboxMax * 0.3f);
	bossFire->setFrameCount(4);

	bossFire->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossFire->getObj()->getNormalMapName());
	///////////////////////////////////////////
	//projectile test
	bossFire2 = new projectileClass;
	if (!bossFire2)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossFire2->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossFire2->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossFire2->getObj()->getMaterialName());
	bossFire2->setProjectileType(2);
	bossFire2->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-50.0f, 102.0f, 0.0f));
	bossFire2->setFrameCount(4);

	bossFire2->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossFire2->getObj()->getNormalMapName());
	bossFire3 = new projectileClass;
	if (!bossFire3)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossFire3->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossFire3->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossFire3->getObj()->getMaterialName());
	bossFire3->setProjectileType(2);
	bossFire3->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-40.0f, 102.0f, 0.0f));
	bossFire3->setFrameCount(4);

	bossFire3->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossFire3->getObj()->getNormalMapName());

	bossFire4 = new projectileClass;
	if (!bossFire4)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossFire4->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossFire4->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossFire4->getObj()->getMaterialName());
	bossFire4->setProjectileType(2);
	bossFire4->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-30.0f, 102.0f, 0.0f));
	bossFire4->setFrameCount(4);

	bossFire4->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossFire4->getObj()->getNormalMapName());

	bossFire5= new projectileClass;
	if (!bossFire5)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossFire5->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossFire5->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossFire5->getObj()->getMaterialName());
	bossFire5->setProjectileType(2);
	bossFire5->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-20.0f, 102.0f, 0.0f));
	bossFire5->setFrameCount(4);

	bossFire5->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossFire5->getObj()->getNormalMapName());

	bossFire6 = new projectileClass;
	if (!bossFire6)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossFire6->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossFire6->getObj()->setMaterialName("MagicRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossFire6->getObj()->getMaterialName());
	bossFire6->setProjectileType(2);
	bossFire6->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-10.0f, 102.0f, 0.0f));
	bossFire6->setFrameCount(4);

	bossFire6->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossFire6->getObj()->getNormalMapName());

	/////////////////////////////////////////////

	//projectile test
	bossIce = new projectileClass;
	if (!bossIce)
	{
		MessageBox(NULL, L"Error create bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossIce->initlialize(graphics->getD3D()->GetDevice(), "playerPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init bossFire obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossIce->getObj()->setMaterialName("MagicBlueSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossIce->getObj()->getMaterialName());
	bossIce->getObj()->setType(5);
	bossIce->setProjectileType(1);
	bossIce->setIsDestroyed(false);
	bossIce->setCheckIfObjHolder(false);
	bossIce->getTranslationMatStart(tempEnemyTranslationMatrix);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMax()) + 6, XMVectorGetY(player->getObj()->getBoundingBoxMax()) };
	bossIce->setBoundingBoxMaxRight(tempBboxMax * 0.3f);
	bossIce->setBoundingBoxMinRight(player->getObj()->getBoundingBoxMax() * 0.3f);

	tempBboxMax = { XMVectorGetX(player->getObj()->getBoundingBoxMin()) - 6, XMVectorGetY(player->getObj()->getBoundingBoxMin()) };
	bossIce->setBoundingBoxMaxLeft(player->getObj()->getBoundingBoxMin() * 0.3f);
	bossIce->setBoundingBoxMinLeft(tempBboxMax * 0.3f);

	bossIce->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossIce->getObj()->getNormalMapName());
	//GUI
	GUIheart1 = new GUItestClass;
	if (!GUIheart1)
	{
		MessageBox(NULL, L"Error create Heart1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = GUIheart1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init Heart1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	GUIheart1->getObj()->setWorldMatrix(heart1);
	GUIheart1->getObj()->setMaterialName("HP2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), GUIheart1->getObj()->getMaterialName());

	GUIheart1->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), GUIheart1->getObj()->getNormalMapName());
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

	bossdoor = new platformClass;
	if (!bossdoor)
	{
		MessageBox(NULL, L"Error create boos door",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = bossdoor->initlialize(graphics->getD3D()->GetDevice(), "bossdoor.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	bossdoor->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), bossdoor->getObj()->getMaterialName());
	bossdoor->getObj()->setWorldMatrix(XMMatrixIdentity());
	bossdoor->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), bossdoor->getObj()->getNormalMapName());
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
	platform->getObj()->setMaterialName("WallTexture_DIFFUSE.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), platform->getObj()->getMaterialName());
	platform->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), platform->getObj()->getNormalMapName());
	addObjectToObjHolder(background->getObj());
	addObjectToObjHolder(platform->getObj());
	addObjectToObjHolder(floor->getObj());
	addObjectToObjHolder(walls->getObj());
	addObjectToObjHolder(pillars->getObj());
	addObjectToObjHolder(foregroundWalls->getObj());
	addObjectToObjHolder(ladders->getObj());


	//GUI POLYGON COUNT
	slot1 = new GUItestClass;
	if (!slot1)
	{
		MessageBox(NULL, L"Error create slot1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init slot1 obj",
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
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingRedSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingBlueSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingWhiteSpriteSheet.png");
	slot1->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot1->getObj());
	slot1->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), slot1->getObj()->getNormalMapName());
	//GUI POLYGON COUNT
	slot2 = new GUItestClass;
	if (!slot2)
	{
		MessageBox(NULL, L"Error create slot2 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot2->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init slot2 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot2->getObj()->setWorldMatrix(slot2Mat);
	slot2->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot2->getObj());
	slot2->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), slot2->getObj()->getNormalMapName());
	//GUI POLYGON COUNT
	polygonDisp = new GUItestClass;
	if (!polygonDisp)
	{
		MessageBox(NULL, L"Error create polyDisp obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = polygonDisp->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init polyDisp obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	polygonDisp->getObj()->setWorldMatrix(polygonDispMat);
	polygonDisp->getObj()->setMaterialName("Polygon.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "Polygon.png");
	addObjectToObjHolder(polygonDisp->getObj());
	polygonDisp->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), polygonDisp->getObj()->getNormalMapName());
	//GUI RING HOLDER
	ringDisplay = new GUItestClass;
	if (!ringDisplay)
	{
		MessageBox(NULL, L"Error create ringDisp obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = ringDisplay->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init ringDisp obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ringDisplay->getObj()->setWorldMatrix(ringDisplayMat);
	//ringDisplay->getObj()->setMaterialName("sampleRing.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingGreen3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingRed3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingBlue3.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "RingWhite3.png");
	ringDisplay->setIsDestroy(true);
	ringDisplay->setCheckIfObjHolder(false);
	ringDisplay->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), ringDisplay->getObj()->getNormalMapName());
	//addObjectToObjHolder(ringDisplay->getObj());

	//GUI RING HOLDER
	xpDisplay = new GUItestClass;
	if (!xpDisplay)
	{
		MessageBox(NULL, L"Error create XpDisp obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = xpDisplay->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init XpDisp obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	xpDisplay->getObj()->setWorldMatrix(xpDisplayMat);
	xpDisplay->getObj()->setMaterialName("EXP0.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "EXP0.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "EXP1.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "EXP2.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "EXP3.png");
	//graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), "EXP4.png");
	xpDisplay->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), xpDisplay->getObj()->getNormalMapName());

	//GUI RING HOLDER
	slot1xp = new GUItestClass;
	if (!slot1xp)
	{
		MessageBox(NULL, L"Error create slot1XP obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot1xp->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init slot1XP obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot1xp->getObj()->setWorldMatrix(slot1xpMat);
	slot1xp->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot1xp->getObj());
	slot1xp->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), slot1xp->getObj()->getNormalMapName());
	//GUI RING HOLDER
	slot2xp = new GUItestClass;
	if (!slot2xp)
	{
		MessageBox(NULL, L"Error create slot2XP obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = slot2xp->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init slot2XP obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	slot2xp->getObj()->setWorldMatrix(slot2xpMat);
	slot2xp->getObj()->setMaterialName("0.png");
	addObjectToObjHolder(slot2xp->getObj());
	slot2xp->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), slot2xp->getObj()->getNormalMapName());
	addObjectToObjHolder(xpDisplay->getObj());
	//////////////////////////
	//		MENY			//
	//////////////////////////

	meny = new GUItestClass;
	if (!meny)
	{
		MessageBox(NULL, L"Error create Meny obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = meny->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init Meny obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	meny->getObj()->setWorldMatrix(menyMat);
	meny->getObj()->setMaterialName("MenuBackground.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), meny->getObj()->getMaterialName());
	meny->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), meny->getObj()->getNormalMapName());
	menyHighlight = new GUItestClass;
	if (!menyHighlight)
	{
		MessageBox(NULL, L"Error create menyHighlight obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = menyHighlight->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init menyHighlight obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	menyHighlight->getObj()->setWorldMatrix(menyHighlightMat);
	menyHighlight->getObj()->setMaterialName("MenuSelected.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), menyHighlight->getObj()->getMaterialName());
	addObjectToObjHolderMeny(menyHighlight->getObj());
	addObjectToObjHolderMeny(meny->getObj());
	menyHighlight->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), menyHighlight->getObj()->getNormalMapName());

	//////////////////////////
	//////	 LIMBO		//////
	//////////////////////////

	limboPickupHolder = new pickupClass[3];

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

	limboBackPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), limboBackPlane->getObj()->getNormalMapName());
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
	limboSmithPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), limboSmithPlane->getObj()->getNormalMapName());
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
	limboWalkingPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), limboWalkingPlane->getObj()->getNormalMapName());
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
	limboFrontPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), limboFrontPlane->getObj()->getNormalMapName());
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
	limboTextPlane->getObj()->setMaterialName("SmithTextSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboTextPlane->getObj()->getMaterialName());
	limboTextPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), limboTextPlane->getObj()->getNormalMapName());
	limboPickupHolder[1].clone(*limboTextPlane);
	limboPickupHolder[1].setFrameCount(4);
	limboPickupHolder[1].setAnimationCount(1);
	limboPickupHolder[1].setPickupType(5);

	addObjectToObjHolderLimbo(limboPickupHolder[1].getObj());

	//LIMBO Text PLANE
	limboTextPlanePressE = new pickupClass;
	if (!limboTextPlanePressE)
	{
		MessageBox(NULL, L"Error create limbo obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = limboTextPlanePressE->initlialize(graphics->getD3D()->GetDevice(), "LimboEnterPlane.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init pickup obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	limboTextPlanePressE->getObj()->setMaterialName("SmithTextEnterSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), limboTextPlanePressE->getObj()->getMaterialName());
	limboTextPlanePressE->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), limboTextPlanePressE->getObj()->getNormalMapName());
	limboPickupHolder[2].clone(*limboTextPlanePressE);
	limboPickupHolder[2].setFrameCount(4);
	limboPickupHolder[2].setAnimationCount(1);
	limboPickupHolder[2].setPickupType(5);

	addObjectToObjHolderLimbo(limboPickupHolder[2].getObj());
	//LIMBO UPGRADE
	upgradeGUI = new GUItestClass;
	if (!upgradeGUI)
	{
		MessageBox(NULL, L"Error create upgradeGUI obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = upgradeGUI->initlialize(graphics->getD3D()->GetDevice(), "LimboUpgradePlane.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init upgradeGUI obj",
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
	upgradeGUI->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), upgradeGUI->getObj()->getNormalMapName());

	//addObjectToObjHolderLimbo(upgradeGUI->getObj());

	//LIMBO UPGRADE OVERLAY
	upgradeOverlay = new GUItestClass;
	if (!upgradeOverlay)
	{
		MessageBox(NULL, L"Error create upgradeOverlay obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = upgradeOverlay->initlialize(graphics->getD3D()->GetDevice(), "LimboUpgradePlane.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init upgradeOverlay obj",
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
	upgradeOverlay->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), upgradeOverlay->getObj()->getNormalMapName());
	//
	//HEalth count
	healthUpgradeCount = new GUItestClass;
	if (!healthUpgradeCount)
	{
		MessageBox(NULL, L"Error create HealthUpgCnout obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = healthUpgradeCount->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init HealthUpgCnout obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	healthUpgradeCount->getObj()->setWorldMatrix(healthUpgradeCountMat);
	healthUpgradeCount->getObj()->setMaterialName("0.png");
	healthUpgradeCount->setIsDestroy(true);
	healthUpgradeCount->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), healthUpgradeCount->getObj()->getNormalMapName());
	//speed count
	speedUpgradeCount = new GUItestClass;
	if (!speedUpgradeCount)
	{
		MessageBox(NULL, L"Error create SpeedUpgCount obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = speedUpgradeCount->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init SpeedUpgCount obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	speedUpgradeCount->getObj()->setWorldMatrix(speedUpgradeCountMat);
	speedUpgradeCount->getObj()->setMaterialName("0.png");
	speedUpgradeCount->setIsDestroy(true);
	speedUpgradeCount->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), speedUpgradeCount->getObj()->getNormalMapName());

	//TOTAL COST PENDING
	totalCostPendingSlot1 = new GUItestClass;
	if (!totalCostPendingSlot1)
	{
		MessageBox(NULL, L"Error create totCostPenSlot1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = totalCostPendingSlot1->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init totCostPenSlot1 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	totalCostPendingSlot1->getObj()->setWorldMatrix(totalCostPendingSlot1Mat);
	totalCostPendingSlot1->getObj()->setMaterialName("0.png");
	totalCostPendingSlot1->setIsDestroy(true);
	totalCostPendingSlot1->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), totalCostPendingSlot1->getObj()->getNormalMapName());
	//speed count
	totalCostPendingSlot2 = new GUItestClass;
	if (!totalCostPendingSlot2)
	{
		MessageBox(NULL, L"Error create totCostPenSlot2 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = totalCostPendingSlot2->initlialize(graphics->getD3D()->GetDevice(), "guiSkit3.bin", hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init totCostPenSlot2 obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	totalCostPendingSlot2->getObj()->setWorldMatrix(totalCostPendingSlot2Mat);
	totalCostPendingSlot2->getObj()->setMaterialName("0.png");
	totalCostPendingSlot2->setIsDestroy(true);
	totalCostPendingSlot2->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), totalCostPendingSlot2->getObj()->getNormalMapName());
	//PORTAL
	portalPlane = new pickupClass;
	if (!portalPlane)
	{
		MessageBox(NULL, L"Error create portal obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = portalPlane->initlialize(graphics->getD3D()->GetDevice(), "Portal.bin");
	if (!result)
	{
		MessageBox(NULL, L"Error init portal obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	portalPlane->getObj()->setMaterialName("PortalSpriteSheet.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), portalPlane->getObj()->getMaterialName());
	portalPlane->setFrameCount(24);
	portalPlane->setAnimationCount(1);
	portalPlane->setPickupType(7);
	portalPlane->setIsDestroy(false);
	portalPlane->setTranslationMatStart(XMMatrixTranslation(XMVectorGetX(spawnBoss->getObj()->getPosition()) + 2.0f, XMVectorGetY(spawnBoss->getObj()->getPosition()) - 8.0f, 0.0f));
	portalPlane->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), portalPlane->getObj()->getNormalMapName());
	//nrOfVisiblePickups++;
	//addPickupToPickupHolder(*portalPlane, nrOfVisiblePickups);

	//pickupHolder[nrOfVisiblePickups - 1].setFrameCount(24);
	//pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(24);
	//pickupHolder[nrOfVisiblePickups - 1].setAnimationCount(1);
	//pickupHolder[nrOfVisiblePickups - 1].getObj()->setAnimationCount(1);
	//pickupHolder[nrOfVisiblePickups - 1].setPickupType(7);
	////pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
	//pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(portalMat);

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
	win->getObj()->setMaterialName("Win.png");
	graphics->getShaders()->createTextureReasourceAndTextureView(graphics->getD3D()->GetDevice(), win->getObj()->getMaterialName());
	win->getObj()->setNormalMapName("normal_3.jpg");
	graphics->getShaders()->createNormalMapInfo(graphics->getD3D()->GetDevice(), win->getObj()->getNormalMapName());
	addObjectToObjHolderWin(win->getObj());
	initializeRings();
	initializeEnemies();

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
	if (boss)
	{
		boss->shutdown();
		delete boss;
		boss = 0;
	}
	if (xpDisplay)
	{
		xpDisplay->shutdown();
		delete xpDisplay;
		xpDisplay = 0;
	}
	if (bossdoor)
	{
		bossdoor->shutdown();
		delete bossdoor;
		bossdoor = 0;
	}
	if (ladders)
	{
		ladders->shutdown();
		delete ladders;
		ladders = 0;
	}

	if (sound)
	{
		sound->shutdown();
		delete sound;
		sound = 0;
	}
	if (pickupSpawn)
	{
		pickupSpawn->shutdown();
		delete pickupSpawn;
		pickupSpawn = 0;
	}
	if (movementInput)
	{
		movementInput->shutdown();
		delete movementInput;
		movementInput = 0;
	}
	if (enemy2)
	{
		enemy2->shutdown();
		delete enemy2;
		enemy2 = 0;
	}
	if (enemyHolder)
	{
		for (int i = 0; i < nrOfVisibleEnemies; i++)
		{
			enemyHolder[i].shutdown();
		}

		delete[] enemyHolder;
		enemyHolder = 0;
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
	if (floor)
	{
		floor->shutdown();
		delete floor;
		floor = 0;
	}
	if (walls)
	{
		walls->shutdown();
		delete walls;
		walls = 0;
	}
	if (pillars)
	{
		pillars->shutdown();
		delete pillars;
		pillars = 0;
	}
	if (foregroundWalls)
	{
		foregroundWalls->shutdown();
		delete foregroundWalls;
		foregroundWalls = 0;
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
	if (spawnEnemys)
	{
		spawnEnemys->shutdown();
		delete spawnEnemys;
		spawnEnemys = 0;
	}
	if (speedUpgradeCount)
	{
		speedUpgradeCount->shutdown();
		delete speedUpgradeCount;
		speedUpgradeCount = 0;
	}
	if (polygonDisp)
	{
		polygonDisp->shutdown();
		delete polygonDisp;
		polygonDisp = 0;
	}
	if (healthUpgradeCount)
	{
		healthUpgradeCount->shutdown();
		delete healthUpgradeCount;
		healthUpgradeCount = 0;
	}
	if (coldownDisplay)
	{
		coldownDisplay->shutdown();
		delete coldownDisplay;
		coldownDisplay = 0;
	}
	if (ring)
	{
		ring->shutdown();
		delete ring;
		ring = 0;
	}
	if (shieldBubble)
	{
		shieldBubble->shutdown();
		delete shieldBubble;
		shieldBubble = 0;
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
	if (limboTextPlanePressE)
	{
		limboTextPlanePressE->shutdown();
		delete limboTextPlanePressE;
		limboTextPlanePressE = 0;
	}
	if (limboPickupHolder)
	{
		for (int i = 0; i < 3; i++)
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
	if (spawnBoss)
	{
		spawnBoss->shutdown();
		delete spawnBoss;
		spawnBoss = 0;
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

	if (enemyFire)
	{
		enemyFire->shutdown();
		delete enemyFire;
		enemyFire = 0;
	}
	if (bossFire2)
	{
		bossFire2->shutdown();
		delete bossFire2;
		bossFire2 = 0;
	}
	if (bossFire3)
	{
		bossFire3->shutdown();
		delete bossFire3;
		bossFire3 = 0;
	}
	if (bossFire4)
	{
		bossFire4->shutdown();
		delete bossFire4;
		bossFire4 = 0;
	}
	if (bossFire5)
	{
		bossFire5->shutdown();
		delete bossFire5;
		bossFire5 = 0;
	}
	if (bossFire6)
	{
		bossFire6->shutdown();
		delete bossFire6;
		bossFire6 = 0;
	}
	if (boss)
	{
		boss->shutdown();
		delete boss;
		boss = 0;
	}
	if (bossdoor)
	{
		bossdoor->shutdown();
		delete bossdoor;
		bossdoor = 0;
	}
	if (bossIce)
	{
		bossIce->shutdown();
		delete bossIce;
		bossIce = 0;
	}
	if (bossFire)
	{
		bossFire->shutdown();
		delete bossFire;
		bossFire = 0;
	}
	if (floor)
	{
		floor->shutdown();
		delete floor;
		floor = 0;
	}
	if (walls)
	{
		walls->shutdown();
		delete walls;
		walls = 0;
	}
	if (pillars)
	{
		pillars->shutdown();
		delete pillars;
		pillars = 0;
	}
	if (foregroundWalls)
	{
		foregroundWalls->shutdown();
		delete foregroundWalls;
		foregroundWalls = 0;
	}
	//////////////////////////
	if (spiderweeb)
	{
		spiderweeb->shutdown();
		delete spiderweeb;
		spiderweeb = 0;
	}
	if (barrel)
	{
		barrel->shutdown();
		delete barrel;
		barrel = 0;
	}
	if (candle)
	{
		candle->shutdown();
		delete candle;
		candle = 0;
	}
	if (plank)
	{
		plank->shutdown();
		delete plank;
		plank = 0;
	}
	if (painting1)
	{
		painting1->shutdown();
		delete painting1;
		painting1 = 0;
	}
	if (painting2)
	{
		painting2->shutdown();
		delete painting2;
		painting2 = 0;
	}
	if (ironmaiden)
	{
		ironmaiden->shutdown();
		delete ironmaiden;
		ironmaiden = 0;
	}
	if (sewer)
	{
		sewer->shutdown();
		delete sewer;
		sewer = 0;
	}
	if (bannerCarpet)
	{
		bannerCarpet->shutdown();
		delete bannerCarpet;
		bannerCarpet = 0;
	}
	if (crate)
	{
		crate->shutdown();
		delete crate;
		crate = 0;
	}
	/////////////////////////
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
	if (portalPlane)
	{
		portalPlane->shutdown();
		delete portalPlane;
		portalPlane = 0;
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
	XMMATRIX tJoints[30];

	graphics->beginScene();
	for (int i = 0; i < objHolderWin.size(); i++)
	{
		result = graphics->frame(objHolderWin[i], view, proj, objHolderWin[i]->getType(), objHolderWin[i]->getMaterialName(), objHolderWin[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0);
		if (!result)
		{
			return false;
		}
	}
	graphics->endScene();


	if (inputDirectOther->isEscapePressed() == true)
	{
		player->resetPlayer();
		player->setMaxHP(1);
		player->setPlayerHP(1);
		if (pickupHolder)
		{
			for (int i = 0; i < nrOfVisiblePickups; i++)
			{
				pickupHolder[i].resetPickup();
			}
		}
		ringDisplay->setIsDestroy(true);
		initializeRings();
		for (int i = 0; i < nrOfVisibleEnemies; i++)
		{
			enemyHolder[i].resetEnemy();
		}
		initializeEnemies();
		slot1->setIsDestroy(true);
		slot2->setIsDestroy(true);
		slot1xp->setIsDestroy(true);
		slot2xp->setIsDestroy(true);
		projectile->resetProjectile();
		projectile->setIsDestroyed(false);
		enemyFire->resetFireEnemy();
		bossIce->resetFireEnemy();
		bossFire->resetFireEnemy();
		bossBattleEntered = false;

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

	for (int i = 0; i < 3; i++)
	{
		limboPickupHolder[i].updateAnimation(dt);
	}

	//shop
	updateShop(dt, upgradeGUI, upgradeOverlay);

	graphics->beginScene();

	int pickupCheck = 0;
	XMMATRIX tJoints[30];
	for (int i = 0; i < objHolderLimbo.size(); i++)
	{
		if (objHolderLimbo[i]->getType() == 2)
		{
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), objHolderLimbo[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, player->getFrameCount(), player->getCurrentFrame(), player->getCurrentAnimation(), player->getFlipped());
			if (!result)

			{
				return false;
			}
		}

		else if (objHolderLimbo[i]->getType() == 4)
		{
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), objHolderLimbo[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, limboPickupHolder[pickupCheck].getFrameCount(), limboPickupHolder[pickupCheck].getCurrentFrame());
			pickupCheck++;
			if (!result)
			{
				return false;
			}
		}

		else if (objHolderLimbo[i]->getType() == 3) {
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), objHolderLimbo[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 2);
			if (!result)
			{
				return false;
			}

		}

		else
		{
			result = graphics->frame(objHolderLimbo[i], view, ortoProj, objHolderLimbo[i]->getType(), objHolderLimbo[i]->getMaterialName(), objHolderLimbo[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0);
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
		projectile->resetProjectile();
		projectile->setIsDestroyed(false);
		enemyFire->resetFireEnemy();

		upgradeOverlay->setIsDestroy(true);
		setShopOverlayCounter(0);
		setShopOverlayCounterRow(0);
		activeShopState = 0;
		boss->setEnemyHP(100);

		if (soundAvailable)
			sound->playAmbient(1);

		std::ofstream myfile;
		myfile.open("readThis.txt");
		myfile << std::to_string(player->getMaxHP()) + "\n";
		myfile << std::to_string(player->getSpeedVal()) + "\n";
		myfile << std::to_string(SpeedCost) + "\n";
		myfile << std::to_string(healthCost) + "\n";
		myfile << std::to_string(player->getNrPixelFramgent()) + "\n";
		myfile << std::to_string(player->getNrPolygons()) + "\n";
		myfile << std::to_string(tempXP) + "\n";
		myfile << std::to_string(player->getWeaponType()) + "\n";
		myfile.close();


		return false;
	}
	if (inputDirectOther->isEscapePressed() == true)
	{
		gameStateLevel = false;
		gameStateLimbo = false;
		gameStateMeny = true;
		player->resetPlayer();
		player->setMaxHP(1);
		player->setPlayerHP(1);
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

	if (boss->getIsActive() && boss->getCheckIfObjHolder())
	{
		updateBoss(dt);
	}
	if (!boss->getIsActive() && boss->getCheckIfObjHolder())
	{
		removeObjFromObjHolder(boss->getObj());
		boss->setCheckIfObjHolder(false);
	}

	if (!portalPlane->getIsDestry() && !portalPlane->getCheckIfObjHolder())
	{
		addObjectToObjHolder(portalPlane->getObj());
		portalPlane->setCheckIfObjHolder(true);
	}

	if (portalPlane->getIsDestry() && portalPlane->getCheckIfObjHolder())
	{
		removeObjFromObjHolder(portalPlane->getObj());
		portalPlane->setCheckIfObjHolder(false);
	}
	if (!portalPlane->getIsDestry() && portalPlane->getCheckIfObjHolder())
	{
		updatePortal(dt);
	}
	//enemy stuff
	for (int i = 0; i < nrOfVisibleEnemies; i++)
	{
		if (enemyHolder[i].getIsActive() && !enemyHolder[i].getCheckIfObjHolder())
		{
			addObjectToObjHolder(enemyHolder[i].getObj());
			enemyHolder[i].setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);
		}
	}

	if (enemyHolder)
	{
		updateEnemy(dt);
	}

	for (int i = 0; i < nrOfVisibleEnemies; i++)
	{
		if (!enemyHolder[i].getIsActive() && enemyHolder[i].getCheckIfObjHolder())
		{
			removeObjFromObjHolder(enemyHolder[i].getObj());
			enemyHolder[i].setCheckIfObjHolder(false);
			nrOfVisibleEnemies--;
			removeEnemyFromEnemyHolder(enemyHolder[i], nrOfVisibleEnemies);
			i = 0;
		}
	}


	//if (!coldownDisplay->getIsDestry() && !coldownDisplay->getCheckIfObjHolder())
	//{
	//	addObjectToObjHolder(coldownDisplay->getObj());
	//	coldownDisplay->setCheckIfObjHolder(true);
	//	coldownDisplay->setIsDestroy(false);
	//}
	//updateColdownDisplay(dt);
	//if (coldownDisplay->getIsDestry() && coldownDisplay->getCheckIfObjHolder())
	//{
	//	removeObjFromObjHolder(coldownDisplay->getObj());
	//	coldownDisplay->setCheckIfObjHolder(false);
	//	coldownDisplay->setIsDestroy(true);
	//}
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
	if (!projectile->getIsDestroyed() && !projectile->getCheckIfObjHolder() && player->getMagicCast())
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

	if (!projectile->getIsDestroyed() && projectile->getCheckIfObjHolder() && player->getMagicCast())
	{
		updateProjectile(dt, projectile, 0);
	}

	//update player shadow
	updatePlayerShadow();

	//update shield
	updateShield(dt);

	//update plygonscout GUI
	updateRingDisplay();
	updateXpDisplayMat();
	updateSlotXp(slot1xpMat, slot2xpMat);
	updateGUIPolygon(slot1Mat, slot2Mat);


	if (!bossDoorDestoryed && !bossDoorInObjHolder)
	{
		addObjectToObjHolder(bossdoor->getObj());
		bossDoorInObjHolder = true;
		
		if (!bossBattleEntered && soundAvailable)
		{
			sound->playAmbient(4);
			bossBattleEntered = true;
		}
	}
	if (!bossDoorDestoryed && bossDoorInObjHolder)
	{
		updateBossDoor();
	}
	if (bossDoorDestoryed && bossDoorInObjHolder)
	{
		removeObjFromObjHolder(bossdoor->getObj());
		bossDoorInObjHolder = false;

		if (bossBattleEntered && soundAvailable)
		{
			sound->playAmbient(1);
			bossBattleEntered = false;
		}
	}


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
	int enemyTypeChecker = 0;
	XMMATRIX tJoints[30];
	graphics->beginScene();
	for (int i = 0; i < objHolder.size(); i++)
	{
		if (objHolder[i]->getType() == 2)
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, player->getFrameCount(), player->getCurrentFrame(), player->getCurrentAnimation(), player->getFlipped());
			if (!result)

			{
				return false;
			}
		}

		else if (objHolder[i]->getType() == 4)
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, objHolder[i]->getFrameCount(), objHolder[i]->getCurrentFrame());
			if (!result)
			{
				return false;
			}
			pickupTypeChecker++;
		}
		else if (objHolder[i]->getType() == 3)
		{
			for (int j = 0; j < objHolder[i]->getJointCount(); j++)
			{
				objHolder[i]->getTransformMatrix(tJoints[j], j);
			}
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, objHolder[i]->getJointCount(), enemyHolder[enemyTypeChecker - 1].getHurt());
			if (!result)
			{
				return false;
			}
			enemyTypeChecker++;

		}

		else if (objHolder[i]->getType() == 5)
		{
			if (!projectile->getIsDestroyed())
				result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, objHolder[i]->getFrameCount(), objHolder[i]->getCurrentFrame(), projectile->getCurrentAnimation(), projectile->getGoesRight());
			if (!enemyFire->getIsDestroyed())
				result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, objHolder[i]->getFrameCount(), objHolder[i]->getCurrentFrame(), enemyFire->getCurrentAnimation(), enemyFire->getGoesRight());
			if (!bossFire->getIsDestroyed())
				result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, objHolder[i]->getFrameCount(), objHolder[i]->getCurrentFrame(), bossFire->getCurrentAnimation(), bossFire->getGoesRight());
			if (!bossIce->getIsDestroyed())
				result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0, objHolder[i]->getFrameCount(), objHolder[i]->getCurrentFrame(), bossIce->getCurrentAnimation(), bossIce->getGoesRight());
			
			if (!result)
			{
				return false;
			}
		}

		else
		{
			result = graphics->frame(objHolder[i], view, proj, objHolder[i]->getType(), objHolder[i]->getMaterialName(), objHolder[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0);
			if (!result)

			{
				return false;
			}
		}
	}
	graphics->endScene();

	if (player->getCurrentAnimation() == 7 && player->getCurrentFrame() == 9)
	{
		player->resetPlayer();
		player->setAnimation(1);
		camera->reset();
		if (pickupHolder)
		{
			for (int i = 0; i < nrOfVisiblePickups; i++)
			{
				pickupHolder[i].resetPickup();
			}
		}
		initializeRings();
		for (int i = 0; i < nrOfVisibleEnemies; i++)
		{
			enemyHolder[i].resetEnemy();
		}
		initializeEnemies();
		projectile->resetProjectile();
		projectile->setIsDestroyed(false);
		enemyFire->resetFireEnemy();
		bossIce->resetFireEnemy();
		bossFire->resetFireEnemy();
		boss->setEnemyHP(100);
		bossBattleEntered = false;

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
		player->setMaxHP(1);
		player->setPlayerHP(1);
		if (pickupHolder)
		{
			for (int i = 0; i < nrOfVisiblePickups; i++)
			{
				pickupHolder[i].resetPickup();
			}
		}
		ringDisplay->setIsDestroy(true);
		initializeRings();
		for (int i = 0; i < nrOfVisibleEnemies; i++)
		{
			enemyHolder[i].resetEnemy();
		}
		initializeEnemies();
		slot1->setIsDestroy(true);
		slot2->setIsDestroy(true);
		slot1xp->setIsDestroy(true);
		slot2xp->setIsDestroy(true);
		projectile->resetProjectile();
		projectile->setIsDestroyed(false);
		enemyFire->resetFireEnemy();
		bossIce->resetFireEnemy();
		bossFire->resetFireEnemy();
		bossBattleEntered = false;

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

	removeObjFromObjHolder(foregroundWalls->getObj());
	addObjectToObjHolder(foregroundWalls->getObj());

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
	XMMATRIX tJoints[30];
	graphics->beginScene();
	for (int i = 0; i < objHolderMeny.size(); i++)
	{
		result = graphics->frame(objHolderMeny[i], view, proj, objHolderMeny[i]->getType(), objHolderMeny[i]->getMaterialName(), objHolderMeny[i]->getNormalMapName(), camera->getPosition(), tJoints, player->getWeaponType(), 0);
		if (!result)

		{
			return false;
		}
	}
	graphics->endScene();

	//NEW GAME
	if (inputDirectOther->isEnterPressed() && counterOverlay == 0)
	{
		gameStateLevel = true;
		if (soundAvailable)
		{
			sound->playSFX(0, 1);
			sound->playAmbient(1);
		}
		for (int i = 4; i > 0; i--)
		{
			removeObjFromObjHolder(heartHolder[i].getObj());
			heartHolder[i].setCheckIfObjHolder(false);
			heartHolder[i].setIsDestroy(true);
			heartHolder[i].setIsBought(false);
		}

		player->setPlayerHP(1);
		player->setMaxHP(1);
		healthCost = 1;
		SpeedCost = 1;
		boss->setEnemyHP(100);
		boss->setIsActive(true);

		player->setSpeedVal(10);

		player->setWeaponType(0);

		player->setNrPixelFragments(0);

		for (int i = 0; i < 4; i++) {
			player->setNrWeaponBought(i, false);
		}
	}

	if (inputDirectOther->isEnterPressed() && counterOverlay == 1)
	{
		if (soundAvailable)
			sound->playSFX(0, 1);

		gameStateLevel = true;
		std::string line;
		int arr[8] = { 0 };
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
		player->setNrPixelFragments(arr[4]);
		player->setNrPolysgons(arr[5]);
		tempXP = arr[6];
		player->setWeaponType(arr[7]);
		boss->setEnemyHP(100);
		boss->setIsActive(true);

		for (int i = player->getMaxHP() - 1; i > 0; i--)
		{
			if (!heartHolder[i].getIsDestry() && !heartHolder[i].getCheckIfObjHolder())
			{
				addObjectToObjHolder(heartHolder[i].getObj());
				heartHolder[i].setCheckIfObjHolder(true);
				heartHolder[i].setIsDestroy(false);
				heartHolder[i].setIsBought(true);
				OutputDebugString(L"\nheart was created!\n");
			}
		}
		
	}

	if (inputDirectOther->isEnterPressed() == true && counterOverlay == 2)
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
	/*OutputDebugString(L"\npickup created!\n");*/

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
				tempArray[j] = pickupHolder[i];
				j++;
			}
		}

		delete[] pickupHolder;
		pickupHolder = tempArray;
	}
}

void gameClass::addEnemyToEnemyHolder(enemyClass & enemy, int nrOfVisibleEnemies, XMVECTOR vector, int type)
{

	enemyClass* tempArray = new enemyClass[nrOfVisibleEnemies];

	for (int i = 0; i < nrOfVisibleEnemies - 1; i++)
	{
		tempArray[i] = enemyHolder[i];
	}

	delete[] enemyHolder;
	enemyHolder = tempArray;
	enemyHolder[nrOfVisibleEnemies - 1].clone(enemy, vector, type);
}

void gameClass::removeEnemyFromEnemyHolder(enemyClass & enemy, int nrOfVisibleEnemies)
{
	int index = -1;
	for (int i = 0; i < nrOfVisibleEnemies + 1; i++)
	{
		if (enemyHolder[i].getObj() == enemy.getObj())
		{
			index = i;
		}
	}

	if (index != -1)
	{
		enemyClass* tempArray = new enemyClass[nrOfVisibleEnemies];
		enemyHolder[index].shutdown();
		int j = 0;
		for (int i = 0; i < nrOfVisibleEnemies + 1; i++)
		{
			if (i != index)
			{
				/*OutputDebugString(L"\nRemoving\n");*/
				tempArray[j] = enemyHolder[i];
				j++;
			}
		}

		delete[] enemyHolder;
		enemyHolder = tempArray;
	}
}

void gameClass::initializeRings()
{
	//nrOfVisiblePickups++;
	//addPickupToPickupHolder(*portalPlane, nrOfVisiblePickups);

	//pickupHolder[nrOfVisiblePickups - 1].setFrameCount(24);
	//pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(24);
	//pickupHolder[nrOfVisiblePickups - 1].setAnimationCount(1);
	//pickupHolder[nrOfVisiblePickups - 1].getObj()->setAnimationCount(1);
	//pickupHolder[nrOfVisiblePickups - 1].setPickupType(7);
	////pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
	//pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(portalMat);

	int index = 0;
	int previousRing = -1;

	while (index < 2)
	{
		srand(time(NULL));
		pickupClass ringTemp;
		ringTemp.clone(*ring);
		nrOfVisiblePickups++;
		addPickupToPickupHolder(ringTemp, nrOfVisiblePickups);
		pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(XMMatrixScaling(0.3f, 0.5f, 0.0f) * XMMatrixTranslation(XMVectorGetX(pickupSpawn->getObj()->getPositionWithIndex(index)), XMVectorGetY(pickupSpawn->getObj()->getPositionWithIndex(index)), 0.1f));
		pickupHolder[nrOfVisiblePickups - 1].setPickupType(3);
		pickupHolder[nrOfVisiblePickups - 1].setRingType(rand() % 4);

		if (previousRing == pickupHolder[nrOfVisiblePickups - 1].getRingType())
		{
			if (previousRing == 0)
			{
				pickupHolder[nrOfVisiblePickups - 1].setRingType(rand() % 3 + 1);
			}
			else if (previousRing == 1)
			{
				previousRing = rand() % 3;
				if (previousRing == 0)
				{
					pickupHolder[nrOfVisiblePickups - 1].setRingType(0);
				}
				if (previousRing == 1)
				{
					pickupHolder[nrOfVisiblePickups - 1].setRingType(2);
				}
				if (previousRing == 2)
				{
					pickupHolder[nrOfVisiblePickups - 1].setRingType(3);
				}
			}
			else if (previousRing == 2)
			{
				previousRing = rand() % 3;
				if (previousRing == 0)
				{
					pickupHolder[nrOfVisiblePickups - 1].setRingType(0);
				}
				if (previousRing == 1)
				{
					pickupHolder[nrOfVisiblePickups - 1].setRingType(1);
				}
				if (previousRing == 2)
				{
					pickupHolder[nrOfVisiblePickups - 1].setRingType(3);
				}
			}
			else if (previousRing == 3)
			{
				pickupHolder[nrOfVisiblePickups - 1].setRingType(rand() % 3);
			}

		}

		if (pickupHolder[nrOfVisiblePickups - 1].getRingType() == 0)
		{
			OutputDebugString(L"\n0. Doublejump\n");
			previousRing = 0;
			index++;
		}
		else if (pickupHolder[nrOfVisiblePickups - 1].getRingType() == 1)
		{
			OutputDebugString(L"\n1. Fireball\n");
			previousRing = 1;
			index++;
		}
		else if (pickupHolder[nrOfVisiblePickups - 1].getRingType() == 2)
		{
			OutputDebugString(L"\n2. Frostbolt\n");
			previousRing = 2;
			index++;
		}
		else if (pickupHolder[nrOfVisiblePickups - 1].getRingType() == 3)
		{
			OutputDebugString(L"\n3. Shield Bubble\n");
			previousRing = 3;
			index++;
		}

		previousRing = pickupHolder[nrOfVisiblePickups - 1].getRingType();
		pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
		pickupHolder[nrOfVisiblePickups - 1].setFrameCount(4);
		pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(4);
		ringTemp.shutdown();
	}
}

void gameClass::initializeEnemies()
{
	for (int i = 0; i < 15; i++)
	{
		enemyClass enemyTemp;
		int randValue = rand() % 2;
		if (randValue == 0)
		{
			enemyTemp.clone(*enemy, spawnEnemys->getObj()->getPositionWithIndex(i), 0);
			nrOfVisibleEnemies++;
			addEnemyToEnemyHolder(enemyTemp, nrOfVisibleEnemies, spawnEnemys->getObj()->getPositionWithIndex(i), 0);
		}
		else
		{
			enemyTemp.clone(*enemy2, spawnEnemys->getObj()->getPositionWithIndex(i), 1);
			nrOfVisibleEnemies++;
			addEnemyToEnemyHolder(enemyTemp, nrOfVisibleEnemies, spawnEnemys->getObj()->getPositionWithIndex(i), 1);
		}
		enemyHolder[nrOfVisibleEnemies - 1].getTranslationMatStart(tempEnemyStartingPositionMatrix);
		enemyHolder[nrOfVisibleEnemies - 1].setIsActive(true);
		enemyHolder[nrOfVisibleEnemies - 1].setEnemyHP((i + 4) + 1);

		XMVECTOR tBboxMax;
		XMVECTOR tBboxMin;
		tBboxMax = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()) + 1, XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()) };
		tBboxMin = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()), XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()) };
		enemyHolder[nrOfVisibleEnemies - 1].setBboxMaxWeaponRight(tBboxMax);
		enemyHolder[nrOfVisibleEnemies - 1].setBboxMinWeaponRight(tBboxMin);

		tBboxMax = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()), XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()) };
		tBboxMin = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()) - 1, XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()) };
		enemyHolder[nrOfVisibleEnemies - 1].setBboxMaxWeaponLeft(tBboxMax);
		enemyHolder[nrOfVisibleEnemies - 1].setBboxMinWeaponLeft(tBboxMin);

		enemyTemp.shutdown();
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


void gameClass::updateBossDoor()
{
	bossdoor->getObj()->setWorldMatrix(XMMatrixIdentity());
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
	for (int i = 0; i < nrOfVisibleEnemies; i++)
	{

		if (enemyHolder[i].getIsFrozen())
		{
			enemyHolder[i].updateFrozenTimer(dt);
		}

		if (enemyHolder[i].getEnemyType() == 0 && !enemyHolder[i].getAttackAnimation())
		{
			enemyHolder[i].getObj()->setStartFrame(61);
			enemyHolder[i].getObj()->setEndFrame(83);
		}

		if (enemyHolder[i].getEnemyType() == 1)
		{
			enemyHolder[i].getObj()->setStartFrame(1);
			enemyHolder[i].getObj()->setEndFrame(39);
		}

		enemyHolder[i].updateFalling(dt);
		/*enemyHolder[i].getObj()->setWorldMatrix(tempEnemyStartingPositionMatrix);*/
		//jag vet att detta är förvirrande men denna tranlationmat func hämtar ut ett värde i x som gör att vår sak rör på oss
		enemyHolder[i].getTranslationMat(tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame);
		enemyHolder[i].getFallingMat(tempEnemyIfAirThenFallMatrix);
		enemyHolder[i].getMasterMovementEnemy(tempMasterMovementEnemyMat);
		//denna håller i alla värden så att vi inte flippar bounding boxen också
		enemyHolder[i].getEnemyTranslationMatrix(tempEnemyTranslationMatrix);
		enemyHolder[i].getTranslationMatStart(tempEnemyStartingPositionMatrix);
		if (!enemyHolder[i].getRoationCheck())
		{
			tempMasterMovementEnemyMat = tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
			tempEnemyTranslationMatrix = tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
		}
		else
		{
			tempMasterMovementEnemyMat = XMMatrixRotationY(-3.1514f) * tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
			tempEnemyTranslationMatrix = tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
		}
		enemyHolder[i].getObj()->setWorldMatrix(tempMasterMovementEnemyMat);
		///////////////
		enemyHolder[i].checkCollisionsY(checkCollisionPlatformTop(platform, enemyHolder[i].getObj(), tempEnemyTranslationMatrix), checkCollisionPlatformBot(platform, enemyHolder[i].getObj(), tempEnemyTranslationMatrix));
		enemyHolder[i].checkCollisionsX(checkCollisionPlatformLeft(platform, enemyHolder[i].getObj(), tempEnemyTranslationMatrix), checkCollisionPlatformRight(platform, enemyHolder[i].getObj(), tempEnemyTranslationMatrix));
		//enemyHolder[i].getObj()->setWorldMatrix(tempEnemyStartingPositionMatrix);
		enemyHolder[i].getTranslationMat(tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame);
		enemyHolder[i].getFallingMat(tempEnemyIfAirThenFallMatrix);
		if (!enemyHolder[i].getRoationCheck())
		{
			tempMasterMovementEnemyMat = tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
			tempEnemyTranslationMatrix = tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
		}
		else
		{
			tempMasterMovementEnemyMat = XMMatrixRotationY(-3.1514f) * tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
			tempEnemyTranslationMatrix = tempEnemyIfAirThenFallMatrix * tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix;
		}
		enemyHolder[i].setMasterMovementEnemy(tempMasterMovementEnemyMat);
		enemyHolder[i].setEnemyTranslationMatrix(tempEnemyTranslationMatrix);
		enemyHolder[i].getObj()->setWorldMatrix(tempMasterMovementEnemyMat);

		//boss->getObj()->setWorldMatrix(XMMatrixIdentity());
		enemyHolder[i].setMasterMovementEnemy(tempMasterMovementEnemyMat);
		enemyHolder[i].setEnemyTranslationMatrix(tempEnemyTranslationMatrix);
		enemyHolder[i].getObj()->setWorldMatrix(tempMasterMovementEnemyMat);

		if (enemyHolder[i].getAttackAnimation() && enemyHolder[i].getObj()->getFrameCount() >= enemyHolder[i].getObj()->getEndFrame() - 1)
		{
			enemyHolder[i].setAttackAnimation(false);
		}
	}
}

void gameClass::updatePlayer(platformClass* platform, double dt)
{
	if (player->getCurrentAnimation() != 7) {
		player->handleMovement(dt, isTextDestroy2);
	}
	player->updateAnimation(dt);
	player->getMoveMat(playerMove);
	player->getObj()->setWorldMatrix(playerMove);

	player->checkCollisions(checkCollisionPlatformTop(platform, player->getObj(), playerMove), checkCollisionPlatformLeft(platform, player->getObj(), playerMove), checkCollisionPlatformRight(platform, player->getObj(), playerMove), checkCollisionPlatformBot(platform, player->getObj(), playerMove), dt);
	if (bossDoorInObjHolder && !bossDoorDestoryed)
		player->checkCollisions(checkCollisionPlatformTop(bossdoor, player->getObj(), playerMove), checkCollisionPlatformLeft(bossdoor, player->getObj(), playerMove), checkCollisionPlatformRight(bossdoor, player->getObj(), playerMove), checkCollisionPlatformBot(bossdoor, player->getObj(), playerMove), dt);

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

void gameClass::updateShield(double dt)
{
	if (player->getShieldBubbleCast())
	{
		if (!shieldBubble->getCheckIfObjHolder())
		{
			addObjectToObjHolder(shieldBubble->getObj());
			shieldBubble->setCheckIfObjHolder(true);

			//player->setIfInObjHolder(false);
			//removeObjFromObjHolder(player->getObj());
		}
		shieldBubble->updateAnimation(dt);
		shieldBubble->getObj()->setWorldMatrix(playerMove);
		player->setInvulnurable(true);
	}
	else
	{
		shieldBubble->setCheckIfObjHolder(false);
		removeObjFromObjHolder(shieldBubble->getObj());
	}
}

void gameClass::updateCamera()
{
	float useThisX = XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2);
	//float useThisX = XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + differenceX;

	float useThisY = XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)));

	//int useThisY = XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + differenceX;

	if (useThisX > -147 && useThisX < 20)
	{
		camera->updatePosition(useThisX, useThisY);
		camera->updateTarget(useThisX, useThisY);
		camera->updatePositionZ(-20);
		camera->setTempX(useThisX);
	}
	else
	{
		camera->updatePosition(camera->getTempX(), useThisY);
		camera->updateTarget(camera->getTempX(), useThisY);
		camera->updatePositionZ(-20);
	}

	if (useThisX > -55.15f && useThisY > 73.15f)
	{
		if (useThisX > -56.15 && useThisX < -3.0f)
		{
			camera->updatePosition(-30.0f, 80.0f);
			camera->updateTarget(-30.0f, 80.0f);
			camera->updatePositionZ(-35); //-35
			bossDoorDestoryed = false;
			//player->setIfInObjHolder(false);
			bossIsInCombat = true;
		}
		else
		{
			bossDoorDestoryed = true;
			bossIsInCombat = false;
		}
	}
	else
	{
		bossDoorDestoryed = true;
		bossIsInCombat = false;
	}
}

void gameClass::staticBackground()
{
	backgroundMat = XMMatrixIdentity();
	background->getObj()->setWorldMatrix(backgroundMat);

	ladders->getObj()->setWorldMatrix(backgroundMat);
	floor->getObj()->setWorldMatrix(backgroundMat);
	walls->getObj()->setWorldMatrix(backgroundMat);
	pillars->getObj()->setWorldMatrix(backgroundMat);
	foregroundWalls->getObj()->setWorldMatrix(backgroundMat);


	//spiderweeb->getObj()->setWorldMatrix(backgroundMat);
	//barrel->getObj()->setWorldMatrix(backgroundMat);
	//candle->getObj()->setWorldMatrix(backgroundMat);
	//plank->getObj()->setWorldMatrix(backgroundMat);
	//painting1->getObj()->setWorldMatrix(backgroundMat);
	//painting2->getObj()->setWorldMatrix(backgroundMat);
	//ironmaiden->getObj()->setWorldMatrix(backgroundMat);
	//sewer->getObj()->setWorldMatrix(backgroundMat);
	//bannerCarpet->getObj()->setWorldMatrix(backgroundMat);
	//crate->getObj()->setWorldMatrix(backgroundMat);
}

void gameClass::updateGUIPolygon(XMMATRIX mat1, XMMATRIX mat2)
{
	if (player->getNrPolygons() == 0 || player->getNrPolygons() >= 10)
	{
		if (player->getNrPolygons() <= 9)
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
	if (player->getNrPolygons() <= 9)
	{
		slot2->getObj()->setMaterialName("0.png");
	}
	slot1->getObj()->setWorldMatrix(mat1);
	slot2->getObj()->setWorldMatrix(mat2);
	polygonDisp->getObj()->setWorldMatrix(polygonDispMat);
}

void gameClass::updateRingDisplay()
{
	ringDisplay->getObj()->setWorldMatrix(ringDisplayMat);
}

void gameClass::updateXpDisplayMat()
{
	if (tempXP == 0)
	{

		xpDisplay->getObj()->setMaterialName("EXP0.png");

	}
	if (tempXP == 1)
	{

		xpDisplay->getObj()->setMaterialName("EXP1.png");


	}
	if (tempXP == 2)
	{
		xpDisplay->getObj()->setMaterialName("EXP2.png");
	}
	if (tempXP == 3)
	{
		xpDisplay->getObj()->setMaterialName("EXP3.png");
	}
	/*if (tempXP == 4)
	{
	xpDisplay->getObj()->setMaterialName("xp4.png");
	}*/

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
	if (inputDirectOther->isArrowDownPressed() && arrowDownReleased && getCounterOverlay() < 2)
	{
		menyHighlightMat = menyHighlightMat * XMMatrixTranslation(0.0f, -0.24f, 0.0f);
		setCounterOverlay(getCounterOverlay() + 1);
		arrowDownReleased = false;
		if (soundAvailable)
			sound->playSFX(0, 0);
	}
	if (inputDirectOther->isArrowUpPressed() && arrowUpReleased && getCounterOverlay() > 0)
	{
		menyHighlightMat = menyHighlightMat * XMMatrixTranslation(0.0f, 0.24f, 0.0f);
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

	for (int i = 0; i < 3; i++)
	{
		limboPickupHolder[i].getObj()->setWorldMatrix(limboMat);
	}
	limboPickupHolder[1].getObj()->setWorldMatrix(XMMatrixTranslation(1.1f, 0.27f, 0.0f));
	limboPickupHolder[2].getObj()->setWorldMatrix(XMMatrixTranslation(1.35f, -1.65f, 0.0f));

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
			upgradeOverlay->getObj()->setMaterialName("CancelSelectedWeapons.png");
		}
		if (upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() == 1)
		{
			upgradeOverlay->getObj()->setMaterialName("CancelSelectedWeapons.png");
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
				inputDirectOther->readGamepad();
				if (inputDirectOther->isArrowRightPressed() && arrowRightReleased)
				{
					arrowRightReleased = false;
					if ((player->getNrPixelFramgent() - totalPendingCost) >= healthCost && nrHPtoBeUpgraded < 4 && player->getMaxHP() < 4)
					{
						if (soundAvailable)
							sound->playSFX(2, 1);
						totalPendingCost += healthCost;
						/*player->setNrPixelFragments(player->getNrPixelFramgent() - healthCost);*/
						nrHPtoBeUpgraded += 1;
						healthCost = healthCost * 2;
					}
				}

				inputDirectOther->readKeyboard(dt);
				inputDirectOther->readGamepad();
				if (inputDirectOther->isArrowLeftPressed() && nrHPtoBeUpgraded > 0 && arrowLeftReleased)
				{
					if (soundAvailable)
						sound->playSFX(2, 2);
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
				inputDirectOther->readGamepad();
				if (inputDirectOther->isArrowRightPressed() && arrowRightReleased)
				{
					arrowRightReleased = false;
					if ((player->getNrPixelFramgent() - totalPendingCost) >= SpeedCost)
					{
						if (soundAvailable)
							sound->playSFX(2, 1);
						totalPendingCost += SpeedCost;
						//player->setNrPixelFragments(player->getNrPixelFramgent() - SpeedCost);
						nrSpeedToBeUpgraded += 1;
						SpeedCost = SpeedCost * 2;
					}
				}

				inputDirectOther->readKeyboard(dt);
				inputDirectOther->readGamepad();
				if (inputDirectOther->isArrowLeftPressed() && nrSpeedToBeUpgraded > 0 && arrowLeftReleased)
				{
					if (soundAvailable)
						sound->playSFX(2, 2);
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
				inputDirectOther->readGamepad();
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(0))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(0))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(0));
						player->setNrWeaponBought(0, true);

						//Change weapon
						if (soundAvailable)
							sound->playSFX(2, 0);
						player->setWeaponType(1);
					}
				}
			}
			if (upgradeOvlerlayCounterWeapons == 1)
			{
				inputDirectOther->readKeyboard(dt);
				inputDirectOther->readGamepad();
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(1))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(1))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(1));
						player->setNrWeaponBought(1, true);
						//Change weapon
						if (soundAvailable)
							sound->playSFX(2, 0);
						player->setWeaponType(2);
					}
				}
			}
			if (upgradeOvlerlayCounterWeapons == 2)
			{
				inputDirectOther->readKeyboard(dt);
				inputDirectOther->readGamepad();
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(2))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(2))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(2));
						player->setNrWeaponBought(2, true);
						//Change weapon
						if (soundAvailable)
							sound->playSFX(2, 0);
						player->setWeaponType(3);
					}
				}
			}
			if (upgradeOvlerlayCounterWeapons == 3)
			{
				inputDirectOther->readKeyboard(dt);
				inputDirectOther->readGamepad();
				if (inputDirectOther->isEnterPressed() && enterReleased && !player->getNrWeaponBought(3))
				{
					enterReleased = false;
					if (player->getNrPolygons() >= player->getNrWeaponCost(3))
					{
						player->setNrPolysgons(player->getNrPolygons() - player->getNrWeaponCost(3));
						player->setNrWeaponBought(3, true);
						//Change weapon
						if (soundAvailable)
							sound->playSFX(2, 0);
						player->setWeaponType(4);
					}
				}
			}
		}


		//IF CONFIRMED IS PRESSED
		if (upgradeOvlerlayCounterWeapons == 4 && getShopOverlayCounterRow() == 0 || getShopOverlayCounter() == 2 && getShopOverlayCounterRow() == 0)
		{
			inputDirectOther->readKeyboard(dt);
			inputDirectOther->readGamepad();
			if (inputDirectOther->isEnterPressed() && enterReleased)
			{
				if (soundAvailable)
					sound->playSFX(2, 3);
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
				if (soundAvailable)
					sound->playSFX(2, 4);
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
	//if (playr->GetTwjiregjne)
	//{
	//	DEBUG has 1
	//}
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

void gameClass::updateProjectile(double dt, projectileClass* projectile, int type)
{
	//Move projectile
	if (type == 0)
	{
		if (player->getRingType() == 1)
		{
			projectile->getObj()->setMaterialName("MagicRedSpriteSheet.png");
			projectile->setProjectileType(0);
		}
		if (player->getRingType() == 2)
		{
			projectile->getObj()->setMaterialName("MagicBlueSpriteSheet.png");
			projectile->setProjectileType(1);
		}

		projectile->moveProjectile(dt);
		projectile->getTransX(projectileMoveMat);
		projectile->getObj()->setWorldMatrix(XMMatrixScaling(0.6f, 0.5f, 0.0f) * projectileMoveMat);
		projectile->updateAnimation(dt);
		projectile->setLifeTime(dt);
		if (projectile->getLifeTime() > 1.5f)
		{
			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
			//OutputDebugString(L"\nProjectile Destroyed!\n");
		}

		//If collision with platforms -> remove projectile
		if (checkCollisionPlatformBot(platform, projectile->getObj(), projectileMoveMat) ||
			checkCollisionPlatformTop(platform, projectile->getObj(), projectileMoveMat) ||
			checkCollisionPlatformRight(platform, projectile->getObj(), projectileMoveMat) ||
			checkCollisionPlatformLeft(platform, projectile->getObj(), projectileMoveMat))
		{
			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}
	}
	else if (type == 1)
	{
		projectile->moveRrojToCertainDestination(dt);
		projectile->getTransX(enemyFireMat);
		projectile->getObj()->setWorldMatrix(XMMatrixScaling(0.6f, 1.0f, 0.0f) * enemyFireMat);
		projectile->updateAnimation(dt);
		projectile->setLifeTime(dt);
		if (projectile->getLifeTime() > 1.5f)
		{
			projectile->setIsDestroyed(true);
		}
	}
	else if (type == 2)
	{
		
		projectile->moveProjY(dt);
		projectile->getTransX(fireBoss2Mat);
		projectile->getObj()->setWorldMatrix(XMMatrixScaling(2.0f, 2.0f, 0.0f) * fireBoss2Mat);
		projectile->updateAnimation(dt);
		projectile->setLifeTime(dt);
		if (projectile->getLifeTime() > 10.5f)
		{
			OutputDebugString(L"Destroyingh projectile");
			projectile->setIsDestroyed(true);
		}
		if (checkCollisionPlatformBot(platform, projectile->getObj(), fireBoss2Mat) ||
			checkCollisionPlatformTop(platform, projectile->getObj(), fireBoss2Mat) ||
			checkCollisionPlatformRight(platform, projectile->getObj(), fireBoss2Mat) ||
			checkCollisionPlatformLeft(platform, projectile->getObj(), fireBoss2Mat))
		{
			projectile->setIsDestroyed(true);

		}
	}
	else if (type = 3)
	{
		projectile->moveRrojToCertainDestination(dt);
		projectile->getTransX(bossProjectileMat);
		projectile->getObj()->setWorldMatrix(XMMatrixScaling(2.0f, 2.0f, 0.0f) * bossProjectileMat);
		projectile->updateAnimation(dt);
		projectile->setLifeTime(dt);
		if (projectile->getLifeTime() > 1.5f)
		{
			projectile->setIsDestroyed(true);
		}

		if (checkCollisionPlatformBot(platform, projectile->getObj(), bossProjectileMat) ||
			checkCollisionPlatformTop(platform, projectile->getObj(), bossProjectileMat) ||
			checkCollisionPlatformRight(platform, projectile->getObj(), bossProjectileMat) ||
			checkCollisionPlatformLeft(platform, projectile->getObj(), bossProjectileMat))
		{
			projectile->setIsDestroyed(true);
		}
	}
}

void gameClass::updateCollision(double dt)
{
	//canTakeDmg = true;
	for (int i = 0; i < nrOfVisibleEnemies; i++)
	{
		float enemyMove = enemyHolder[i].getMove();

		bool inverse = false;

		enemyHolder[i].getEnemyTranslationMatrix(tempEnemyTranslationMatrix);

		lengthBetween1 = XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove));
		lengthBetween2 = XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)) - XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix));
		lengthBetweenEnemyStartAndEnemyCurrentPos1 = XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(enemyHolder[i].getStartPos(), tempEnemyTranslationMatrix));
		lengthBetweenEnemyStartAndEnemyCurrentPos2 = XMVectorGetX(XMVector3Transform(enemyHolder[i].getStartPos(), tempEnemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix));

		if (enemyHolder[i].getEnemyType() == 0 && enemyHolder[i].getIsActive() && player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponLeft(), playerMove * XMMatrixTranslation(4.2f, 0.0f, 0.0f)), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponLeft(), playerMove), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (enemyHolder[i].hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				enemyHolder[i].setEnemyHP(enemyHolder[i].getEnemyHP() - player->getWeapon()->getDamage());
				//OutputDebugString(L"\nenemy lost hP!\n");
			}
			if (enemyHolder[i].getEnemyHP() <= 0)
			{
				player->setNrPolysgons(player->getNrPolygons() + 1);
				removeObjFromObjHolder(enemyHolder[i].getObj());
				enemyHolder[i].setIsActive(false);
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
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * tempEnemyTranslationMatrix * offset);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(8);
				}
				player->setIfInObjHolder(false);
			}
		}
		else if (enemyHolder[i].getEnemyType() == 0 && enemyHolder[i].getIsActive() && !player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponRight(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponRight(), playerMove * XMMatrixTranslation(-4.2f, 0.0f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (enemyHolder[i].hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				enemyHolder[i].setEnemyHP(enemyHolder[i].getEnemyHP() - player->getWeapon()->getDamage());
				//OutputDebugString(L"\nenemy lost hP!\n");
			}
			if (enemyHolder[i].getEnemyHP() <= 0)
			{
				player->setNrPolysgons(player->getNrPolygons() + 1);
				removeObjFromObjHolder(enemyHolder[i].getObj());
				enemyHolder[i].setIsActive(false);
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
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * tempEnemyTranslationMatrix * offset);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
				}
				player->setIfInObjHolder(false);
			}
		}

		if (enemyHolder[i].getEnemyType() == 1 && enemyHolder[i].getIsActive() && player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponLeft(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponLeft(), playerMove), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (enemyHolder[i].hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				enemyHolder[i].setEnemyHP(enemyHolder[i].getEnemyHP() - player->getWeapon()->getDamage());
				//OutputDebugString(L"\nenemy lost hP!\n");
			}
			if (enemyHolder[i].getEnemyHP() <= 0)
			{
				player->setNrPolysgons(player->getNrPolygons() + 1);
				removeObjFromObjHolder(enemyHolder[i].getObj());
				enemyHolder[i].setIsActive(false);
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
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * tempEnemyTranslationMatrix * offset);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(8);
				}
				player->setIfInObjHolder(false);
			}
		}
		else if (enemyHolder[i].getEnemyType() == 1 && enemyHolder[i].getIsActive() && !player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponRight(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponRight(), playerMove), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (enemyHolder[i].hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				enemyHolder[i].setEnemyHP(enemyHolder[i].getEnemyHP() - player->getWeapon()->getDamage());
				//OutputDebugString(L"\nenemy lost hP!\n");
			}
			if (enemyHolder[i].getEnemyHP() <= 0)
			{
				player->setNrPolysgons(player->getNrPolygons() + 1);
				removeObjFromObjHolder(enemyHolder[i].getObj());
				enemyHolder[i].setIsActive(false);
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
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * tempEnemyTranslationMatrix * offset);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
				}
				player->setIfInObjHolder(false);
			}
		}

		if (player->getRingType() == 1 && enemyHolder[i].getIsActive() && player->getMagicCast() && !projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinLeft(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxLeft(), projectileMoveMat), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (enemyHolder[i].hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				enemyHolder[i].setEnemyHP(enemyHolder[i].getEnemyHP() - 1);
				//	OutputDebugString(L"\nenemy lost hP by Fireball!\n");
			}
			if (enemyHolder[i].getEnemyHP() <= 0)
			{
				player->setNrPolysgons(player->getNrPolygons() + 1);
				removeObjFromObjHolder(enemyHolder[i].getObj());
				enemyHolder[i].setIsActive(false);
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
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * tempEnemyTranslationMatrix * offset);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(8);
				}
				player->setIfInObjHolder(false);
			}
			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}

		else if (player->getRingType() == 1 && enemyHolder[i].getIsActive() && player->getMagicCast() && projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinRight(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxRight(), projectileMoveMat), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (enemyHolder[i].hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				enemyHolder[i].setEnemyHP(enemyHolder[i].getEnemyHP() - 1);
				//OutputDebugString(L"\nenemy lost hP by Fireball!\n");
			}
			if (enemyHolder[i].getEnemyHP() <= 0)
			{
				player->setNrPolysgons(player->getNrPolygons() + 1);
				removeObjFromObjHolder(enemyHolder[i].getObj());
				enemyHolder[i].setIsActive(false);
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
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(scale * tempEnemyTranslationMatrix * offset);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(1);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(8);
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(8);
				}
				player->setIfInObjHolder(false);
			}
			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}

		if (player->getRingType() == 2 && enemyHolder[i].getIsActive() && player->getMagicCast() && !projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinLeft(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxLeft(), projectileMoveMat), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (!enemyHolder[i].getIsFrozen())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				//OutputDebugString(L"\nenemy frozen by Frostbolt!\n");
				enemyHolder[i].setIsFrozen(true);
			}

			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}

		else if (player->getRingType() == 2 && enemyHolder[i].getIsActive() && player->getMagicCast() && projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinRight(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxRight(), projectileMoveMat), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (!enemyHolder[i].getIsFrozen())
			{
				if (soundAvailable)
					sound->playSFX(1, 4);
				//OutputDebugString(L"\nenemy frozen by Frostbolt!\n");
				enemyHolder[i].setIsFrozen(true);
			}

			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}

		//////////////////////
		// ATTACK			//
		//////////////////////

		enemyHolder[i].timeCountdown(dt);

		if (!enemyHolder[i].getIsFrozen())
		{
			if (enemyHolder[i].getIsActive() && lengthBetween2 <= XMVectorGetX(enemyHolder[i].getTriggerCheck()) && lengthBetween1 <= 0.9f && player->getObj()->getCollisionClass()->checkCollisionY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix)))
			{
				//går höger
				if (enemyHolder[i].getEnemyType() == 0 && lengthBetween2 <= XMVectorGetX(enemyHolder[i].getRangeVector()) - 3)
				{
					enemyFire->setIsDestroyed(true);
					enemyHolder[i].setMove(0.0f);
					if (enemyHolder[i].getObj()->getCollisionClass()->checkCollision(XMVector3Transform(enemyHolder[i].getBboxMinWeaponRight(), tempEnemyTranslationMatrix * XMMatrixTranslation(-2.0f, 0.0f, 0.0f)), XMVector3Transform(enemyHolder[i].getBboxMaxWeaponRight(), tempEnemyTranslationMatrix), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) && !player->getInvulnurable())
					{
						if (enemyHolder[i].attackCooldown())
						{
							enemyHolder[i].setAttackAnimation(true);
							enemyHolder[i].getObj()->setStartFrame(34);
							enemyHolder[i].getObj()->setEndFrame(60);
							if (soundAvailable)
								sound->playSFX(1, 17);
							//OutputDebugString(L"Attacking");		
						}
						if (enemyHolder[i].getAttackAnimation() && enemyHolder[i].getObj()->getFrameCount() >= 46 && enemyHolder[i].getObj()->getFrameCount() < 51)
						{
							if (soundAvailable)
								sound->playSFX(1, 5);
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
				//////
				//////RANGE ENEMY STUFF
				//////
				else if (enemyHolder[i].getEnemyType() == 1 && lengthBetween1 <= XMVectorGetX(enemyHolder[i].getRangeVector()) + 5)
				{
					enemyHolder[i].setMove(0.0f);
					enemyFire->setIsDestroyed(false);
				}
				else
				{
					if (!enemyHolder[i].getFacing() && countEnemy <= 0)
					{
						enemyHolder[i].setRoationCheck(true);
						countEnemy = 100;
						enemyHolder[i].setMove(0.0f);
					}
					else if (!enemyHolder[i].getFacing() && countEnemy >= 0)
					{
						countEnemy -= 1;
					}
					else
					{
						enemyHolder[i].setRoationCheck(false);
						enemyHolder[i].setFacing(true);
						enemyHolder[i].updateAttackCooldownTimer(dt);
					}
					enemyHolder[i].setTranslation(enemyHolder[i].getMove());
					enemyHolder[i].setMove(-2.5f * dt);
					if (!enemyHolder[i].getAttackAnimation())
					{
						enemyHolder[i].getObj()->setStartFrame(1);
						enemyHolder[i].getObj()->setEndFrame(33);
					}
				}
			}
			else if (enemyHolder[i].getIsActive() && XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))) > XMVectorGetX(enemyHolder[i].getStartPos()) + 0.05f)
			{
				enemyHolder[i].setMove(1.5f * dt);
				enemyHolder[i].setTranslation(enemyHolder[i].getMove());

				if (!enemyHolder[i].getAttackAnimation() && XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))) > XMVectorGetX(enemyHolder[i].getStartPos()) + 0.1f)
				{
					enemyHolder[i].getObj()->setStartFrame(1);
					enemyHolder[i].getObj()->setEndFrame(33);
					inverse = true;
				}
			}

			if (enemyHolder[i].getIsActive() && lengthBetween1 <= XMVectorGetX(enemyHolder[i].getTriggerCheck()) && lengthBetween1 >= 0.9f && player->getObj()->getCollisionClass()->checkCollisionY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix)))
			{
				if (enemyHolder[i].getEnemyType() == 0 && lengthBetween1 <= XMVectorGetX(enemyHolder[i].getRangeVector()) + 0.5f)
				{
					enemyFire->setIsDestroyed(true);
					enemyHolder[i].setMove(0.0f);
					if (enemyHolder[i].getObj()->getCollisionClass()->checkCollision(XMVector3Transform(enemyHolder[i].getBboxMinWeaponLeft(), tempEnemyTranslationMatrix), XMVector3Transform(enemyHolder[i].getBboxMaxWeaponLeft(), tempEnemyTranslationMatrix * XMMatrixTranslation(2.0f, 0.0f, 0.0f)), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) && !player->getInvulnurable())
					{
						if (enemyHolder[i].attackCooldown())
						{
							enemyHolder[i].setAttackAnimation(true);
							enemyHolder[i].getObj()->setStartFrame(34);
							enemyHolder[i].getObj()->setEndFrame(60);
							if (soundAvailable)
								sound->playSFX(1, 17);
							//OutputDebugString(L"Attacking");				
						}

						if (enemyHolder[i].getAttackAnimation() && enemyHolder[i].getObj()->getFrameCount() >= 46 && enemyHolder[i].getObj()->getFrameCount() < 51)
						{
							if (soundAvailable)
								sound->playSFX(1, 5);
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
				//////
				//////RANGE ENEMY STUFF
				//////
				else if (enemyHolder[i].getEnemyType() == 1 && lengthBetween1 <= XMVectorGetX(enemyHolder[i].getRangeVector()) + 5)
				{
					enemyHolder[i].setMove(0.0f);
					enemyFire->setIsDestroyed(false);
				}
				else
				{
					//går åt vänster
					if (enemyHolder[i].getFacing() && countEnemy <= 0)
					{
						enemyHolder[i].setRoationCheck(true);
						countEnemy = 100;
						enemyHolder[i].setMove(0.0f);
					}
					else if (enemyHolder[i].getFacing() && countEnemy >= 0)
					{
						countEnemy -= 1;
					}
					else
					{
						enemyHolder[i].setRoationCheck(false);
						enemyHolder[i].setFacing(false);
						enemyHolder[i].updateAttackCooldownTimer(dt);
					}

					enemyHolder[i].setMove(2.5f * dt);
					enemyHolder[i].setTranslation(enemyHolder[i].getMove());
					if (!enemyHolder[i].getAttackAnimation())
					{
						enemyHolder[i].getObj()->setStartFrame(1);
						enemyHolder[i].getObj()->setEndFrame(33);
					}
				}
			}
			else if (enemyHolder[i].getIsActive() && XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))) < XMVectorGetX(enemyHolder[i].getStartPos()))
			{
				enemyHolder[i].setMove(-1.5f * dt);
				enemyHolder[i].setTranslation(enemyHolder[i].getMove());
				//OutputDebugString(L"MOVING TO SPAWN");

				if (!enemyHolder[i].getAttackAnimation() && XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getPosition(), tempEnemyTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))) < XMVectorGetX(enemyHolder[i].getStartPos()) - 0.1f)
				{
					enemyHolder[i].getObj()->setStartFrame(1);
					enemyHolder[i].getObj()->setEndFrame(33);
					inverse = true;
				}
			}




			if (enemyHolder[i].getEnemyType() == 1 && lengthBetween1 <= XMVectorGetX(enemyHolder[i].getRangeVector()) + 5 && player->getObj()->getCollisionClass()->checkCollisionY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix), XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix)))
			{
				//projectile enemy stuff
				if (!enemyFire->getIsDestroyed() && !enemyFire->getCheckIfObjHolder())
				{
					//OutputDebugString(L"\nCreating Fireball enemy\n");
					if (soundAvailable)
						sound->playSFX(1, 2);
					addObjectToObjHolder(enemyFire->getObj());
					enemyFire->setCheckIfObjHolder(true);
					player->setIfInObjHolder(false);
					enemyHolder[i].getEnemyTranslationMatrix(tempEnemyTranslationMatrix);
					enemyHolder[i].getTranslationMatStart(tempEnemyStartingPositionMatrix);
					enemyHolder[i].getTranslationMat(tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame);
					//Set start pos and direction
					float useThisX = XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2);
					float useThisY = (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2));
					XMVECTOR useThis = { useThisX, useThisY };

					float useThisX2 = XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix)) + ((XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix)) - XMVectorGetX(XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix))) / 2);
					float useThisY2 = (XMVectorGetY(XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix)) + ((XMVectorGetY(XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMax(), tempEnemyTranslationMatrix)) - XMVectorGetY(XMVector3Transform(enemyHolder[i].getObj()->getBoundingBoxMin(), tempEnemyTranslationMatrix))) / 2));
					XMVECTOR useThis2 = { useThisX2, useThisY2 };

					enemyFire->setDestinationStart(useThis2);
					enemyFire->setDestinationPoint(useThis);
					enemyFire->setTranslationMatStart(tempMatrixThatMakesOurSkeletonMove_HoldsOurXValueFrame * tempEnemyStartingPositionMatrix);

					if (lengthBetween2 <= XMVectorGetX(enemyHolder[i].getTriggerCheck()) && lengthBetween1 <= 1.5f)
					{
						enemyFire->setGoesRight(true);
					}
					if (lengthBetween1 <= XMVectorGetX(enemyHolder[i].getTriggerCheck()) && lengthBetween1 >= 1.5f)
					{
						enemyFire->setGoesRight(false);
					}
				}

			}

			enemyHolder[i].getObj()->playAnimation(dt, inverse);
		}
		if (!enemyFire->getIsDestroyed() && enemyFire->getCheckIfObjHolder())
		{
			updateProjectile(dt * 0.1, enemyFire, 1);
		}
		if (enemyFire->getIsDestroyed() && enemyFire->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(enemyFire->getObj());
			enemyFire->resetProjectile();
		}

		enemyHolder[i].updateAttackCooldownTimer(dt);
	}

	if (!enemyFire->getIsDestroyed() && enemyFire->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
	{
		enemyFire->getObj()->getWorldMatrix(enemyFireMat);
		if (!enemyFire->getGoesRight() && player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(enemyFire->getBoundingBoxMinLeft(), enemyFireMat), XMVector3Transform(enemyFire->getBoundingBoxMaxLeft(), enemyFireMat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) && !player->getInvulnurable())
		{
			//OutputDebugString(L"\nFire damage!\n");
			if (soundAvailable)
				sound->playSFX(1, 5);
			player->setPlayerHP(player->getPlayerHP() - 1);
			player->setPlayerHurt(true);
			player->setPlayerHurtFromLeft(true);
			//player->setPlayerHurtFromRight(true);
			if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
			{
				heartHolder[player->getPlayerHP()].setIsDestroy(true);
				removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
				heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
			}
			enemyFire->resetProjectile();
		}
		if (enemyFire->getGoesRight() && player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(enemyFire->getBoundingBoxMinRight(), enemyFireMat), XMVector3Transform(enemyFire->getBoundingBoxMaxRight(), enemyFireMat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) && !player->getInvulnurable())
		{
			//OutputDebugString(L"\nFire damage!\n");
			if (soundAvailable)
				sound->playSFX(1, 5);
			player->setPlayerHP(player->getPlayerHP() - 1);
			player->setPlayerHurt(true);
			player->setPlayerHurtFromLeft(true);
			//player->setPlayerHurtFromRight(true);
			if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
			{
				heartHolder[player->getPlayerHP()].setIsDestroy(true);
				removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
				heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
			}
			enemyFire->resetProjectile();
		}
	}

	////////////////////////////////
	//		END OF ENEMY CALC	  //
	////////////////////////////////

	for (int i = 0; i < ladders->getObj()->getMeshCount(); i++)
	{
		if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(ladders->getObj()->getBoundingBoxMin(i), XMMatrixIdentity()), XMVector3Transform(ladders->getObj()->getBoundingBoxMax(i), XMMatrixIdentity()), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
		{
			isTextDestroy2 = false;
			if (!isTextInPickupHolder2 && !isTextDestroy2)
			{
				//OutputDebugString(L"\nText created22!\n");
				/*pickupClass text2;
				text2.clone(*limboTextPlanePressE);
				nrOfVisiblePickups++;
				addPickupToPickupHolder(text2, nrOfVisiblePickups);
				pickupHolder[nrOfVisiblePickups - 1].setFrameCount(4);
				pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(4);
				pickupHolder[nrOfVisiblePickups - 1].setAnimationCount(1);
				pickupHolder[nrOfVisiblePickups - 1].getObj()->setAnimationCount(1);
				pickupHolder[nrOfVisiblePickups - 1].setPickupType(8);
				pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(XMMatrixIdentity());
				text2.shutdown();*/
				isTextDestroy2 = false;
				isTextInPickupHolder2 = true;
			}
			i = ladders->getObj()->getMeshCount();
		}
		else
		{
			isTextDestroy2 = true;
		}
	}
	if (isTextInPickupHolder2 && isTextDestroy2)
	{
		for (int j = 0; j < nrOfVisiblePickups; j++)
		{
			if (pickupHolder[j].getPickupType() == 8)
			{
				isTextInPickupHolder2 = false;
				//OutputDebugString(L"\nRemoveing text22!\n");
				/*pickupHolder[j].setIsDestroy(true);*/
				isTextDestroy2 = true;
			}
		}
	}
	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		if (pickupHolder[i].getPickupType() == 8)
		{
			pickupHolder[i].setTranslationMatStart(XMMatrixScaling(0.7, 0.7, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) - 1.5f + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) - 3.9f, 0.0f));
		}
	}

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		XMMATRIX yOffset;
		pickupHolder[i].getTranslationMatStart(yOffset);
		if (!pickupHolder[i].getIsDestry() && player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(pickupHolder[i].getObj()->getBoundingBoxMin(), yOffset), XMVector3Transform(pickupHolder[i].getObj()->getBoundingBoxMax(), yOffset)))
		{
			if (pickupHolder[i].getPickupType() == 3)
			{
				isTextDestroy = false;
				if (!isTextInPickupHolder && !isTextDestroy)
				{
					//OutputDebugString(L"\nText created!\n");
					pickupClass text;
					text.clone(*limboTextPlanePressE);
					nrOfVisiblePickups++;
					addPickupToPickupHolder(text, nrOfVisiblePickups);
					pickupHolder[nrOfVisiblePickups - 1].setIsDestroy(false);
					pickupHolder[nrOfVisiblePickups - 1].setFrameCount(4);
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(4);
					pickupHolder[nrOfVisiblePickups - 1].setAnimationCount(1);
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setAnimationCount(1);
					pickupHolder[nrOfVisiblePickups - 1].setPickupType(5);
					pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(XMMatrixTranslation(-1.9, -4.9f, 0.0) * XMMatrixScaling(2.6, 1.5, 0.0) * yOffset);
					text.shutdown();
					isTextInPickupHolder = true;
				}

				if (pickupHolder[i].getPickupType() == 3 && inputDirectOther->isEnterPressed() && enterReleased) //type 3 means it's a RING
				{
					for (int j = 0; j < nrOfVisiblePickups; j++)
					{
						if (pickupHolder[j].getPickupType() == 5)
						{
							isTextInPickupHolder = false;
							//OutputDebugString(L"\nRemoveing text 2!\n");
							pickupHolder[j].setIsDestroy(true);
							isTextDestroy = true;
						}
					}
					enterReleased = true;
				}
				i = nrOfVisiblePickups;
			}
		}
		else
		{
			//OutputDebugString(L"\nNO COLLISION!\n");
			isTextDestroy = true;
		}
	}
	if (isTextInPickupHolder && isTextDestroy)
	{
		for (int j = 0; j < nrOfVisiblePickups; j++)
		{
			if (pickupHolder[j].getPickupType() == 5)
			{
				isTextInPickupHolder = false;
				//OutputDebugString(L"\nRemoveing text!\n");
				pickupHolder[j].setIsDestroy(true);
				isTextDestroy = true;
			}
		}
	}

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		//IF WE PICKUP A RING
		XMMATRIX yOffset;
		pickupHolder[i].getTranslationMatStart(yOffset);
		if (!pickupHolder[i].getIsDestry() && player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(pickupHolder[i].getObj()->getBoundingBoxMin(), yOffset), XMVector3Transform(pickupHolder[i].getObj()->getBoundingBoxMax(), yOffset)))
		{
			if (pickupHolder[i].getPickupType() == 1)
			{
				if (soundAvailable)
					sound->playSFX(1, 8);
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
						ringDisplay->getObj()->setMaterialName("RingGreen3.png");
					}
					if (pickupHolder[i].getRingType() == 1)
					{
						ringDisplay->getObj()->setMaterialName("RingRed3.png");
					}
					if (pickupHolder[i].getRingType() == 2)
					{
						ringDisplay->getObj()->setMaterialName("RingBlue3.png");
					}
					if (pickupHolder[i].getRingType() == 3)
					{
						ringDisplay->getObj()->setMaterialName("RingWhite3.png");
					}
				}
				if (soundAvailable)
					sound->playSFX(1, 7);
				//OutputDebugString(L"\nRing was picked up so cool effect is spawning!\n");
				pickupClass effect;
				effect.clone(*ring);
				nrOfVisiblePickups++;
				addPickupToPickupHolder(effect, nrOfVisiblePickups);
				if (player->getRingType() == 0)
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setMaterialName("RingGreenSpriteSheet.png");
				if (player->getRingType() == 1)
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setMaterialName("RingRedSpriteSheet.png");
				if (player->getRingType() == 2)
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setMaterialName("RingBlueSpriteSheet.png");
				if (player->getRingType() == 3)
					pickupHolder[nrOfVisiblePickups - 1].getObj()->setMaterialName("RingWhiteSpriteSheet.png");
				pickupHolder[nrOfVisiblePickups - 1].setFrameCount(9);
				pickupHolder[nrOfVisiblePickups - 1].getObj()->setFrameCount(9);
				pickupHolder[nrOfVisiblePickups - 1].setAnimationCount(1);
				pickupHolder[nrOfVisiblePickups - 1].getObj()->setAnimationCount(1);
				pickupHolder[nrOfVisiblePickups - 1].setPickupType(6);
				pickupHolder[nrOfVisiblePickups - 1].setTranslationMatStart(XMMatrixScaling(0.4, 0.9, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) + 1.0f, 0.0f));
				effect.shutdown();

				pickupHolder[i].setIsDestroy(true);
				enterReleased = false;
			}
		}
	}

	for (int i = 0; i < nrOfVisiblePickups; i++)
	{
		if (pickupHolder[i].getPickupType() == 6)
		{
			pickupHolder[i].setTranslationMatStart(XMMatrixScaling(0.4, 0.9, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) + 1.0f, 0.0f));
			if (pickupHolder[i].getCurrentFrame() == 9)
			{
				pickupHolder[i].setIsDestroy(true);
			}
		}
	}

	if (!portalPlane->getIsDestry())
	{
		XMMATRIX yOffset;
		portalPlane->getTranslationMatStart(yOffset);

		if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove), XMVector3Transform(portalPlane->getObj()->getBoundingBoxMin(), yOffset), XMVector3Transform(portalPlane->getObj()->getBoundingBoxMax(), yOffset)))
		{
			//OutputDebugString(L"\nPORTAL!!!\n");
			if (soundAvailable)
				sound->playSFX(1, 11);
			gameStateLevel = false;
			gameStateLimbo = false;
			gameStateWin = true;
			gameStateMeny = false;
			if (soundAvailable)
				sound->playAmbient(3);
		}
	}
}

void gameClass::updatePortal(double dt)
{
	XMMATRIX yOffset;
	portalPlane->getTranslationMatStart(yOffset);
	portalPlane->getObj()->setWorldMatrix(yOffset);
	portalPlane->updateAnimation(dt);
}

void gameClass::updateBoss(double dt)
{
	//////////////////////
	//					//
	//	FOR DISPLAY	   ///
	//					//
	//////////////////////
	if (ifBossIsSpawning == false)
	{
		boss->getEnemyTranslationMatrix(tempBossTranslationMatrix);
		if (!boss->getIsFrozen())
		{
			boss->updateFalling(dt);

			if (!boss->getAttackAnimation())
			{
				boss->getObj()->setStartFrame(1);
				boss->getObj()->setEndFrame(39);
			}
			if (boss->getAttackAnimation());
			{
				if (boss->getObj()->getFrameCount() >= boss->getObj()->getEndFrame() - 1)
				{
					boss->setAttackAnimation(false);
				}
				
			}
			/*enemyHolder[i].getObj()->setWorldMatrix(tempEnemyStartingPositionMatrix);*/
			//jag vet att detta är förvirrande men denna tranlationmat func hämtar ut ett värde i x som gör att vår sak rör på oss
			boss->getTranslationMat(tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame);
			boss->getFallingMat(tempBossIfAirThenFallMatrix);
			boss->getMasterMovementEnemy(tempMasterMovementBossMat);
			//denna håller i alla värden så att vi inte flippar bounding boxen också
			boss->getEnemyTranslationMatrix(tempBossTranslationMatrix);
			boss->getTranslationMatStart(tempBossStartingPositionMatrix);
			if (!boss->getRoationCheck())
			{
				tempMasterMovementBossMat = tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
				tempBossTranslationMatrix = tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
			}
			else
			{
				tempMasterMovementBossMat = XMMatrixRotationY(-3.1514f) * tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
				tempBossTranslationMatrix = tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
			}
			boss->getObj()->setWorldMatrix(tempMasterMovementBossMat);
			///////////////
			boss->checkCollisionsY(checkCollisionPlatformTop(platform, boss->getObj(), tempBossTranslationMatrix), checkCollisionPlatformBot(platform, boss->getObj(), tempBossTranslationMatrix));
			boss->checkCollisionsX(checkCollisionPlatformLeft(platform, boss->getObj(), tempBossTranslationMatrix), checkCollisionPlatformRight(platform, boss->getObj(), tempBossTranslationMatrix));
			//enemyHolder[i].getObj()->setWorldMatrix(tempEnemyStartingPositionMatrix);
			boss->getTranslationMat(tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame);
			boss->getFallingMat(tempBossIfAirThenFallMatrix);
			if (!boss->getRoationCheck())
			{
				tempMasterMovementBossMat = tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
				tempBossTranslationMatrix = tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
			}
			else
			{
				tempMasterMovementBossMat = XMMatrixRotationY(-3.1514f) * tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
				tempBossTranslationMatrix = tempBossIfAirThenFallMatrix * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix;
			}
			boss->setMasterMovementEnemy(tempMasterMovementBossMat);
			boss->setEnemyTranslationMatrix(tempBossTranslationMatrix);
			boss->getObj()->setWorldMatrix(tempMasterMovementBossMat);
		}
		else if (boss->getIsFrozen())
		{
			boss->updateFrozenTimer(dt);
		}
		boss->setMasterMovementEnemy(tempMasterMovementBossMat);
		boss->setEnemyTranslationMatrix(tempBossTranslationMatrix);
		boss->getObj()->setWorldMatrix(tempMasterMovementBossMat);
	}
	else if (ifBossIsSpawning == true)
	{
		boss->getObj()->setWorldMatrix(tempMasterMovementBossMat * XMMatrixTranslation(0.0, 10.0, 0.0));
	}

	////////////////////////////////////////
	//									  //
	//		  CALC BOSS BEHAVIOUR	      //
	//									  //
	////////////////////////////////////////

	float enemyMove = boss->getMove();

	boss->getEnemyTranslationMatrix(tempBossTranslationMatrix);
	lengthBetween1 = XMVectorGetX(XMVector3Transform(boss->getObj()->getPosition(), tempBossTranslationMatrix)) - XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove));
	lengthBetween2 = XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)) - XMVectorGetX(XMVector3Transform(boss->getObj()->getPosition(), tempBossTranslationMatrix));



	//	IF BOSS HURTS PLAYER

	//////////////////////////
	//						//
	//	DETERMIN BOSS STAT  //
	//	
	//////////////////////////

	if (boss->getEnemyHP() >= 76)
	{
		ifBossIsSpawning = false;
		canSpawnEnemys = true;
		canSpawnEnemys2 = true;
		nrOfEnemysBossHasSpawned = 0;
	}
	else if (boss->getEnemyHP() < 30 && canSpawnEnemys2 == true)
	{
		ifBossIsSpawning = true;
	}
	else if (boss->getEnemyHP() < 76 && canSpawnEnemys == true)
	{
		ifBossIsSpawning = true;
	}
	else if (boss->getEnemyHP() < 30 && canSpawnEnemys2 == false)
	{
		ifBossIsSpawning = false;
	}
	else if (boss->getEnemyHP() < 76 && canSpawnEnemys == false)
	{
		ifBossIsSpawning = false;
	}


	//////////////////////
	//					//
	//	PHASE BATTLING	//
	//					//
	//////////////////////
	if (ifBossIsSpawning == false)
	{
		//OutputDebugString(L"NOT SPAWNING");
		float lengthBetween3 = fabs(XMVectorGetX(XMVector3Transform(boss->getObj()->getPosition(), tempBossTranslationMatrix)) - XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), playerMove)));

		//	IF PLAYER HURTS BOSS

		/////////////////////////////////
		//							//
		//   IF TAKE WEAPON DMG		//
		//							//
		//////////////////////////////

		if (ifBossIsSpawning == false && bossIsInCombat == true && player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponLeft(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponLeft(), playerMove), XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (boss->hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 16);
				boss->setEnemyHP(boss->getEnemyHP() - player->getWeapon()->getDamage());
				//OutputDebugString(L"\nenemy lost hP!\n");
			}
			if (boss->getEnemyHP() <= 0)
			{
				if (soundAvailable)
					sound->playSFX(1, 15);
				removeObjFromObjHolder(boss->getObj());
				boss->setIsActive(false);
				player->setIfInObjHolder(false);
				bossIsInCombat = false;
				portalPlane->setIsDestroy(false);
				if (!bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder())
				{
					bossFire->setIsDestroyed(true);
				}
			}
		}
		else if (ifBossIsSpawning == false && bossIsInCombat == true && !player->getFlipped() && player->getIfAttack() && player->getWeapon()->getCollisionClass()->checkCollision(XMVector3Transform(player->getWeapon()->getBboxMinWeaponRight(), playerMove), XMVector3Transform(player->getWeapon()->getBboxMaxWeaponRight(), playerMove), XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (boss->hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 16);
				boss->setEnemyHP(boss->getEnemyHP() - player->getWeapon()->getDamage());
				//OutputDebugString(L"\nenemy lost hP!\n");
			}
			if (boss->getEnemyHP() <= 0)
			{
				if (soundAvailable)
					sound->playSFX(1, 15);
				removeObjFromObjHolder(boss->getObj());
				boss->setIsActive(false);
				player->setIfInObjHolder(false);
				bossIsInCombat = false;
				portalPlane->setIsDestroy(false);
				if (!bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder())
				{
					bossFire->setIsDestroyed(true);
				}
			}
		}

		/////////////////////////////////
		//							//
		//   IF TAKE FIRE DMG		//
		//							//
		//////////////////////////////
		if (ifBossIsSpawning == false && player->getRingType() == 1 && bossIsInCombat == true && player->getMagicCast() && !projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinLeft(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxLeft(), projectileMoveMat), XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (boss->hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 16);
				boss->setEnemyHP(boss->getEnemyHP() - 1);
				//OutputDebugString(L"\nenemy lost hP by Fireball!\n");
			}
			if (boss->getEnemyHP() <= 0)
			{
				if (soundAvailable)
					sound->playSFX(1, 15);
				removeObjFromObjHolder(boss->getObj());
				boss->setIsActive(false);
				bossIsInCombat = false;
				player->setIfInObjHolder(false);
				portalPlane->setIsDestroy(false);
				if (!bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder())
				{
					bossFire->setIsDestroyed(true);
				}
			}
			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}
		else if (ifBossIsSpawning == false && player->getRingType() == 1 && bossIsInCombat == true && player->getMagicCast() && projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinRight(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxRight(), projectileMoveMat), XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (boss->hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 16);
				boss->setEnemyHP(boss->getEnemyHP() - 1);
				//OutputDebugString(L"\nenemy lost hP by Fireball!\n");
			}
			if (boss->getEnemyHP() <= 0)
			{
				if (soundAvailable)
					sound->playSFX(1, 15);
				removeObjFromObjHolder(boss->getObj());
				boss->setIsActive(false);
				player->setIfInObjHolder(false);
				bossIsInCombat = false;
				portalPlane->setIsDestroy(false);
				if (!bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder())
				{
					bossFire->setIsDestroyed(true);
				}
			}
			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}

		/////////////////////////////////
		//							//
		//   IF TAKE ICE "DMG"		//
		//							//
		//////////////////////////////
		if (ifBossIsSpawning == false && player->getRingType() == 2 && bossIsInCombat == true && player->getMagicCast() && !projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinLeft(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxLeft(), projectileMoveMat), XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f)), XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -1.0f, 0.0f))))
		{
			if (boss->hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 16);
				//OutputDebugString(L"\nenemy frozen by Frostbolt!\n");
				boss->setIsFrozen(true);
			}

			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}
		else if (ifBossIsSpawning == false && player->getRingType() == 2 && bossIsInCombat == true && player->getMagicCast() && projectile->getGoesRight() && !projectile->getIsDestroyed() && projectile->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(projectile->getBoundingBoxMinRight(), projectileMoveMat), XMVector3Transform(projectile->getBoundingBoxMaxRight(), projectileMoveMat), XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f)), XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix * XMMatrixTranslation(0.0f, -0.5f, 0.0f))))
		{
			if (boss->hurtState())
			{
				if (soundAvailable)
					sound->playSFX(1, 16);
				//OutputDebugString(L"\nenemy frozen by Frostbolt!\n");
				boss->setIsFrozen(true);
			}

			removeObjFromObjHolder(projectile->getObj());
			projectile->resetProjectile();
			player->setMagicCast(false);
		}

		/////////////////////////////
		//							/
		//   IF SHOOTING FIRE	   //
		//                         //
		/////////////////////////////
		nrOfEnemysBossHasSpawned = 0;
		boss->timeCountdown(dt);
		if (!boss->getIsFrozen())
		{
			int randValue = rand() % 6;
			if (randValue <= 4 && bossIsInCombat == true)
			{
				boss->setMove(0.0f);
				bossFire->setIsDestroyed(false);
			}
			else if (randValue > 4 && bossIsInCombat == true && bossTimerForRainingFire <= 0)
			{
				if (soundAvailable)
					sound->playSFX(1, 10);

				OutputDebugString(L"\nrand > 4\n");
				bossTimerForRainingFire = 10;
				bossFire->setIsDestroyed(true);
				boss->getObj()->setStartFrame(41);
				boss->getObj()->setEndFrame(62);
				boss->setAttackAnimation(true);

				bossFire2->setIsDestroyed(false);
				bossFire3->setIsDestroyed(false);
				bossFire4->setIsDestroyed(false);
				bossFire5->setIsDestroyed(false);
				bossFire6->setIsDestroyed(false);
			}
			if (bossTimerForRainingFire > 0.0f)
			{
				updateBossTimerForRainingFire(dt);
			}
		}
		
		//projectile enemy stuff
		if (!bossFire->getIsDestroyed() && !bossFire->getCheckIfObjHolder())
		{
			addObjectToObjHolder(bossFire->getObj());
			bossFire->setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);
			boss->getEnemyTranslationMatrix(tempBossTranslationMatrix);
			boss->getTranslationMatStart(tempBossStartingPositionMatrix);
			boss->getTranslationMat(tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame);
			//Set start pos and direction
			float useThisX = XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2);
			float useThisY = (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2));
			XMVECTOR useThis = { useThisX, useThisY };

			float useThisX2 = XMVectorGetX(XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix)) + ((XMVectorGetX(XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix)) - XMVectorGetX(XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix))) / 2);
			float useThisY2 = (XMVectorGetY(XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix)) + ((XMVectorGetY(XMVector3Transform(boss->getObj()->getBoundingBoxMax(), tempBossTranslationMatrix)) - XMVectorGetY(XMVector3Transform(boss->getObj()->getBoundingBoxMin(), tempBossTranslationMatrix))) / 2));

			XMVECTOR useThis2 = { useThisX2, useThisY2 };

			bossFire->setDestinationStart(useThis2);
			bossFire->setDestinationPoint(useThis);
			bossFire->setTranslationMatStart(XMMatrixRotationZ(3.14159265) * tempMatrixThatMakesOurBossMove_HoldsOurXValueFrame * tempBossStartingPositionMatrix);
		}
		if (!bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder())
		{
			updateProjectile(dt, bossFire, 3);
		}
		if (bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(bossFire->getObj());
			bossFire->resetProjectile();
		}

		/////////////////////////////////////////////////// FIRE 1
		//projectile enemy stuff
		if (!bossFire2->getIsDestroyed() && !bossFire2->getCheckIfObjHolder())
		{
			OutputDebugString(L"spawn 2 projectile");
			addObjectToObjHolder(bossFire2->getObj());
			bossFire2->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-50.0f, 102.0f, 0.0f));
			bossFire2->setCheckIfObjHolder(true);
			bossFire2->setIsDestroyed(false);
			player->setIfInObjHolder(false);
		}

		if (!bossFire2->getIsDestroyed() && bossFire2->getCheckIfObjHolder())
		{
			updateProjectile(dt, bossFire2, 2);
		}
		if (bossFire2->getIsDestroyed() && bossFire2->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(bossFire2->getObj());
			bossFire2->resetProjectile();
		}

		//projectile enemy stuff
		if (!bossFire3->getIsDestroyed() && !bossFire3->getCheckIfObjHolder())
		{
			OutputDebugString(L"spawning 3 projectile");
			addObjectToObjHolder(bossFire3->getObj());
			bossFire3->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-40.0f, 102.0f, 0.0f));
			bossFire3->setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);
		}

		if (!bossFire3->getIsDestroyed() && bossFire3->getCheckIfObjHolder())
		{
			updateProjectile(dt, bossFire3, 2);
		}
		if (bossFire3->getIsDestroyed() && bossFire3->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(bossFire3->getObj());
			bossFire3->resetProjectile();
		}

		//projectile enemy stuff
		if (!bossFire4->getIsDestroyed() && !bossFire4->getCheckIfObjHolder())
		{
			OutputDebugString(L"spawning 4 projectile");
			addObjectToObjHolder(bossFire4->getObj());
			bossFire4->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-30.0f, 102.0f, 0.0f));
			bossFire4->setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);

		}

		if (!bossFire4->getIsDestroyed() && bossFire4->getCheckIfObjHolder())
		{
			updateProjectile(dt, bossFire4, 2);
		}
		if (bossFire4->getIsDestroyed() && bossFire4->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(bossFire4->getObj());
			bossFire4->resetProjectile();
		}

		//projectile enemy stuff
		if (!bossFire5->getIsDestroyed() && !bossFire5->getCheckIfObjHolder())
		{
			OutputDebugString(L"spawning 5 projectile");
			addObjectToObjHolder(bossFire5->getObj());
			bossFire5->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-20.0f, 102.0f, 0.0f));
			bossFire5->setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);
		}

		if (!bossFire5->getIsDestroyed() && bossFire5->getCheckIfObjHolder())
		{
			updateProjectile(dt, bossFire5, 2);
		}
		if (bossFire5->getIsDestroyed() && bossFire5->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(bossFire5->getObj());
			bossFire5->resetProjectile();
		}

		//projectile enemy stuff
		if (!bossFire6->getIsDestroyed() && !bossFire6->getCheckIfObjHolder())
		{
			addObjectToObjHolder(bossFire6->getObj());
			bossFire6->setTranslationMatStart(XMMatrixRotationZ(-1.57079633) * XMMatrixTranslation(-10.0f, 102.0f, 0.0f));
			bossFire6->setCheckIfObjHolder(true);
			player->setIfInObjHolder(false);
		}

		if (!bossFire6->getIsDestroyed() && bossFire6->getCheckIfObjHolder())
		{
			updateProjectile(dt, bossFire6, 2);
		}
		if (bossFire6->getIsDestroyed() && bossFire6->getCheckIfObjHolder())
		{
			removeObjFromObjHolder(bossFire6->getObj());
			bossFire6->resetProjectile();
		}

		if (!bossFire->getIsDestroyed() && bossFire->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
		{
			bossFire->getObj()->getWorldMatrix(bossProjectileMat);
			if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire->getBoundingBoxMinLeft(), bossProjectileMat), XMVector3Transform(bossFire->getBoundingBoxMaxLeft(), bossProjectileMat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			{
				//OutputDebugString(L"\nFire damage!\n");
				player->setPlayerHP(player->getPlayerHP() - 1);
				player->setPlayerHurt(true);
				player->setPlayerHurtFromLeft(true);
				//player->setPlayerHurtFromRight(true);
				if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
				{
					heartHolder[player->getPlayerHP()].setIsDestroy(true);
					removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
					heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
				}
				bossFire->resetProjectile();
			}
			//if (bossFire->getGoesRight() && player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire->getBoundingBoxMinRight(), bossProjectileMat), XMVector3Transform(bossFire->getBoundingBoxMaxRight(), bossProjectileMat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			//{
			//	OutputDebugString(L"\nFire damage!\n");
			//	player->setPlayerHP(player->getPlayerHP() - 1);
			//	player->setPlayerHurt(true);
			//	player->setPlayerHurtFromLeft(true);
			//	//player->setPlayerHurtFromRight(true);
			//	if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
			//	{
			//		heartHolder[player->getPlayerHP()].setIsDestroy(true);
			//		removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
			//		heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
			//	}
			//	bossFire->resetProjectile();
			//}
		}

		////////////////////
		if (!bossFire2->getIsDestroyed() && bossFire2->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
		{
			bossFire2->getObj()->getWorldMatrix(fireBoss2Mat);
			if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire2->getBoundingBoxMinLeft(), fireBoss2Mat), XMVector3Transform(bossFire2->getBoundingBoxMaxLeft(), fireBoss2Mat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			{
				//OutputDebugString(L"\nFire damage!\n");
				player->setPlayerHP(player->getPlayerHP() - 1);
				player->setPlayerHurt(true);
				player->setPlayerHurtFromLeft(true);
				//player->setPlayerHurtFromRight(true);
				if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
				{
					heartHolder[player->getPlayerHP()].setIsDestroy(true);
					removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
					heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
				}
				//bossFire2->resetProjectile();
			}
		}
		if (!bossFire3->getIsDestroyed() && bossFire3->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
		{
			bossFire3->getObj()->getWorldMatrix(fireBoss2Mat);
			if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire3->getBoundingBoxMinLeft(), fireBoss2Mat), XMVector3Transform(bossFire3->getBoundingBoxMaxLeft(), fireBoss2Mat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			{
				//OutputDebugString(L"\nFire damage!\n");
				player->setPlayerHP(player->getPlayerHP() - 1);
				player->setPlayerHurt(true);
				player->setPlayerHurtFromLeft(true);
				//player->setPlayerHurtFromRight(true);
				if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
				{
					heartHolder[player->getPlayerHP()].setIsDestroy(true);
					removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
					heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
				}
				//bossFire2->resetProjectile();
			}
		}
		if (!bossFire4->getIsDestroyed() && bossFire4->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
		{
			bossFire4->getObj()->getWorldMatrix(fireBoss2Mat);
			if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire4->getBoundingBoxMinLeft(), fireBoss2Mat), XMVector3Transform(bossFire4->getBoundingBoxMaxLeft(), fireBoss2Mat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			{
				//OutputDebugString(L"\nFire damage!\n");
				player->setPlayerHP(player->getPlayerHP() - 1);
				player->setPlayerHurt(true);
				player->setPlayerHurtFromLeft(true);
				//player->setPlayerHurtFromRight(true);
				if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
				{
					heartHolder[player->getPlayerHP()].setIsDestroy(true);
					removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
					heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
				}
				//bossFire2->resetProjectile();
			}
		}
		if (!bossFire5->getIsDestroyed() && bossFire5->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
		{
			bossFire5->getObj()->getWorldMatrix(fireBoss2Mat);
			if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire5->getBoundingBoxMinLeft(), fireBoss2Mat), XMVector3Transform(bossFire5->getBoundingBoxMaxLeft(), fireBoss2Mat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			{
				//OutputDebugString(L"\nFire damage!\n");
				player->setPlayerHP(player->getPlayerHP() - 1);
				player->setPlayerHurt(true);
				player->setPlayerHurtFromLeft(true);
				//player->setPlayerHurtFromRight(true);
				if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
				{
					heartHolder[player->getPlayerHP()].setIsDestroy(true);
					removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
					heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
				}
				//bossFire2->resetProjectile();
			}
		}
		if (!bossFire6->getIsDestroyed() && bossFire6->getCheckIfObjHolder() && player->getCurrentAnimation() != 7)
		{
			bossFire6->getObj()->getWorldMatrix(fireBoss2Mat);
			if (player->getObj()->getCollisionClass()->checkCollision(XMVector3Transform(bossFire6->getBoundingBoxMinLeft(), fireBoss2Mat), XMVector3Transform(bossFire6->getBoundingBoxMaxLeft(), fireBoss2Mat), XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove), XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)))
			{
				//OutputDebugString(L"\nFire damage!\n");
				player->setPlayerHP(player->getPlayerHP() - 1);
				player->setPlayerHurt(true);
				player->setPlayerHurtFromLeft(true);
				//player->setPlayerHurtFromRight(true);
				if (!heartHolder[player->getPlayerHP()].getIsDestry() && heartHolder[player->getPlayerHP()].getCheckIfObjHolder())
				{
					heartHolder[player->getPlayerHP()].setIsDestroy(true);
					removeObjFromObjHolder(heartHolder[player->getPlayerHP()].getObj());
					heartHolder[player->getPlayerHP()].setCheckIfObjHolder(false);
				}
				//bossFire2->resetProjectile();
			}
		}
	}
	//////////////////////
	//					//
	//	PHASE SPAWNING	//
	//					//
	//////////////////////
	else if (ifBossIsSpawning == true)
	{
		if (nrOfEnemysBossHasSpawned < 7)
		{
			//OutputDebugString(L"\nSPAWNING");
			if (bossTimer <= 0)
			{
				nrOfEnemysBossHasSpawned++;
				bossTimer = 300 * dt;
				boss->getObj()->setStartFrame(64);
				boss->getObj()->setEndFrame(93);
				//boss->setEnemyTranslationMatrix(tempBossTranslationMatrix * XMMatrixTranslation(0.0, 10.0f, 0.0));
				int randValue = rand() % 2;
				if (randValue == 0)
				{
					nrOfVisibleEnemies++;
					addEnemyToEnemyHolder(*enemy, nrOfVisibleEnemies, spawnBoss->getObj()->getPosition(), 0);
				}
				if (randValue == 1)
				{
					nrOfVisibleEnemies++;
					addEnemyToEnemyHolder(*enemy, nrOfVisibleEnemies, spawnBoss->getObj()->getPosition(), 0);
				}
				enemyHolder[nrOfVisibleEnemies - 1].setIsActive(true);
				enemyHolder[nrOfVisibleEnemies - 1].setEnemyHP(30);
				XMVECTOR tBboxMax;
				XMVECTOR tBboxMin;
				tBboxMax = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()) + 1, XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()) };
				tBboxMin = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()), XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()) };
				enemyHolder[nrOfVisibleEnemies - 1].setBboxMaxWeaponRight(tBboxMax);
				enemyHolder[nrOfVisibleEnemies - 1].setBboxMinWeaponRight(tBboxMin);

				tBboxMax = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()), XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMax()) };
				tBboxMin = { XMVectorGetX(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()) - 1, XMVectorGetY(enemyHolder[nrOfVisibleEnemies - 1].getObj()->getBoundingBoxMin()) };
				enemyHolder[nrOfVisibleEnemies - 1].setBboxMaxWeaponLeft(tBboxMax);
				enemyHolder[nrOfVisibleEnemies - 1].setBboxMinWeaponLeft(tBboxMin);

			}
			else if (bossTimer > 0)
			{
				updateBossTimer(dt);
			}
		}
		if (nrOfEnemysBossHasSpawned >= 7)
		{
			ifBossIsSpawning = false;
			canSpawnEnemys = false;
			canSpawnEnemys2 = false;
			nrOfEnemysBossHasSpawned = 0;
		}
	}

	if (!boss->getIsFrozen())
	{
		boss->getObj()->playAnimation(dt, false);
	}

	boss->updateAttackCooldownTimer(dt);

	//////////////////
	//				//
	//	COLLISION	//
	//				//
	//////////////////

	////CHECK COLLISION WITH FIREBALL

}

void gameClass::updateBossTimer(float dt)
{
	if (bossTimer > 0)
	{
		bossTimer -= 2 * dt;
	}
}

void gameClass::updateBossTimerForRainingFire(float dt)
{
	if (bossTimerForRainingFire > 0)
	{
		bossTimerForRainingFire -= 2 * dt;
	}
}

void gameClass::updateColdownDisplay(float dt)
{
	/*coldownDisplay->getObj()->setMaterialName("Transparent.png");
	coldownDisplay->getObj()->setWorldMatrix(XMMatrixIdentity());
	if (player->getCanCast())
	{
		OutputDebugString(L"\nCD < 0.0f!\n");
		coldownDisplay->setIsDestroy(false);
	}
	if (!player->getCanCast())
	{
		coldownDisplay->setIsDestroy(true);
	}
	if (player->getRingType() == 0 && player->getPlayAnimation())
	{
		coldownDisplay->getObj()->setMaterialName("Transparent.png");
		coldownDisplay->getObj()->setWorldMatrix(XMMatrixIdentity());
	}
	else if (player->getRingType() == 1 && !coldownDisplay->getIsDestry())
	{
		OutputDebugString(L"\nFADE!\n");
		coldownDisplay->getObj()->setMaterialName("MagicFireFadeSpriteSheet.png");
		coldownDisplay->getObj()->setWorldMatrix(XMMatrixScaling(0.4, 0.6, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) + 1.0f, 0.0f));
		coldownDisplay->updateAnimation(dt);
		if (coldownDisplay->getCurrentFrame() == 5)
		{
			coldownDisplay->setIsDestroy(true);
		}
	}
	else if (player->getRingType() == 2 && !coldownDisplay->getIsDestry())
	{
		OutputDebugString(L"\nFADE!\n");
		coldownDisplay->getObj()->setMaterialName("MagicBlueFadeSpriteSheet.png");
		coldownDisplay->getObj()->setWorldMatrix(XMMatrixScaling(0.4, 0.6, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) + 1.0f, 0.0f));
		coldownDisplay->updateAnimation(dt);
		if (coldownDisplay->getCurrentFrame() == 5)
		{
			coldownDisplay->setIsDestroy(true);
		}
	}
	else if (player->getRingType() == 3 && !coldownDisplay->getIsDestry())
	{
		coldownDisplay->getObj()->setMaterialName("ShieldFadeSpriteSheet.png");
		coldownDisplay->getObj()->setWorldMatrix(XMMatrixScaling(0.4, 0.6, 0.0) * XMMatrixTranslation(XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + ((XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetX(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) / 2), XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove)) + (XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMax(), playerMove)) - XMVectorGetY(XMVector3Transform(player->getObj()->getBoundingBoxMin(), playerMove))) + 1.0f, 0.0f));
		coldownDisplay->updateAnimation(dt);
		if (coldownDisplay->getCurrentFrame() == 5)
		{
			coldownDisplay->setIsDestroy(true);
		}
	}*/
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
