#pragma once
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "objectClass.h"
#include "directInputClass.h"
#include "weaponClass.h"
#include "projectileClass.h"

class playerClass
{
public:
	playerClass();
	playerClass(const playerClass& other);
	~playerClass();

	bool initialize(ID3D11Device* device, const char* filename, HINSTANCE hInstance, HWND hwnd);
	void shutdown();
	void setTranslation(float x);

	objectClass* getObj();
	void getTranslationMat(XMMATRIX& other);
	void getTranslationMatStart(XMMATRIX& other);
	void setStartMat(float x, float y);

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

	void updateAnimation(double dt);

	bool getFlipped();
	int getFrameCount();
	int getCurrentFrame();
	int getCurrentAnimation();
	float getAnimationTime();
	float getcurrentTime();

	bool hurtState();

	void updateTimer();

	weaponClass* getWeapon();
	bool getIfAttack();

	bool getIfInObjHolder();
	void setIfInObjHolder(bool other);

	void setHasRing(bool check);
	bool getHasRing();

	void setRingType(int other);
	int getRingType();

	void setFireballCast(bool check);
	bool getFireballCast();

	float getMoveValY();

private:
	bool isHurt;
	int fakeTimer;

	objectClass* obj;
	directInput* input;
	weaponClass* weapon;

	float moveVal;
	XMMATRIX translation;
	XMMATRIX transStart;

	XMVECTOR triggerCheck;

	bool idle;
	bool running;
	bool jumping;
	bool falling;
	bool attacking;
	bool isHit;

	bool isJumping;
	bool justJumped;
	float upSpeed;
	float moveValX;
	float moveValY;
	float moveValZ;

	bool hasDoubleJumped;
	bool spaceReleased;

	float oldMoveValX;
	float oldMoveValY;

	XMMATRIX moveMat;

	bool flipped;
	int frameCount;
	int currentFrame;
	int currentAnimation;
	float animationTime;
	float currentTime;


	int nrOfLoops;
	float timeBetweenFrames;

	int HP;
	bool isPlayerHurt;
	bool isAttacking;
	void checkIfAttacking();

	bool fireballCast; //has player cast fireball?

	bool hasRing;
	int ringType; // 0 = DOUBLEJUMP, 1 = FIREBALL, 2 = ???, 3 = ???, 4 = ???, 5 = ???, 6 = ???, 7 = ???, 8 = ???.

	bool isInObjHolder;


};


#endif PLAYERCLASS_H