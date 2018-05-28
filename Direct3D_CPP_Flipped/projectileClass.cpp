#include "projectileClass.h"

projectileClass::projectileClass()
{
	obj = 0;
	isDestroyed = false;
	checkIfSetToObjHolder = false;
	transStart = XMMatrixIdentity();
	transX = XMMatrixIdentity();
	goesRight = true;
	moveValX = 0.0f;
	moveValY = 0.0f;
	lifeTime = 0.0f;

	bboxMaxLeft = { 0.0f,0.0f };
	bboxMinLeft = { 0.0f, 0.0f };
	bboxMaxRight = { 0.0f,0.0f };
	bboxMinRight = { 0.0f, 0.0f };

	currentFrame = 1;
	frameCount = 4;
	currentAnimation = 1;
	animationCount = 1;
	animationSpeed = 0.1f;
	currentTime = 0.0f;
}

projectileClass::projectileClass(const projectileClass & other)
{
}

projectileClass::~projectileClass()
{
}

bool projectileClass::initlialize(ID3D11Device * device, const char * filename)
{
	bool result;
	obj = new objectClass;

	if (!obj)
	{
		MessageBox(NULL, L"Error create projectile obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = obj->initlialize(device, filename);
	if (!result)
	{
		MessageBox(NULL, L"Error init projectile obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	obj->setType(5);

	return true;
}

void projectileClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
}

void projectileClass::resetFireEnemy()
{
	transStart = XMMatrixIdentity();
	transX = XMMatrixIdentity();
	moveValX = 0.0f;
	moveValY = 0.0f;
}

objectClass * projectileClass::getObj()
{
	return this->obj;
}

void projectileClass::setIsDestroyed(bool check)
{
	this->isDestroyed = check;
}

bool projectileClass::getIsDestroyed()
{
	return this->isDestroyed;
}

void projectileClass::setTranslationMatStart(XMMATRIX & other)
{
	this->transStart = other;
}

void projectileClass::getTranslationMatStart(XMMATRIX & other)
{
	other = this->transStart;
}

void projectileClass::setTransX(XMMATRIX & other)
{
	this->transX = other;
}

void projectileClass::getTransX(XMMATRIX & other)
{
	other = this->transX;
}

void projectileClass::setBoundingBoxMaxLeft(XMVECTOR other)
{
	this->bboxMaxLeft = other;
}

void projectileClass::setBoundingBoxMinLeft(XMVECTOR other)
{
	this->bboxMinLeft = other;
}

void projectileClass::setBoundingBoxMaxRight(XMVECTOR other)
{
	this->bboxMaxRight = other;
}

void projectileClass::setBoundingBoxMinRight(XMVECTOR other)
{
	this->bboxMinRight = other;
}

XMVECTOR projectileClass::getBoundingBoxMaxLeft()
{
	return this->bboxMaxLeft;
}

XMVECTOR projectileClass::getBoundingBoxMinLeft()
{
	return this->bboxMinLeft;
}

XMVECTOR projectileClass::getBoundingBoxMaxRight()
{
	return this->bboxMaxRight;
}

XMVECTOR projectileClass::getBoundingBoxMinRight()
{
	return this->bboxMinRight;
}

void projectileClass::moveProjY(double dt)
{

	moveValY += -20.0f * dt;
	
	transX = transStart * XMMatrixTranslation(0.0f, moveValY, 0.0f);
}

void projectileClass::moveProjectile(double dt)
{
	if (projectileType == 0)
	{
		if (goesRight)
		{
			moveValX += 20.0f * dt;
		}
		else
		{
			moveValX += -20.0f * dt;
		}
	}
	if (projectileType == 1)
	{
		if (goesRight)
		{
			moveValX += 16.0f * dt;
		}
		else
		{
			moveValX += -16.0f * dt;
		}
	}
	transX = transStart * XMMatrixTranslation(moveValX, 0.0f, 0.0f);
}

void projectileClass::moveRrojToCertainDestination(double dt)
{
	float dirX = XMVectorGetX(transDestination) - XMVectorGetX(transDestinationStart);
	float dirY = XMVectorGetY(transDestination) - XMVectorGetY(transDestinationStart);

	XMVECTOR dir = { dirX, dirY };
	XMVector2Normalize(dir);

	float normDirX = XMVectorGetX(dir);
	float normaDirY = XMVectorGetY(dir);
  
	moveValX += normDirX * dt;
	moveValY += normaDirY * dt;

	transX = transStart * XMMatrixTranslation(moveValX, moveValY, 0.0f);
}

void projectileClass::setDestinationPoint(XMVECTOR other)
{
	this->transDestination = other;
}

void projectileClass::setDestinationStart(XMVECTOR other)
{
	this->transDestinationStart = other;
}


void projectileClass::resetProjectile()
{
	//isDestroyed = false;
	checkIfSetToObjHolder = false;
	transStart = XMMatrixIdentity();
	transX = XMMatrixIdentity();
	goesRight = true;
	moveValX = 0.0f;
	lifeTime = 0.0f;
	moveValY = 0.0f;
}

void projectileClass::setProjectileType(int value)
{
	this->projectileType = value;
}

int projectileClass::getProjectileType()
{
	return this->projectileType;
}

void projectileClass::setCheckIfObjHolder(bool check)
{
	this->checkIfSetToObjHolder = check;
}

bool projectileClass::getCheckIfObjHolder()
{
	return this->checkIfSetToObjHolder;
}

void projectileClass::setGoesRight(bool check)
{
	this->goesRight = check;
}

bool projectileClass::getGoesRight()
{
	return this->goesRight;
}

void projectileClass::setLifeTime(double value)
{
	this->lifeTime += value;
}

double projectileClass::getLifeTime()
{
	return this->lifeTime;
}

void projectileClass::updateAnimation(double dt)
{
	if (currentTime > animationSpeed)
	{
		currentTime = 0.0f;
		currentFrame++;
		if (currentFrame > frameCount)
		{
			currentFrame = 1;
		}
	}
	currentTime += 1 * dt;
	obj->setCurrentFrame(currentFrame);
}

int projectileClass::getCurrentFrame()
{
	return this->currentFrame;
}

void projectileClass::setFrameCount(int other)
{
	this->frameCount = other;
	obj->setFrameCount(other);
}

int projectileClass::getFrameCount()
{
	return this->frameCount;
}

void projectileClass::setCurrentAnimation(int other)
{
	this->currentAnimation = other;
	obj->setCurrentAnimation(other);
}

int projectileClass::getCurrentAnimation()
{
	return this->currentAnimation;
}

void projectileClass::setAnimationCount(int other)
{
	this->animationCount = other;
	obj->setAnimationCount(other);
}

int projectileClass::getAnimationCount()
{
	return this->animationCount;
}
