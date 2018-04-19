#pragma once
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "objectClass.h"
#include "directInputClass.h"

class playerClass
{
public:
	playerClass();
	playerClass(const playerClass& other);
	~playerClass();

	bool initlialize(ID3D11Device* device, const char* filename, HINSTANCE hInstance, HWND hwnd);
	void shutdown();
	void setTranslation(float x);

	objectClass* getObj();
	void getTranslationMat(XMMATRIX& other);
	void getTranslationMatStart(XMMATRIX& other);
	void setStartMat(float x);

	float getMove();
	void setMove(float x);
	void resetMove();

	XMVECTOR getTriggerCheck();

	void playerClass::handleMovement(float dt, bool collisionCheckTop, bool collisionCheckLeft, bool collisionCheckRight, bool collisionCheckBot);
	void getMoveMat(XMMATRIX& mat);

	void resetPlayer();

	void setPlayerHP(int x);
	int getPlayerHP();

	void setPlayerHurt(bool x);
	bool getPlayerHurt();

	bool getFlipped();
	int getFrameCount();
	int getCurrentFrame();
	float getAnimationTime();
	float getcurrentTime();

private:
	objectClass* obj;
	directInput* input;

	float moveVal;
	XMMATRIX translation;
	XMMATRIX transStart;

	XMVECTOR triggerCheck;

	bool isJumping;
	bool justJumped;
	float upSpeed;
	float moveValX;
	float moveValY;
	float moveValZ;
	XMMATRIX moveMat;

	bool flipped;
	int frameCount;
	int currentFrame;
	float animationTime;
	float currentTime;

	int HP;
	bool isPlayerHurt;
};


#endif PLAYERCLASS_H