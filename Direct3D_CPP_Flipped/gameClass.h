#pragma once
#ifndef GAMECLASS_H
#define GAMECLASS_H
#define WIN32_LEAN_AND_MEAN						//speed ups building process. Reduces the size of the Win32 header files by excluding som of the less used APIs

#include <windows.h>
#include "graphicsClass.h"
#include "directInputClass.h"
#include "deltaTimeClass.h"
#include <DirectXMath.h>
#include "SoundClass.h"

#include "cameraClass.h"
#include "objectClass.h"
#include "directInputClass.h"
#include "enemyClass.h"
#include "backgroundPlaneClass.h"
#include "pickupClass.h"
#include "playerClass.h"
#include "platformClass.h"
#include "projectileClass.h"
#include "GUItest.h"
#include <cstdlib>
#include <string>

using namespace DirectX;


class gameClass
{
public:
	gameClass(HINSTANCE hInstance);
	gameClass(const gameClass& other);
	~gameClass();

	bool initialize(int ShowWnd);
	void run();
	void shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);		//handles our messages from window

	void getMoveMat(XMMATRIX& mat);
	void setMoveMat(float x);

	void addObjectToObjHolder(objectClass* obj);
	void removeObjFromObjHolder(objectClass* obj);

	void addObjectToObjHolderLimbo(objectClass* obj);
	void removeObjFromObjHolderLimbo(objectClass* obj);

	void addObjectToObjHolderMeny(objectClass* obj);
	void removeObjFromObjHolderMeny(objectClass* obj);

	void addObjectToObjHolderWin(objectClass* obj);
	void removeObjFromObjHolderWin(objectClass* obj);

	void addHearthToHeartHolder(GUItestClass &heart, int playerHP);
	void removeHearthFromHeartHolder(GUItestClass heart, int playerHP);

	void addPickupToPickupHolder(pickupClass &pickup, int nrOfVisiblePickups);
	void removePickupFromPickupHolder(pickupClass &pickup, int nrOfVisiblePickups);

	void initializeRings();

	void checkReleasedKeys();

private:
	bool frameLimbo(double dt);
	bool frameGame(double dt);
	bool frameMeny(double dt);
	bool frameWin(double dt);
	bool initializeWindow(int ShowWnd, int& width, int& height);
	void shutdownWindow();

	bool ringsInitialized;

	LPCWSTR appName;
	HINSTANCE hInstance;
	HWND hwnd;

	SoundClass* sound;
	bool soundAvailable;

	directInput* inputDirectOther;
	graphicsClass* graphics;
	deltatime* dt;

	cameraClass* camera;
	directInput* movementInput;
	enemyClass* enemy;
	backgroundClass* background;
	pickupClass* expFragment;
	pickupClass* ring;
	playerClass* player;
	platformClass* platform;
	projectileClass* projectile;
	GUItestClass* GUItest;

	GUItestClass* heartHolder;
	pickupClass* pickupHolder;

	std::vector<objectClass*> objHolder;
	std::vector<objectClass*> objHolderMeny;
	std::vector<objectClass*> objHolderLimbo;
	std::vector<objectClass*> objHolderWin;

	XMMATRIX moveMatTest;
	float moveTest;

	XMMATRIX world, view, proj, ortoProj;
	void updateConstantMatrices();
	XMMATRIX enemyMatPos, matMul, enemyFallingMat;
	XMMATRIX masterMovementEnemyMat;
	XMMATRIX enemyTranslationMatrix;
	void updateEnemy(double dt);
	XMMATRIX playerMove;
	void updatePlayer(platformClass* platform, double dt);
	void updatePlayerShadow();
	void updateCamera();
	XMMATRIX backgroundMat;
	void staticBackground();
	XMMATRIX pickupStartPosMoveMat;
	void updatePickup(double dt);
	void updateProjectile(double dt);
	XMMATRIX projectileMoveMat;
	float lengthBetween1;
	float lengthBetween2;
	void updateCollision(double dt);
	XMMATRIX platformMat;

	XMMATRIX enemyTrans;

	float lengthBetweenEnemyStartAndEnemyCurrentPos1;
	float lengthBetweenEnemyStartAndEnemyCurrentPos2;

	XMVECTOR tempBboxMin;
	int countEnemy;
	/*bool checkCollisionPlatform();*/

	bool checkCollisionPlatformTop(platformClass* platform, objectClass *obj, XMMATRIX objWorld);
	bool checkCollisionPlatformLeft(platformClass* platform, objectClass *obj, XMMATRIX objWorld);
	bool checkCollisionPlatformRight(platformClass* platform, objectClass *obj, XMMATRIX objWorld);
	bool checkCollisionPlatformBot(platformClass* platform, objectClass *obj, XMMATRIX objWorld);

	int nrOfVisiblePickups;

	bool gameStateLevel;
	bool gameStateMeny;
	bool gameStateLimbo;
	bool gameStateWin;
	void setGameStateLevel(bool other);
	void setGameStateMeny(bool other);
	void setGameStateLimbo(bool other);


	//GUI
	GUItestClass* GUIheart1;
	void updatePlatform();
	XMMATRIX guiMat;
	bool updateGUI(double dt, GUItestClass* obj);
	XMMATRIX heart1;
	XMMATRIX heart2;
	XMMATRIX heart3;
	XMMATRIX heart4;
	XMMATRIX heart5;

	GUItestClass* slot1;
	GUItestClass* slot2;
	XMMATRIX slot1Mat;
	XMMATRIX slot2Mat;
	XMMATRIX slot1MatLimbo;
	XMMATRIX slot2MatLimbo;
	void updateGUIPolygon(XMMATRIX mat1, XMMATRIX mat2);

	GUItestClass* ringDisplay;
	XMMATRIX ringDisplayMat;
	void updateRingDisplay();

	GUItestClass* xpDisplay;
	XMMATRIX xpDisplayMat;
	void updateXpDisplayMat();
	int tempXP;

	GUItestClass* slot1xp;
	XMMATRIX slot1xpMat;
	GUItestClass* slot2xp;
	XMMATRIX slot2xpMat;
	void updateSlotXp(XMMATRIX mat1, XMMATRIX mat2);
	XMMATRIX slot1xpMatLimbo;
	XMMATRIX slot2xpMatLimbo;

	////////////////////////MENY 
	GUItestClass* meny;
	XMMATRIX menyMat;
	bool done;
	GUItestClass* menyHighlight;
	XMMATRIX menyHighlightMat;
	int counterOverlay;
	void setCounterOverlay(int other);
	int getCounterOverlay();
	void updateOverlay();
	int menyTimer;
	bool menyCheck;

	
	bool firstFrame;


	/////////LIMBO STUFF
		backgroundClass* limboFrontPlane;
		pickupClass* limboSmithPlane;
		backgroundClass* limboBackPlane;
		pickupClass* limboTextPlane;
		platformClass* limboWalkingPlane;
		XMMATRIX limboMat;
		void updateLimboBackground();

		pickupClass* limboPickupHolder;

		GUItestClass* healthUpgradeCount;
		XMMATRIX healthUpgradeCountMat;
		GUItestClass* speedUpgradeCount;
		void updateCountersShop();
		XMMATRIX speedUpgradeCountMat;

		GUItestClass* totalCostPendingSlot2;
		XMMATRIX totalCostPendingSlot2Mat;
		GUItestClass* totalCostPendingSlot1;
		void pendingCostUpdate();
		XMMATRIX totalCostPendingSlot1Mat;

	//has to do with shop
	GUItestClass* upgradeGUI;
	GUItestClass* upgradeOverlay;
	void updateShopWorldMat();
	XMMATRIX shopMat;
	void updateShop(double dt, GUItestClass* obj, GUItestClass* obj2);
	bool isUpgradeHPAactive;
	int nrHPtoBeUpgraded;
	int healthCost;
	bool upgradeCooldown;
	int upgradeTimer;
	int activeShopState;
	int ShopTabsCounter;
	int upgradeOvlerlayCounterWeapons;

	bool enterReleased;
	bool arrowUpReleased;
	bool arrowDownReleased;
	bool arrowLeftReleased;
	bool arrowRightReleased;

	int shopOverlayCount;
	int shopOverlayCountRow;
	XMMATRIX shopOverlayMat;
	int getShopOverlayCounter();
	int getShopOverlayCounterRow();
	void setShopOverlayCounterRow(int x);
	void setShopOverlayCounter(int x);
	int nrSpeedToBeUpgraded;
	int SpeedCost;

	int totalPendingCost;
	int costHPBeginning;
	int costSpeedBeginnning;

	//////////////////////WIN STATE
	GUItestClass* win;
	XMMATRIX winMat;

	backgroundClass* playerShadowPlane;
	XMMATRIX shadowMat;
};

//func proto and globals needed so we can redirect the windows system messaging into our messageHandler func inside the game class
//func proto
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//globals
static gameClass* appHandle = 0;

#endif