#include "pickupClass.h"

pickupClass::pickupClass()
{
	obj = 0;
	transStart = XMMatrixIdentity();
	isDestroy = false;
	checkIfSetToObjHolder = false;

	frameCount = 8;
	currentFrame = 2;
	currentTime = 0;
	animationSpeed = 50;

	isAnimated = true;
	isRing = false;

}

pickupClass::pickupClass(const pickupClass & other)
{
	//objectClass * obj;
	
	/*pickupClass *newPickup = new pickupClass;
	newPickup->obj = new objectClass;
	newPickup->transStart = other.transStart;
	newPickup->isDestroy = other.isDestroy;
	newPickup->checkIfSetToObjHolder = other.checkIfSetToObjHolder;
	newPickup->frameCount = other.frameCount;
	newPickup->currentFrame = other.currentFrame;
	newPickup->animationSpeed = other.animationSpeed;
	newPickup->isAnimated = other.isAnimated;
	newPickup->isRing = other.isRing;

	newPickup->ringType = other.ringType;
	newPickup->pickupType = other.pickupType;*/
	
}

pickupClass::~pickupClass()
{
}

void pickupClass::clone(const pickupClass& other)
{
	obj = new objectClass;
	obj->clone(*other.obj);
	obj->setType(4);
}

bool pickupClass::initlialize(ID3D11Device * device, const char* filename)
{
	bool result;
	obj = new objectClass;

	if (!obj)
	{
		MessageBox(NULL, L"Error create bakcground obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = obj->initlialize(device, filename);
	if (!result)
	{
		MessageBox(NULL, L"Error init background obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	setStartMat(-3.0f);
	obj->setType(4);
	return true;
}

void pickupClass::shutdown()
{
	if (obj)
	{
		obj->shutdown();
		delete obj;
		obj = 0;
	}
}

objectClass * pickupClass::getObj()
{
	return this->obj;
}

bool pickupClass::getIsDestry()
{
	return this->isDestroy;
}

void pickupClass::setIsDestroy(bool check)
{
	this->isDestroy = check;
}

void pickupClass::setStartMat(float x)
{
	this->transStart = XMMatrixTranslation(x - 10, 1.5f, 0.0f);
}

void pickupClass::setTranslationMatStart(XMMATRIX & other)
{
	this->transStart = other;
}

void pickupClass::getTranslationMatStart(XMMATRIX & other)
{
	other = this->transStart;
}

void pickupClass::resetPickup()
{
	isDestroy = true;
}


bool pickupClass::getCheckIfObjHolder()
{
	return this->checkIfSetToObjHolder;
}

void pickupClass::setCheckIfObjHolder(bool check)
{
	this->checkIfSetToObjHolder = check;
}

void pickupClass::updateAnimation(double dt)
{
	if (isAnimated)
	{
		if (currentTime > animationSpeed * dt)
		{
			currentTime = 0;
			currentFrame++;
			if (currentFrame > frameCount)
			{
				currentFrame = 1;
			}
		}
		currentTime += 1 * dt;
	}
}

int pickupClass::getFrameCount()
{
	return this->frameCount;
}

int pickupClass::getCurrentFrame()
{
	return this->currentFrame;
}

void pickupClass::setPickupType(int other)
{
	this->pickupType = other;
	if (other == 3)
	{
		this->isRing = true;
		this->isAnimated = false;
	}
	else
	{
		this->isRing = false;
		this->isAnimated = true;
	}
		
}

int pickupClass::getPickupType()
{
	return this->pickupType;
}


void pickupClass::setRingType(int other)
{
	this->ringType = other;
}

int pickupClass::getRingType()
{
	return this->ringType;
}
