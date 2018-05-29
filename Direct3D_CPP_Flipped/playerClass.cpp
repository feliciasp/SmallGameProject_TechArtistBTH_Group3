#include "playerClass.h"

playerClass::playerClass()
{
	obj = 0;
	moveVal = 0;
	input = 0;
	sound = 0;
	soundAvailable = true;

	hasRing = false;
	ringType = 0;

	translation = XMMatrixIdentity();
	transStart = XMMatrixIdentity();
	triggerCheck = { 4.0f, 0.0f, 0.0f };

	isInObjHolder = false;

	nrRun = 0;

	//movement
	moveValX = 0.0f;
	moveValY = 0.0f;
	moveValZ = 0.0f;
	moveMat = XMMatrixIdentity();
	upSpeed = 0.0f;
	isJumping = false;
	justJumped = false;
	flipped = false;
	inAir = false;

	isPlayerHurt = false;
	frameCount = 2;

	isHurt = false;
	hurtFromRight = false;
	hurtFromLeft = false;
	fallBack = false;
	hurtFallback = 4.0f;
	hurtFallbackValue = 0.0f;
	fakeTimer = 0;

	firstFrame = true;

	gravityTimer = 0;

	isAttacking = false;

	currentFrame = 1;
	currentAnimation = 1;
	currentTime = 0;

	animTimer = 0;
	animAllowSwap = false;

	idle = true;
	running = false;
	jumping = false;
	falling = false;
	attacking = false;
	attackReleased = true;
	isHit = false;
	timeBetweenFrames = 0.25f;
	nrOfLoops = 0;

	polygoner = 0;
	for (int i = 0; i < 4; i++)
	{
		weaponBought[i] = false;
	}

	weaponCost[0] = 3;
	weaponCost[1] = 10;
	weaponCost[2] = 30;
	weaponCost[3] = 100;

	dodge = false;
	isDodging = false;
	dodgeFallback = 6.2f;
	dodgeFallbackValue = 0.0f;
	dodgeReleased = true;
	invulnurable = false;

	dodgeCooldownActive = false;
	dodgeCooldown = 1.2f;

	hasDoubleJumped = false;

	spaceReleased = true;
	wReleased = true;

	magicCast = false;
	magicWasCast = false;
	magicCooldown = 0.0f;
	shieldBubbleCooldown = 0.0f;
	shieldBubbleCast = false;

	polygoner = 0;
	fargments = 20;

	showShadow = true;

	weaponType = 0;
}

playerClass::playerClass(const playerClass & other)
{
}

playerClass::~playerClass()
{
}

bool playerClass::initialize(ID3D11Device* device, const char* filename, HINSTANCE hInstance, HWND hwnd,int width,int height)
{
	bool result;

	obj = new objectClass;
	if (!obj)
	{
		MessageBox(NULL, L"Error create object obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = obj->initlialize(device, filename);
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	obj->setType(2);

	input = new directInput;
	if (!input)
	{
		MessageBox(NULL, L"Error create object obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = input->initialize(hInstance, hwnd, width, height);
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//WEAPONS BEGIN
	XMVECTOR tempBboxMax;

	weapon1 = new weaponClass;
	if (!weapon1)
	{
		MessageBox(NULL, L"Error create object weapon1",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	weapon1->setDamage(1);

	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(this->getObj()->getBoundingBoxMax()) };
	this->weapon1->setBboxMaxWeaponRight(tempBboxMax);
	this->weapon1->setBboxMinWeaponRight(this->getObj()->getBoundingBoxMax());
	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(this->getObj()->getBoundingBoxMin()) };
	this->weapon1->setBboxMaxWeaponLeft(this->getObj()->getBoundingBoxMin());
	this->weapon1->setBboxMinWeaponLeft(tempBboxMax);

	weapon2 = new weaponClass;
	if (!weapon2)
	{
		MessageBox(NULL, L"Error create object weapon2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	weapon2->setDamage(2);

	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(this->getObj()->getBoundingBoxMax()) };
	this->weapon2->setBboxMaxWeaponRight(tempBboxMax);
	this->weapon2->setBboxMinWeaponRight(this->getObj()->getBoundingBoxMax());
	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(this->getObj()->getBoundingBoxMin()) };
	this->weapon2->setBboxMaxWeaponLeft(this->getObj()->getBoundingBoxMin());
	this->weapon2->setBboxMinWeaponLeft(tempBboxMax);

	weapon3 = new weaponClass;
	if (!weapon3)
	{
		MessageBox(NULL, L"Error create object weapon2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	weapon3->setDamage(4);

	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(this->getObj()->getBoundingBoxMax()) };
	this->weapon3->setBboxMaxWeaponRight(tempBboxMax);
	this->weapon3->setBboxMinWeaponRight(this->getObj()->getBoundingBoxMax());
	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(this->getObj()->getBoundingBoxMin()) };
	this->weapon3->setBboxMaxWeaponLeft(this->getObj()->getBoundingBoxMin());
	this->weapon3->setBboxMinWeaponLeft(tempBboxMax);

	weapon4 = new weaponClass;
	if (!weapon4)
	{
		MessageBox(NULL, L"Error create object weapon2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	weapon4->setDamage(6);

	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(this->getObj()->getBoundingBoxMax()) };
	this->weapon4->setBboxMaxWeaponRight(tempBboxMax);
	this->weapon4->setBboxMinWeaponRight(this->getObj()->getBoundingBoxMax());
	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(this->getObj()->getBoundingBoxMin()) };
	this->weapon4->setBboxMaxWeaponLeft(this->getObj()->getBoundingBoxMin());
	this->weapon4->setBboxMinWeaponLeft(tempBboxMax);

	weapon5 = new weaponClass;
	if (!weapon5)
	{
		MessageBox(NULL, L"Error create object weapon2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	weapon5->setDamage(8);

	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMax()) + 3, XMVectorGetY(this->getObj()->getBoundingBoxMax()) };
	this->weapon5->setBboxMaxWeaponRight(tempBboxMax);
	this->weapon5->setBboxMinWeaponRight(this->getObj()->getBoundingBoxMax());
	tempBboxMax = { XMVectorGetX(this->getObj()->getBoundingBoxMin()) - 3, XMVectorGetY(this->getObj()->getBoundingBoxMin()) };
	this->weapon5->setBboxMaxWeaponLeft(this->getObj()->getBoundingBoxMin());
	this->weapon5->setBboxMinWeaponLeft(tempBboxMax);

	//WEAPONS END

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
	/*	MessageBox(NULL, L"Error sound obj init",
			L"Error", MB_OK | MB_ICONERROR);
		return false;*/
		soundAvailable = false;
	}

	setStartMat(0.0f, 5.0f);

	return true;
}

void playerClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
	if (input)
	{
		input->shutdown();
		delete input;
		input = 0;
	}
	if (weapon1)
	{
		weapon1->shutdown();
		delete weapon1;
		weapon1 = 0;
	}
	if (weapon2)
	{
		weapon2->shutdown();
		delete weapon2;
		weapon2 = 0;
	}
	if (weapon3)
	{
		weapon3->shutdown();
		delete weapon3;
		weapon3 = 0;
	}
	if (weapon4)
	{
		weapon4->shutdown();
		delete weapon4;
		weapon4 = 0;
	}
	if (weapon5)
	{
		weapon5->shutdown();
		delete weapon5;
		weapon5 = 0;
	}
	if (sound)
	{
		sound->shutdown();
		delete sound;
		sound = 0;
	}
}

void playerClass::setTranslation(float x)
{
	translation = XMMatrixTranslation(x, 0.0f, 0.0f);
}

objectClass* playerClass::getObj()
{
	return this->obj;
}

void playerClass::getTranslationMat(XMMATRIX & other)
{
	other = this->translation;
}

void playerClass::getTranslationMatStart(XMMATRIX & other)
{
	other = this->transStart;
}

void playerClass::setStartMat(float x, float y)
{
	this->transStart = XMMatrixTranslation(x, y, 0.0f);
}

float playerClass::getMove()
{
	return moveVal;
}

void playerClass::setMove(float x)
{
	moveVal -= x;
}

void playerClass::resetMove()
{

	moveVal = 0;
}
bool playerClass::hurtState()
{
	if (this->isHurt == false && fakeTimer == 0)
	{
		this->isHurt = true;
		fakeTimer = 300;
		return true;
	}
	else
	{
		return false;
	}
}

void playerClass::updateTimer()
{
	this->fakeTimer -= 1;
	if (this->fakeTimer == 0)
	{
		this->isHurt = false;
	}
}

XMVECTOR playerClass::getTriggerCheck()
{
	return this->triggerCheck;
}

void playerClass::handleMovement(double dt, bool checkClimb)
{
	if (animTimer >= 0.1)
	{
		animAllowSwap = true;
		animTimer = 0;
	}

	animTimer += dt;
	
		
	invulnurable = false;

	gravityTimer += 1;

	oldMoveValX = moveValX;
	oldMoveValY = moveValY;

	if (dt > 0.1)
		dt = 0;

	idle = true;

	bool isCliming = false;

	justJumped = false;
	currentAnimation = 1;
	frameCount = 2;
	if (!this->input->isWPressed())
	{
		wReleased = true;
	}
	if (this->input->isWPressed() && !fallBack && !isDodging && !checkClimb)
	{
		gravityTimer = 0;
		moveValY += 6 * dt;
		isCliming = true;
		upSpeed = 0;
		if (wReleased)
		{
			currentFrame = 1;
			wReleased = false;

		}
		currentAnimation = 8;
		frameCount = 2;	
		idle = false;
		running = false;
		timeBetweenFrames = 0.05f;
	}
	else
	{
		moveValY += upSpeed * dt;
	}

	timeBetweenFrames = 0.25f;
	showShadow = true;

	input->readKeyboard(dt);
	input->readGamepad();

	if (dodgeCooldownActive)
	{
		dodgeFallbackValue += 1 * dt;
		if (dodgeFallbackValue >= dodgeCooldown)
		{
			dodgeFallbackValue = 0.0f;
			dodgeCooldownActive = false;
		}
	}

	if (!this->input->isEPressed() && !dodgeCooldownActive)
	{
		dodgeReleased = true;
	}

	if (this->input->isEPressed() && !dodgeCooldownActive && dodgeReleased)
	{
		dodge = true;
		dodgeReleased = false;
	}

	
	
	if (isHurt && dodge)
	{
		isHurt = true;
		dodge = false;
	}

	if (dodge && !isHurt)
	{
		currentFrame = 7;
		currentTime = 0;
		dodge = false;
		isDodging = true;
	}

	if (isDodging)
	{
		invulnurable = true;
		frameCount = 10;
		currentAnimation = 2;
		timeBetweenFrames = 4.0f;

		if (flipped)
		{
			moveValX += -17.0f * dt;
			dodgeFallbackValue += 17.0f * dt;
			if (dodgeFallbackValue >= dodgeFallback)
			{
				isDodging = false;
				dodgeFallbackValue = 0.0f;
				invulnurable = false;
				dodgeCooldownActive = true;
				currentTime = 0;
				currentFrame = 1;
			}
		}

		if (!flipped)
		{
			moveValX += 17.0f * dt;
			dodgeFallbackValue += 17.0f * dt;
			if (dodgeFallbackValue >= dodgeFallback)
			{
				isDodging = false;
				dodgeFallbackValue = 0.0f;
				invulnurable = false;
				dodgeCooldownActive = true;
				currentTime = 0;
				currentFrame = 1;
			}
		}
	}

	if (isHurt && !isDodging)
	{
		currentFrame = 1;
		currentTime = 0;
		isHurt = false;
		fallBack = true;
	}

	if (fallBack)
	{
		frameCount = 1;
		currentAnimation = 5;
		invulnurable = true;

		if (hurtFromLeft)
		{
			moveValX += -17.0f * dt;
			hurtFallbackValue += 17.0f * dt;
			if (hurtFallbackValue >= hurtFallback)
			{
				fallBack = false;
				hurtFromLeft = false;
				hurtFallbackValue = 0.0f;
			}
		}

		else if (hurtFromRight)
		{
			moveValX += 17.0f * dt;
			hurtFallbackValue += 17.0f * dt;
			if (hurtFallbackValue >= hurtFallback)
			{
				fallBack = false;
				hurtFromRight = false;
				hurtFallbackValue = 0.0f;
			}
		}
	}

	if (this->input->isAPressed() && !fallBack && !isDodging)
	{
		moveValX += -speedVal * dt;
		if (!isCliming)
		{
			if (!running && !attacking)
			{
				currentTime = 0;
				currentFrame = 1;
			}
			currentAnimation = 2;
			frameCount = 8;
			timeBetweenFrames = 0.1f;
			idle = false;
			running = true;
			//OutputDebugString(L"func move left called");
			if (this->flipped == false && !attacking)
			{
				flipped = true;

			}
		}
		
	}
	
	if (this->input->isDPressed() && !fallBack && !isDodging)
	{
		moveValX += speedVal * dt;
		if (!isCliming)
		{
			if (running == false && attacking == false)
			{
				currentTime = 0;
				currentFrame = 1;
			}
			currentAnimation = 2;
			frameCount = 8;
			timeBetweenFrames = 0.1f;
			idle = false;
			running = true;
			//OutputDebugString(L"func move right called");
			if (this->flipped == true && !attacking)
			{
				flipped = false;
			}
		}
		
	}

	if (running && currentFrame % 4 == 0 && firstFrame ||
		running && currentFrame == 9 && firstFrame)
	{
		if (soundAvailable)
			sound->playSFX(1, 6);
		firstFrame = false;
	}
	if (currentFrame % 4 != 0 && !firstFrame)
	{
		firstFrame = true;
	}
	
	if (this->input->isSpacePressed() && !fallBack && !isDodging)
	{
		if (!isJumping)
		{
			if (soundAvailable)
				sound->playSFX(1, 1);

			gravityTimer = 0;
			upSpeed = 23.5f;
			//OutputDebugString(L"upSpeed set");
			justJumped = true;
			spaceReleased = false;
			inAir = true;
			if (attacking == false)
			{
				currentFrame = 1;
				currentTime = 0;
			}
			
		}


		if (hasRing == true && ringType == 0)
		{
			if (isJumping == true && !hasDoubleJumped && spaceReleased)
			{
				if (soundAvailable)
					sound->playSFX(1, 1);
				gravityTimer = 0;
				upSpeed = 23.5f;
				if (attacking == false)
				{
					currentFrame = 1;
					currentTime = 0;
				}
				hasDoubleJumped = true;
			}
		}
		isJumping = true;
	}

	if (!this->input->isSpacePressed() && upSpeed > upSpeed * 0.5 && !fallBack && !isDodging)
	{
		upSpeed -= upSpeed - (upSpeed * 0.99);
	}
	if (!this->input->isSpacePressed() && !fallBack)
	{
		spaceReleased = true;
	}

	if (upSpeed > 1 && !fallBack)
	{
		gravityTimer += 1;
		running = false;
		idle = false;
		jumping = true;
		showShadow = false;
		currentAnimation = 3;
		frameCount = 2;
		timeBetweenFrames = 0.1f;
	}

	if (inAir)
	{
		running = false;
		idle = false;
		jumping = true;
		showShadow = false;
		currentAnimation = 3;
		frameCount = 2;
		timeBetweenFrames = 0.1f;
	}
	
	if (upSpeed > -1.0f && !fallBack && !isCliming)
	{
		upSpeed += (-50 * dt) - gravityTimer * dt;
		isJumping = true;
	}
	else if (upSpeed < -1.0f && !fallBack && !isDodging && !isCliming) //upSpeed less than -1.0f;
	{
		gravityTimer = 0;
		if (falling == false && attacking == false)
		{
			currentTime = 0;
			currentFrame = 1;
		}
		upSpeed += (-50 * dt) - -upSpeed * dt;
		if (animAllowSwap)
		{
			currentAnimation = 4;
			timeBetweenFrames = 0.1f;
			frameCount = 2;
			idle = false;
			running = false;
			falling = true;
			showShadow = false;
			inAir = false;
		}
	}

	if (this->input->isOPressed() && !fallBack && !isDodging && attackReleased)
	{
		if (attacking == false)
		{
			if (soundAvailable)
				sound->playSFX(1, 0);
			
			attacking = true;
			currentTime = 0;
			currentFrame = 1;
		}

		attackReleased = false;
	}

	//Fireball cast
	if (this->input->isPPressed() && hasRing && ringType == 1 && !magicCast && magicCooldown == 0.0f)
	{
		if (soundAvailable)
			sound->playSFX(1, 2);
		
		magicCast = true;
		magicWasCast = true;
	}
	//Frostbolt cast
	if (this->input->isPPressed() && hasRing && ringType == 2 && !magicCast && magicCooldown == 0.0f)
	{
		if (soundAvailable)
			sound->playSFX(1, 3);

		magicCast = true;
		magicWasCast = true;
	}
	//Shield bubble cast
	if (this->input->isPPressed() && hasRing && ringType == 3 && !shieldBubbleCast && shieldBubbleCooldown == 0.0f && !magicWasCast)
	{
		if (soundAvailable)
			sound->playSFX(1, 9);

		shieldBubbleCast = true;
		invulnurable = true;
	}

	if (shieldBubbleCast)
	{

		shieldBubbleCooldown += dt;

		if (shieldBubbleCooldown > 1.0f)
		{
			invulnurable = false;
			shieldBubbleCooldown = 0.0f;
			shieldBubbleCast = false;
			magicWasCast = true;
		}
	}

	if (magicWasCast)
	{
		magicCooldown += dt;

		if (magicCooldown > 6.0f)
		{
			magicCooldown = 0.0f;
			magicWasCast = false;
			canCast = true;
		}
		else
		{
			canCast = false;
		}
	}



	if (!this->input->isOPressed())
	{
		attackReleased = true;
	}

	if (attacking == true && !fallBack)
	{
		currentAnimation = 6;
		frameCount = 4;

		timeBetweenFrames = 0.06f;

		idle = false;
	}
	
	if (running == true && idle == true && attacking == false && !fallBack && !isDodging)
	{
		running = false;
		currentTime = 0;
		currentFrame = 1;
		timeBetweenFrames = 0.25f;
	}

	if (falling == true && idle == true && attacking == false && !fallBack && !isDodging)
	{
		falling = false;
		currentTime = 0;
		currentFrame = 1;
		timeBetweenFrames = 0.25f;
	}

	if (jumping == true && idle == true && attacking == false && !fallBack && !isDodging)
	{
		jumping = false;
		currentTime = 0;
		currentFrame = 1;
		timeBetweenFrames = 0.25f;

	}

	if (isHit == true && idle == true)
	{
		isHit = false;
		currentTime = 0;
		currentFrame = 1;
		timeBetweenFrames = 0.1f;
	}

	if (isDodging)
	{
		moveValY = oldMoveValY;
		upSpeed = 0.0f;
	}
	
	if (HP <= 0) {
		currentAnimation = 7;
		frameCount = 9;
		timeBetweenFrames = 0.1f;
	}

	moveMat = XMMatrixTranslation(moveValX, moveValY+8, 0.0f);
}

void playerClass::checkCollisions(bool top, bool left, bool right, bool bot, double dt)
{
	if (top)
	{
		moveValY = oldMoveValY;
		if (upSpeed > 0)
			upSpeed = 0;
	}
	if (bot)
	{
		animAllowSwap = false;
		animTimer = 0;

		gravityTimer = 0;
		moveValY = oldMoveValY;
		isJumping = false;
		upSpeed = 0;
		idle = true;
		hasDoubleJumped = false;
	}

	if (left)
	{
		moveValX = oldMoveValX;
	}
	if (right)
	{
		moveValX = oldMoveValX;
	}

	moveMat = XMMatrixTranslation(moveValX, moveValY + 8, 0.0f);
}

void playerClass::checkIfAttacking()
{
	if (isHit == true)
	{
		this->isAttacking = true;
	}
	else
	{
		this->isAttacking = false;
	}
}

bool playerClass::getIfAttack()
{
	return isHit;
}

bool playerClass::getAttacking()
{
	return this->attacking;
}

bool playerClass::getIfInObjHolder()
{
	return this->isInObjHolder;
}

void playerClass::setIfInObjHolder(bool other)
{
	this->isInObjHolder = other;
}


bool playerClass::getInvulnurable()
{
	return this->invulnurable;
}

float playerClass::getMoveValY()
{
	return this->moveValY;
}


void playerClass::setMaxHP(int other)
{
	this->maxHP = other;
}

int playerClass::getMaxHP()
{
	return this->maxHP;
}
bool playerClass::getShowShadow()
{
	return this->showShadow;
}

bool playerClass::getIsJumping()
{
	return this->isJumping;
}

float playerClass::getSpeedVal()
{
	return this->speedVal;
}

void playerClass::setSpeedVal(float x)
{
	this->speedVal = x;
}

void playerClass::setWeaponType(int type)
{
	this->weaponType = type;
}

int playerClass::getWeaponType()
{
	return this->weaponType;
}

bool playerClass::getPlayAnimation()
{
	return this->playAnimation;
}

void playerClass::setPlayAnimation(bool other)
{
	this->playAnimation = other;
}

float playerClass::getCDDisplay()
{
	return this->magicCooldown;
}

bool playerClass::getMagicWasCast()
{
	return this->magicWasCast;
}

void playerClass::setNrRun(int x)
{
	this->nrRun = x;
}

bool playerClass::getCanCast()
{
	return canCast;
}

void playerClass::setHasRing(bool check)
{
	this->hasRing = check;
}

bool playerClass::getHasRing()
{
	return this->hasRing;
}

void playerClass::setRingType(int other)
{
	this->ringType = other;
}

int playerClass::getRingType()
{
	return this->ringType;
}


void playerClass::setMagicCast(bool check)
{
	this->magicCast = check;
}

bool playerClass::getMagicCast()
{
	return this->magicCast;
}

bool playerClass::getShieldBubbleCast()
{
	return this->shieldBubbleCast;
}

int playerClass::getNrPixelFramgent()
{
	return this->fargments;
}

void playerClass::setNrPixelFragments(int other)
{
	this->fargments = other;
}

int playerClass::getNrPolygons()
{
	return this->polygoner;
}

void playerClass::setNrPolysgons(int other)
{
	this->polygoner = other;
}

bool playerClass::getNrWeaponBought(int index)
{
	return this->weaponBought[index];
}

void playerClass::setNrWeaponBought(int index, bool other)
{
	this->weaponBought[index] = other;
}

int playerClass::getNrWeaponCost(int index)
{
	return this->weaponCost[index];
}

void playerClass::getMoveMat(XMMATRIX& mat)
{
	mat = moveMat;
}

void playerClass::resetPlayer()
{
	moveVal = 0;
	translation = XMMatrixIdentity();
	transStart = XMMatrixIdentity();

	//movement
	moveValX = 0.0f;
	moveValY = 0.0f;
	moveValZ = 0.0f;
	moveMat = XMMatrixIdentity();
	upSpeed = 0.0f;
	isJumping = false;
	HP = maxHP;
	isAttacking = false;

	isInObjHolder = false;

	hasRing = false;

	magicCast = false;
	magicWasCast = false;
	magicCooldown = 0.0f;

	isHurt = false;

}

void playerClass::setPlayerHP(int x)
{
	this->HP = x;
}

int playerClass::getPlayerHP()
{
	return this->HP;
}

void playerClass::setPlayerHurt(bool x)
{
	this->isHurt = x;
}

void playerClass::setPlayerHurtFromLeft(bool x)
{
	this->hurtFromLeft = x;
}

void playerClass::setPlayerHurtFromRight(bool x)
{
	this->hurtFromRight = x;
}

bool playerClass::getPlayerHurt()
{
	return this->isPlayerHurt;
}

void playerClass::updateAnimation(double dt)
{
	
	if (currentTime > timeBetweenFrames)
	{
		currentFrame++;
		if (currentFrame > frameCount)
		{
			currentFrame = 1;
			if (attacking == false)
			{
				if (idle == true || running == true)
					nrOfLoops++;
			}
			
			if (attacking == true)
			{
				attacking = false;
				isHit = true;
			}
			
		}
		
		if (nrOfLoops == 3 && currentFrame == frameCount)
		{
			currentFrame++;
			nrOfLoops = 0;
		}
		currentTime = 0;
	}

	currentTime+= 1 * dt;
}

bool playerClass::getFlipped()
{
	return this->flipped;
}

int playerClass::getFrameCount()
{
	return this->frameCount;
}

int playerClass::getCurrentFrame()
{
	return this->currentFrame;
}

int playerClass::getCurrentAnimation()
{
	return this->currentAnimation;
}

float playerClass::getAnimationTime()
{
	return this->animationTime;
}

float playerClass::getcurrentTime()
{
	return this->currentTime;
}

void playerClass::setAnimation(int animation)
{
	this->currentAnimation = animation;
}

weaponClass * playerClass::getWeapon()
{
	switch (this->getWeaponType()) {
		case 0:
			/*OutputDebugString(L"\BASIC\n");*/
			return this->weapon1;
			break;
		case 1:
			/*OutputDebugString(L"\nGOLD\n");*/
			return this->weapon2;
			break;
		case 2:
			/*OutputDebugString(L"\nMAGIC\n");*/
			return this->weapon3;
			break;
		case 3:
			/*OutputDebugString(L"\nBLOOD\n");*/
			return this->weapon4;
			break;
		case 4:
			/*OutputDebugString(L"\nDARK\n");*/
			return this->weapon5;
			break;
	}
}
