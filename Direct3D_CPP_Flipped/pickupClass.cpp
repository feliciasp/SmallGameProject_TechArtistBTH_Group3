#include "pickupClass.h"

pickupClass::pickupClass()
{
	obj = 0;
	transStart = XMMatrixIdentity();
	isDestroy = false;
	checkIfSetToObjHolder = false;

	frameCount = 8;
	currentFrame = 2;
	currentAnimation = 1;
	animationCount = 1;
	currentTime = 0;
	animationSpeed = 0.2;


	isAnimated = true;
	isRing = false;

}

pickupClass::pickupClass(const pickupClass & other)
{
	
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
	srand(time(NULL));
	ringType = rand() % 3;

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
	if (pickupType == 3)
	{
		isAnimated = false;
		if (ringType == 0)
		{
			currentFrame = 2;
			obj->setCurrentFrame(2);
		}

		if (ringType == 1)
		{
			currentFrame = 1;
			obj->setCurrentFrame(1);
		}

		if (ringType == 2)
		{
			currentFrame = 3;
			obj->setCurrentFrame(3);
		}
		
		if (ringType == 3)
		{
			currentFrame = 0;
			obj->setCurrentFrame(0);
		}
	}

	else if (pickupType == 4)
	{
		isAnimated = false;
		currentFrame = 1;
		obj->setCurrentFrame(1);
	}

	else
		isAnimated = true;

	if (isAnimated)
	{
		if (pickupType == 6)
		{
			animationSpeed = 0.08;
		}
		if (pickupType == 9)
		{
			animationSpeed = 0.8;
		}
		if (currentTime > animationSpeed)
		{
			currentTime = 0;
			currentFrame++;
			obj->setCurrentFrame(currentFrame);
			if (currentFrame > frameCount)
			{
				currentFrame = 1;
				obj->setCurrentFrame(1);
			}
		}
		currentTime += 1 * dt;
	}

}

void pickupClass::setFrameCount(int frameCount)
{
	this->frameCount = frameCount;
	obj->setFrameCount(frameCount);
}

int pickupClass::getFrameCount()
{
	return this->frameCount;
}

int pickupClass::getCurrentFrame()
{
	return this->currentFrame;
}

void pickupClass::setCurrentAnimation(int currentAnimation)
{
	this->currentAnimation = currentAnimation;
	obj->setCurrentAnimation(currentAnimation);
}

int pickupClass::getCurrentAnimation()
{
	return this->currentAnimation;
}

void pickupClass::setAnimationCount(int animationCount)
{
	this->animationCount = animationCount;
	obj->setAnimationCount(animationCount);
}

int pickupClass::getAnimationCount()
{
	return this->animationCount;
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
