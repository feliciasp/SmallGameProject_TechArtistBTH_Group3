#include "playerClass.h"

playerClass::playerClass()
{
	obj = 0;
	moveVal = 0;
	input = 0;

	translation = XMMatrixIdentity();
	transStart = XMMatrixIdentity();
	triggerCheck = { 4.0f, 0.0f, 0.0f };

	HP = 3;
	//movement
	moveValX = 0.0f;
	moveValY = 0.0f;
	moveValZ = 0.0f;
	moveMat = XMMatrixIdentity();
	upSpeed = 0.0f;
	isJumping = false;
	justJumped = false;
	flipped = false;

	isPlayerHurt = false;
	frameCount = 2;

	

	isAttacking = false;

	currentFrame = 1;
	currentAnimation = 1;
	currentTime = 0;

	idle = true;
	startedRunning = false;
	running = false;
	startedJumping = false;
	jumping = false;
	startedFalling = false;
	falling = false;
	animationSpeed = 250;
	nrOfLoops = 0;
}

playerClass::playerClass(const playerClass & other)
{
}

playerClass::~playerClass()
{
}

bool playerClass::initlialize(ID3D11Device* device, const char* filename, HINSTANCE hInstance, HWND hwnd)
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
	result = input->initialize(hInstance, hwnd);
	if (!result)
	{
		MessageBox(NULL, L"Error init enemy obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	weapon = new weaponClass;
	if (!weapon)
	{
		MessageBox(NULL, L"Error create object weapon",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
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
	if (weapon)
	{
		weapon->shutdown();
		delete weapon;
		weapon = 0;
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

XMVECTOR playerClass::getTriggerCheck()
{
	return this->triggerCheck;
}

void playerClass::handleMovement(double dt)
{

	oldMoveValX = moveValX;
	oldMoveValY = moveValY;

	if (dt > 20)
		dt = 0;

	idle = true;


	justJumped = false;
	moveValY += upSpeed * dt;


	currentAnimation = 1;
	frameCount = 2;
	animationSpeed = 250;

	input->readKeyboard(dt);
	if (this->input->isAPressed())
	{
		moveValX += -10.0f * dt;
		if (running == false)
		{
			currentTime = 0;
			currentFrame = 1;
		}
		currentAnimation = 2;
		frameCount = 8;
		animationSpeed = 100;
		idle = false;
		running = true;
		//OutputDebugString(L"func move left called");
		if (this->flipped == false)
		{
			flipped = true;

		}
	}
	
	if (this->input->isDPressed())
	{
		moveValX += 10.0f * dt;
		if (running == false)
		{
			currentTime = 0;
			currentFrame = 1;
		}
		currentAnimation = 2;
		frameCount = 8;
		animationSpeed = 100;
		idle = false;
		running = true;
		//OutputDebugString(L"func move right called");
		if (this->flipped == true)
		{
			flipped = false;
		}
	}
	

	if (this->input->isSpacePressed())
	{
		if (!isJumping)
		{
			upSpeed = 23.5f;
			//OutputDebugString(L"upSpeed set");
			justJumped = true;
			currentFrame = 1;
			currentTime = 0;
		}
		running = false;
		isJumping = true;
		idle = false;
		jumping = true;
		currentAnimation = 3;
		frameCount = 2;
		animationSpeed = 250;
	}

	if (!this->input->isSpacePressed() && upSpeed > upSpeed * 0.5)
		upSpeed -= upSpeed - (upSpeed * 0.99);


	if (upSpeed > -1.0f)
	{
		upSpeed += (-50 * dt) - moveValY * dt;
		isJumping = true;
	}
	else if (upSpeed < -1.0f) //upSpeed less than -1.0f;
	{
		if (falling == false)
		{
			currentTime = 0;
			currentFrame = 1;
		}
		upSpeed += (-50 * dt) - -upSpeed * dt;
		currentAnimation = 4;
		frameCount = 2;
		idle = false;
		running = false;
		falling = true;
	}
	
	if (running == true && idle == true)
	{
		running = false;
		currentTime = 0;
		currentFrame = 1;
		animationSpeed = 250;
	}

	if (falling == true && idle == true)
	{
		falling = false;
		currentTime = 0;
		currentFrame = 1;
		animationSpeed = 250;
	}

	moveMat = XMMatrixTranslation(moveValX, moveValY+8, 0.0f);

}

void playerClass::checkCollisions(bool top, bool left, bool right, bool bot)
{
	if (top)
	{
		moveValY = oldMoveValY;
		if (upSpeed > 0)
			upSpeed = 0;
	}

	if (bot)
	{
		moveValY = oldMoveValY;
		isJumping = false;
		upSpeed = 0;
		idle = true;
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
	if (this->input->isOPressed())
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
	checkIfAttacking();
	if (this->isAttacking)
	{
		return true;
	}
	else
	{
		return false;
	}
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
	HP = 3;
	isAttacking = false;
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
	this->isPlayerHurt = x;
}

bool playerClass::getPlayerHurt()
{
	return this->isPlayerHurt;
}

void playerClass::updateAnimation()
{
	if (currentTime > animationSpeed)
	{
		currentFrame++;
		if (currentFrame > frameCount)
		{
			currentFrame = 1;
			if(idle == true || running == true)
				nrOfLoops++;
		}
			
		if (nrOfLoops == 3 && currentFrame == frameCount)
		{
			currentFrame++;
			nrOfLoops = 0;
		}
		currentTime = 0;
	}

	currentTime++;
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

weaponClass * playerClass::getWeapon()
{
	return this->weapon;
}
