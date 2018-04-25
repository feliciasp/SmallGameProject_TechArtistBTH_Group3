#pragma once
#ifndef PICKUPCLASS_H
#define PICKUPCLASS_H

#include "objectClass.h"

class pickupClass
{
public:
	pickupClass();
	pickupClass(const pickupClass& other);
	~pickupClass();

	bool initlialize(ID3D11Device* device, const char* filename);
	void shutdown();

	objectClass* getObj();

	bool getIsDestry();
	void setIsDestroy(bool check);

	void setStartMat(float x);
	void setTranslationMatStart(XMMATRIX& other);
	void getTranslationMatStart(XMMATRIX& other);
	void resetPickup();

	bool getCheckIfObjHolder();
	void setCheckIfObjHolder(bool check);

	void updateAnimation(double dt);
	int getFrameCount();
	int getCurrentFrame();

private:
	objectClass * obj;
	bool isDestroy;
	XMMATRIX transStart;
	bool checkIfSetToObjHolder;

	int frameCount;
	int currentFrame;
	float currentTime;
	float animationSpeed;
};


#endif