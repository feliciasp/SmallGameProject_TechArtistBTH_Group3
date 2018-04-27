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
	void setPlayerHurtFromLeft(bool x);
	void setPlayerHurtFromRight(bool x);
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

	bool getInvulnurable();

	void setHasRing(bool check);
	bool getHasRing();

	void setRingType(int other);
	int getRingType();

	

	float getMoveValY();

private:
	bool isHurt;
	bool hurtFromLeft;
	bool hurtFromRight;
	bool fallBack;
	float hurtFallback;
	float hurtFallbackValue;
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

	bool dodge;
	bool isDodging;
	float dodgeFallback;
	float dodgeFallbackValue;
	bool dodgeReleased;
	bool invulnurable;

	bool dodgeCooldownActive;
	float dodgeCooldown;

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
	bool attackReleased;

	bool hasRing;
	int ringType; // 0 = DOUBLEJUMP, 1 = ???, 2 = ???, 3 = ???, 4 = ???, 5 = ???, 6 = ???, 7 = ???, 8 = ???.

	bool isInObjHolder;


};


#endif PLAYERCLASS_H