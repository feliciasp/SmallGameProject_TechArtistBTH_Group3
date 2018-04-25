#include "enemyClass.h"

enemyClass::enemyClass()
{
	temptest = 3;
	obj = 0;
	moveVal = 0;
	translation = XMMatrixIdentity();
	transStart = XMMatrixIdentity();
	triggerCheck = { 10.5f, 0.0f, 0.0f};
	isActive = true;
	checkIfObjHolder = false;
	HP = 3;
	isHurt = false;
	fakeTimer = 0;


	isFacingRight = true;
	useRotation = false;
}

enemyClass::enemyClass(const enemyClass & other)
{

}

enemyClass::~enemyClass()
{
}

bool enemyClass::initlialize(ID3D11Device* device, const char* filename)
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
		MessageBox(NULL, L"Error init enemy obj3",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	obj->setType(3);

	setStartMat(8.0f);

	return true;
}

void enemyClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
}

void enemyClass::setTriggerVector(XMVECTOR x)
{
	this->triggerVector = x;
}

XMVECTOR enemyClass::getTriggerVector()
{
	return this->triggerVector;
}

void enemyClass::resetEnemy()
{
	moveVal = 0;
	translation = XMMatrixIdentity();
	isActive = true;
	checkIfObjHolder = false;
	HP = 3;
	isHurt = false;
	fakeTimer = 0;

	isFacingRight = true;
	useRotation = false;
}

bool enemyClass::getCheckIfObjHolder()
{
	return this->checkIfObjHolder;
}

void enemyClass::setCheckIfObjHolder(bool other)
{
	this->checkIfObjHolder = other;
}

void enemyClass::setIsActive(bool check)
{
	this->isActive = check;
}

bool enemyClass::getIsActive()
{
	return this->isActive;
}

void enemyClass::setEnemyHP(int x)
{
	this->HP = x;
}

int enemyClass::getEnemyHP()
{
	return this->HP;
}

bool enemyClass::hurtState()
{
	if (this->isHurt == false && fakeTimer == 0)
	{
		this->isHurt = true;
		fakeTimer = 150;
		return true;
	}
	else
	{
		return false;
	}
}

void enemyClass::timeCountdown()
{
	if (this->fakeTimer != 0)
	{
		this->fakeTimer -= 1;
		this->isHurt = false;
	}
}

void enemyClass::setFacing(bool other)
{
	this->isFacingRight = other;
}

bool enemyClass::getFacing()
{
	return this->isFacingRight;
}

void enemyClass::setRoationCheck(bool other)
{
	this->useRotation = other;
}

bool enemyClass::getRoationCheck()
{
	return this->useRotation;
}

void enemyClass::checkCollisions(bool top, bool left, bool right, bool bot)
{
	if (top)
	{
		temptest = oldMoveValY;
	}

	if (bot)
	{
		temptest = oldMoveValY;
	}

	/*if (left)
	{
		moveValX = oldMoveValX;
	}
	if (right)
	{
		moveValX = oldMoveValX;
	}*/

	this->translationInY = XMMatrixTranslation(0.0f, temptest, 0.0f);
}

void enemyClass::setEnemyHurt(bool check)
{
	this->isHurt = check;
}

bool enemyClass::getEnemyHurt()
{
	return this->isHurt;
}



void enemyClass::setTranslation(float x)
{
	translation = XMMatrixTranslation(x, 0.0f, 0.0f);
}

objectClass* enemyClass::getObj()
{
	return this->obj;
}

void enemyClass::getTranslationMat(XMMATRIX & other)
{
	other = this->translation;
}

void enemyClass::getTranslationMatStart(XMMATRIX & other)
{
	other = this->transStart;
}

void enemyClass::setStartMat(float x)
{
	this->transStart = XMMatrixTranslation(x, 0.0f, 0.0f);
}

float enemyClass::getMove()
{
	return moveVal;
}

void enemyClass::setMove(float x)
{
	moveVal -= x;
}

void enemyClass::resetMove()
{

	moveVal = 0;
}

XMVECTOR enemyClass::getTriggerCheck()
{
	return this->triggerCheck;
}

void enemyClass::updateFalling(double dt)
{
	oldMoveValY = temptest;
	temptest += -10.5 * dt;
	
	this->translationInY = XMMatrixTranslation(0.0f, temptest, 0.0f);
}

void enemyClass::getFallingMat(XMMATRIX & other)
{
	other = this->translationInY;
}


