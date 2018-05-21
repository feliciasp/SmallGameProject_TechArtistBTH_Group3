#pragma once
#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include "objectClass.h"
#include "directInputClass.h"
#include "weaponClass.h"
#include "projectileClass.h"
#include "SoundClass.h"

class playerClass
{
public:
	playerClass();
	playerClass(const playerClass& other);
	~playerClass();

	bool initialize(ID3D11Device* device, const char* filename, HINSTANCE hInstance, HWND hwnd, int width, int height);
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

	void handleMovement(double dt, bool check);
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

	void setFireballCast(bool check);
	bool getFireballCast();

	int getNrPixelFramgent();
	void setNrPixelFragments(int other);

	int getNrPolygons();
	void setNrPolysgons(int other);

	bool getNrWeaponBought(int index);
	void setNrWeaponBought(int index, bool other);

	int getNrWeaponCost(int index);

	float getMoveValY();

	void setMaxHP(int other);
	int getMaxHP();

	bool getShowShadow();
	bool getIsJumping();

	float getSpeedVal();
	void setSpeedVal(float x);

	

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
	SoundClass* sound;
	bool soundAvailable;

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


	bool inAir;

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
	int maxHP;
	bool isPlayerHurt;
	bool isAttacking;
	void checkIfAttacking();
	bool attackReleased;

	bool magicCast; //has player cast fireball?
	bool magicWasCast;
	float magicCooldown;

	bool hasRing;
	int ringType; // 0 = DOUBLEJUMP, 1 = FIREBALL, 2 = FROSTBOLT, 3 = ???, 4 = ???, 5 = ???, 6 = ???, 7 = ???, 8 = ???.

	bool isInObjHolder;


	////PICKUP STATS!!!!!
	int polygoner;
	int fargments;

	bool showShadow;

	float speedVal;

	bool weaponBought[4];
	int weaponCost[4];



};


#endif PLAYERCLASS_H