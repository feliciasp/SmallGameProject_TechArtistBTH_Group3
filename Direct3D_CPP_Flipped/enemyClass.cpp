#include "enemyClass.h"

enemyClass::enemyClass()
{
	temptest = 3;
	obj = 0;
	moveVal = 0;
	translation = XMMatrixIdentity();
	transStart = XMMatrixIdentity();
	masterMoveMat = XMMatrixIdentity();
	tranlsationInXMatrix = XMMatrixIdentity();
	triggerCheck = { 10.5f, 0.0f, 0.0f};
	rangeCheck = { 4.0f, 0.0f, 0.0f };
	isActive = true;
	checkIfObjHolder = false;
	HP = 3;
	isAttack = false;
	isHurt = false;
	attackTimer = 1.0f;
	hurtTimer = 0.3f;

	isFacingRight = true;
	useRotation = false;

	isHit = false;

	/*collidingX = false;*/

	//VAPEN
	bboxMinRight = { 0.0f, 0.0f };
	bboxMaxRight = { 0.0f,0.0f };
	bboxMinLeft = { 0.0f, 0.0f };
	bboxMaxLeft = { 0.0f,0.0f };
	tonsOfDmg = 0;
	hurt = 0;
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

	startPos = {5.0f, 0.0f, 0.0f};
	setStartMat(5.0f);

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

void enemyClass::setRangeVector(XMVECTOR x)
{
	this->rangeVector = x;
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
	isAttack = false;
	attackTimer = 1.0f;
	hurtTimer = 0.3f;

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
	if (this->isHurt == false && hurtTimer <= 0)
	{
		this->isHurt = true;
		hurtTimer = 0.3f;
		this->hurt = 1;
		return true;
	}
	else
	{
		return false;
	}
}

void enemyClass::timeCountdown(float dt)
{
	this->hurtTimer -= 1 * dt;
	if (this->hurtTimer <= 0)
	{
		this->isHurt = false;
		this->hurt = 0;
	}
}

bool enemyClass::attackCooldown()
{
	if (this->isAttack == false && attackTimer <= 0)
	{
		this->isAttack = true;
		attackTimer = 1.0f;
		return true;
	}
	else
	{
		return false;
	}
}

void enemyClass::updateAttackCooldownTimer(float dt)
{
	this->attackTimer -= 1 * dt;
	if (this->attackTimer <= 0)
	{
		this->isAttack = false;
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

void enemyClass::checkIfAttacking()
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

bool enemyClass::getIfAttack()
{
	return isHit;
}

int enemyClass::getAttackCooldown()
{
	return this->attackTimer;
}

void enemyClass::checkCollisionsY(bool top, bool bot)
{
	if (top)
	{
		temptest = oldMoveValY;
	}

	if (bot)
	{
		temptest = oldMoveValY;
	}

	this->translationInY = XMMatrixTranslation(0.0f, temptest, 0.0f);
}
void enemyClass::checkCollisionsX(bool left, bool right)
{
	collidingRight = false;
	collidingLeft = false;

	if (left && isFacingRight)
	{
		collidingLeft = true;
	}
	if (right && !isFacingRight)
	{
		collidingRight = true;
	}
}

//bool enemyClass::getCollidingX()
//{
//	return this->collidingX;
//}


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
	if(!collidingRight && x < 0)
		moveVal -= x;
	if (!collidingLeft && x > 0)
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

XMVECTOR enemyClass::getRangeVector()
{
	return this->rangeCheck;
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


//VAPEN

void enemyClass::setBboxMaxWeaponRight(XMVECTOR vector)
{
	this->bboxMaxRight = vector;
}

void enemyClass::setBboxMinWeaponRight(XMVECTOR vector)
{
	this->bboxMinRight = vector;
}

XMVECTOR enemyClass::getBboxMaxWeaponRight()
{
	return this->bboxMaxRight;
}

XMVECTOR enemyClass::getBboxMinWeaponRight()
{
	return this->bboxMinRight;
}

void enemyClass::setBboxMaxWeaponLeft(XMVECTOR vector)
{
	this->bboxMaxLeft = vector;
}

void enemyClass::setBboxMinWeaponLeft(XMVECTOR vector)
{
	this->bboxMinLeft = vector;
}

XMVECTOR enemyClass::getBboxMaxWeaponLeft()
{
	return this->bboxMaxLeft;
}

XMVECTOR enemyClass::getBboxMinWeaponLeft()
{
	return this->bboxMinLeft;
}

XMVECTOR enemyClass::getStartPos()
{
	return this->startPos;
}

int enemyClass::getHurt()
{
	return this->hurt;
}

void enemyClass::getMasterMovementEnemy(XMMATRIX & other)
{
	other = this->masterMoveMat;
}

void enemyClass::setMasterMovementEnemy(XMMATRIX & other)
{
	this->masterMoveMat = other;
}

void enemyClass::getEnemyTranslationMatrix(XMMATRIX & other)
{
	other = this->tranlsationInXMatrix;
}

void enemyClass::setEnemyTranslationMatrix(XMMATRIX & other)
{
	this->tranlsationInXMatrix = other;
}
