#pragma once
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "objectClass.h"
#include "directInputClass.h"
#include "weaponClass.h"

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

	void handleMovement(double dt);
	void checkCollisions(bool top, bool left, bool right, bool bot);
	void getMoveMat(XMMATRIX& mat);

	void resetPlayer();

	void setPlayerHP(int x);
	int getPlayerHP();

	void setPlayerHurt(bool x);
	bool getPlayerHurt();

	void updateAnimation();

	bool getFlipped();
	int getFrameCount();
	int getCurrentFrame();
	int getCurrentAnimation();
	float getAnimationTime();
	float getcurrentTime();

	weaponClass* getWeapon();
	bool getIfAttack();

private:
	objectClass* obj;
	directInput* input;
	weaponClass* weapon;

	float moveVal;
	XMMATRIX translation;
	XMMATRIX transStart;

	XMVECTOR triggerCheck;

	bool idle;
	bool running;

	bool isJumping;
	bool justJumped;
	float upSpeed;
	float moveValX;
	float moveValY;
	float moveValZ;

	float oldMoveValX;
	float oldMoveValY;

	XMMATRIX moveMat;

	bool flipped;
	int frameCount;
	int currentFrame;
	int currentAnimation;
	float animationTime;
	float currentTime;

	int animationSpeed;

	int HP;
	bool isPlayerHurt;
	bool isAttacking;
	void checkIfAttacking();
};


#endif PLAYERCLASS_H