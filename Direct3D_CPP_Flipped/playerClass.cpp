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
	frameCount = 3;
	currentFrame = 2;
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

	setStartMat(0.0f);

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
	
}

void playerClass::setTranslation(float x)
{
	translation = XMMatrixTranslation(x, 0.0f, 0.0f);
	//moveVal = x;
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

void playerClass::setStartMat(float x)
{
	this->transStart = XMMatrixTranslation(x, 0.0f, 0.0f);
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

void playerClass::handleMovement(float dt, bool collisionCheckTop, bool collisionCheckLeft, bool collisionCheckRight, bool collisionCheckBot)
{

	justJumped = false;
	moveValY += upSpeed * dt;

	input->readKeyboard(dt);
	if (this->input->isAPressed() && !collisionCheckLeft)
	{
		moveValX += -10.0f * dt;
		//OutputDebugString(L"func move left called");
		if (this->flipped == false)
		{
			flipped = true;
		}
	}
	
	if (this->input->isDPressed() && !collisionCheckRight)
	{
		moveValX += 10.0f * dt;
		//OutputDebugString(L"func move right called");
		if (this->flipped == true)
		{
			flipped = false;
		}
	}
	



	if (this->input->isSpacePressed() && !collisionCheckTop)
	{
		if (!isJumping)
		{
			upSpeed = 30.5f;
			//OutputDebugString(L"upSpeed set");
			justJumped = true;
		}
		isJumping = true;
	}



	if (!this->input->isSpacePressed() && upSpeed > 15)
		upSpeed -= upSpeed - (upSpeed * 0.99);

	if (collisionCheckTop && upSpeed > 0)
		upSpeed = 0;


	if (!collisionCheckBot && upSpeed > -1.0f)
	{
		upSpeed += (-50 * dt) - moveValY * dt;
		isJumping = true;
	}
	else if (!collisionCheckBot) //upSpeed less than -1.0f;
	{
		upSpeed += (-50 * dt) - -upSpeed * dt;
	}
	else if (isJumping && !justJumped)
	{
		upSpeed = 0.0f;
		isJumping = false;
		//OutputDebugString(L"JUMP SET FALSE");
	}


	moveMat = XMMatrixTranslation(moveValX, moveValY, 0.0f);

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

float playerClass::getAnimationTime()
{
	return this->animationTime;
}

float playerClass::getcurrentTime()
{
	return this->currentTime;
}
