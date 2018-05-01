#include "enemyClass.h"

enemyClass::enemyClass()
{
	temptest = 3;
	obj = 0;
	moveValX = 0;
	moveValY = 0;
	moveValZ = 0;
	transStart = XMMatrixIdentity();
	triggerCheck = { 10.5f, 0.0f, 0.0f};
	rangeCheck = { 4.0f, 0.0f, 0.0f };
	isActive = true;
	checkIfObjHolder = false;
	HP = 3;
	isAttack = false;
	isHurt = false;

	hurtCooldown = 0;

	upSpeed = 0;

	fakeTimer = 1000;


	isFacingRight = true;
	useRotation = false;

	isHit = false;

	//VAPEN
	bboxMinRight = { 0.0f, 0.0f };
	bboxMaxRight = { 0.0f,0.0f };
	bboxMinLeft = { 0.0f, 0.0f };
	bboxMaxLeft = { 0.0f,0.0f };
	tonsOfDmg = 0;
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


	setStartMat(0.0f, 8.0f);


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
	isActive = true;
	checkIfObjHolder = false;
	HP = 3;
	isHurt = false;

	hurtCooldown = 0;

	isAttack = false;
	fakeTimer = 300;


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
	if (this->isHurt == false && hurtCooldown == 0)
	{
		this->isHurt = true;

		hurtCooldown = 150;

		fakeTimer = 300;

		return true;
	}
	else
	{
		return false;
	}
}

void enemyClass::timeCountdown(double dt)
{
	if (this->hurtCooldown != 0)
	{
		this->hurtCooldown -= 1 * dt;
		this->isHurt = false;
	}
}

bool enemyClass::attackCooldown()
{
	if (this->isAttack == false && fakeTimer <= 0)
	{
		this->isAttack = true;
		fakeTimer = 300;
		return true;
	}
	else
	{
		return false;
	}
}

void enemyClass::updateAttackCooldownTimer()
{
	this->fakeTimer -= 1;
	if (this->fakeTimer <= 0)
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

void enemyClass::setRotationCheck(bool other)
{
	this->useRotation = other;
}

bool enemyClass::getRotationCheck()
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
	return this->fakeTimer;
}

void enemyClass::checkCollisions(bool top, bool left, bool right, bool bot)
{
	if (top)
	{
		moveValY = oldMoveValY;
	}

	if (bot)
	{
		moveValY = oldMoveValY;
	}
	if (left)
	{
		moveValX = oldMoveValX;
	}
	if (right)
	{
		moveValX = oldMoveValX;
	}
	moveMat = XMMatrixTranslation(moveValX, moveValY, 0.0f);
	if (useRotation)
	{
		moveMat = XMMatrixRotationY(-3.1514f) * moveMat;
	}
}


void enemyClass::setEnemyHurt(bool check)
{
	this->isHurt = check;
}

bool enemyClass::getEnemyHurt()
{
	return this->isHurt;
}

void enemyClass::handleMovement(double dt)
{
	oldMoveValX = moveValX;
	oldMoveValY = moveValY;

	if (dt > 20)
		dt = 0;

	//idle = true;
	//justJumped = false;
	moveValY += upSpeed * dt;

	//input->readKeyboard(dt);
	if (lengthBetween1 <= XMVectorGetX(triggerCheck) && lengthBetween1 >= 1.5f)
	{
		//g�r v�nster

		moveValX += -2.5f * dt;
		/*idle = false;
		running = true;*/

		if (this->isFacingRight == true)
			isFacingRight = false;

		if (isFacingRight && turningDelay <= 0)
		{
			useRotation = true;
			turningDelay = 100;
		}
		else if (isFacingRight && turningDelay >= 0)
		{
			turningDelay -= 1;
		}
		else
		{
			useRotation = false;
			isFacingRight = false;
		}
	}
	if (lengthBetween2 <= XMVectorGetX(triggerCheck) && lengthBetween1 <= 1.5f)
	{
		//g�r h�ger

		moveValX += 2.5f * dt;
		/*idle = false;
		running = true;*/
		
		if (!isFacingRight && turningDelay <= 0)
		{
			useRotation = true;
			turningDelay = 100;
		}
		else if (!isFacingRight && turningDelay >= 0)
		{
			turningDelay -= 1;
		}
		else
		{
			useRotation = false;
			isFacingRight = true;
		}
	}


	/*if ()
	{
		if (!isJumping)
		{
			upSpeed = 23.5f;
			justJumped = true;
		}
		isJumping = true;
	}*/

	//if (upSpeed > 1)
	//{
	//	/*running = false;
	//	idle = false;
	//	jumping = true;*/
	//}

	if (upSpeed > -1.0f)
	{
		upSpeed += (-50 * dt) - moveValY * dt;
		/*isJumping = true;*/
	}
	else if (upSpeed < -1.0f) //upSpeed less than -1.0f;
	{
		upSpeed += (-50 * dt) - -upSpeed * dt;
		/*idle = false;
		running = false;
		falling = true;*/
	}

	/*if (this->input->isOPressed())
		if (attacking == false)
			attacking = true;*/

	/*if (attacking == true)
		idle = false;


	if (running == true && idle == true && attacking == false)
		running = false;

	if (falling == true && idle == true && attacking == false)
		falling = false;

	if (jumping == true && idle == true && attacking == false)
		jumping = false;

	if (isHit == true && idle == true)
		isHit = false;*/

	moveMat = XMMatrixTranslation(moveValX, moveValY + 8, 0.0f);
}

objectClass* enemyClass::getObj()
{
	return this->obj;
}

void enemyClass::getTranslationMatStart(XMMATRIX & other)
{
	other = this->transStart;
}

void enemyClass::setStartMat(float x, float y)
{
	this->transStart = XMMatrixTranslation(x, y, 0.0f);
}

void enemyClass::getMoveMat(XMMATRIX other)
{
}

void enemyClass::resetMove()
{
}

XMVECTOR enemyClass::getTriggerCheck()
{
	return this->triggerCheck;
}


XMVECTOR enemyClass::getRangeVector()
{
	return this->rangeCheck;
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
