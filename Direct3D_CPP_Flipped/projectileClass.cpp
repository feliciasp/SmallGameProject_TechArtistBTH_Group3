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
	lifeTime = 0.0f;
	bboxMinRight = { 0.0f, 0.0f };
	bboxMaxRight = { 0.0f,0.0f };
	bboxMinLeft = { 0.0f, 0.0f };
	bboxMaxLeft = { 0.0f,0.0f };
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

void projectileClass::moveProjectile(double dt)
{
	if (goesRight)
	{
		moveValX += 15.0f * dt;
	}
	else 
	{
		moveValX += -15.0f * dt;
	}

	transX = transStart * XMMatrixTranslation(moveValX, 0.0f, 0.0f);
}

void projectileClass::resetProjectile()
{
	isDestroyed = false;
	checkIfSetToObjHolder = false;
	transStart = XMMatrixIdentity();
	transX = XMMatrixIdentity();
	goesRight = true;
	moveValX = 0.0f;
	lifeTime = 0.0f;
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
