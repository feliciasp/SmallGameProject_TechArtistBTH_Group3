#pragma once
#ifndef GAMECLASS_H
#define GAMECLASS_H
#define WIN32_LEAN_AND_MEAN						//speed ups building process. Reduces the size of the Win32 header files by excluding som of the less used APIs

#include <windows.h>
#include "graphicsClass.h"
#include "directInputClass.h"
#include "deltaTimeClass.h"
#include <DirectXMath.h>

#include "cameraClass.h"
#include "objectClass.h"
#include "directInputClass.h"
#include "enemyClass.h"
#include "backgroundPlaneClass.h"
#include "pickupClass.h"
#include "playerClass.h"
#include "platformClass.h"
#include "GUItest.h"

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

	private:
		bool frameLimbo(double dt);
		bool frameGame(double dt);
		bool frameMeny(double dt);
		bool initializeWindow(int ShowWnd, int& width, int& height);
		void shutdownWindow();
		
		
		LPCWSTR appName;
		HINSTANCE hInstance;
		HWND hwnd;

		directInput* inputDirectOther;
		graphicsClass* graphics;
		deltatime* dt;

		cameraClass* camera;
		directInput* movementInput;
		enemyClass* enemy;
		backgroundClass* background;
		pickupClass* pickup;
		playerClass* player;
		platformClass* platform;
		GUItestClass* GUItest;

		std::vector<objectClass*> objHolder;
		std::vector<objectClass*> objHolderMeny;
		std::vector<objectClass*> objHolderLimbo;

		XMMATRIX moveMatTest;
		float moveTest;

		XMMATRIX world, view, proj;
		void updateConstantMatrices();
		XMMATRIX enemyMatPos, matMul, enemyFallingMat;
		XMMATRIX masterMovementEnemyMat;
		XMMATRIX enemyTranslationMatrix;
		void updateEnemy(double dt);
		XMMATRIX playerMove;
		void updatePlayer(double dt);
		void updateCamera();
		XMMATRIX backgroundMat;
		void staticBackground();
		XMMATRIX pickupStartPosMoveMat;
		void updatePickup();
		float lengthBetween1;
		float lengthBetween2;
		void updateCollision(double dt);
		XMMATRIX platformMat;


		int countEnemy;
		/*bool checkCollisionPlatform();*/

		bool checkCollisionPlatformTop(objectClass *obj, XMMATRIX objWorld);
		bool checkCollisionPlatformLeft(objectClass *obj, XMMATRIX objWorld);
		bool checkCollisionPlatformRight(objectClass *obj, XMMATRIX objWorld);
		bool checkCollisionPlatformBot(objectClass *obj, XMMATRIX objWorld);


	
		bool gameStateLevel;
		bool gameStateMeny;
		bool gameStateLimbo;
		void setGameStateLevel(bool other);
		void setGameStateMeny(bool other);
		void setGameStateLimbo(bool other);

		//GUI
		GUItestClass* GUIheart1;
		GUItestClass* GUIheart2;
		GUItestClass* GUIheart3;
		void updatePlatform();
		XMMATRIX guiMat;
		bool updateGUI(double dt, GUItestClass* obj);
		XMMATRIX heart1;
		XMMATRIX heart2;
		XMMATRIX heart3;

		////////////////////////MENY 
		GUItestClass* meny;
		XMMATRIX menyMat;
		bool done;

		/////////LIMBO STUFF
		GUItestClass* limbo;
		XMMATRIX limboMat;
};

//func proto and globals needed so we can redirect the windows system messaging into our messageHandler func inside the game class
//func proto
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//globals
static gameClass* appHandle = 0;

#endif