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
	isActive = true;
	checkIfObjHolder = false;
	HP = 3;
	isHurt = false;
	hurtCooldown = 0;

	upSpeed = 0;

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

void enemyClass::setLengthBetween(float length1, float length2)
{
	this->lengthBetween1 = length1;
	this->lengthBetween2 = length2;
}

void enemyClass::updateInteraction(playerClass player)
{
	XMMATRIX playerMoveMat;
	playerMoveMat = player->getMoveMat(playerMoveMat);


	lengthBetween1 = XMVectorGetX(XMVector3Transform(this->getObj()->getPosition(), moveMat)) - XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), player->getMoveMat()));
	lengthBetween2 = XMVectorGetX(XMVector3Transform(player->getObj()->getPosition(), player->getMoveMat())) - XMVectorGetX(XMVector3Transform(this->getObj()->getPosition(), moveMat));
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
		//går vänster

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
		//går höger

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

//void enemyClass::setTranslation(float x)
//{
//	oldMoveValX = moveValX;
//	translation = XMMatrixTranslation(x, 0.0f, 0.0f);
//	moveValX = x;
//}

objectClass* enemyClass::getObj()
{
	return this->obj;
}

//void enemyClass::getTranslationMat(XMMATRIX & other)
//{
//	other = this->translation;
//}

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


//void enemyClass::setMove(float x)
//{
//	moveVal -= x;
//}


XMVECTOR enemyClass::getTriggerCheck()
{
	return this->triggerCheck;
}

//void enemyClass::updateFalling(double dt)
//{
//	oldMoveValY = temptest;
//	temptest += -10.5 * dt;
//	
//	this->translationInY = XMMatrixTranslation(0.0f, temptest, 0.0f);
//}
//
//void enemyClass::getFallingMat(XMMATRIX & other)
//{
//	other = this->translationInY;
//}


