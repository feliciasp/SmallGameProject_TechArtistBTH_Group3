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
	void getTranslationMatStart(XMMATRIX& other);
	void resetPickup();

	bool getCheckIfObjHolder();
	void setCheckIfObjHolder(bool check);

private:
	objectClass * obj;
	bool isDestroy;
	XMMATRIX transStart;
	bool checkIfSetToObjHolder;
};


#endif