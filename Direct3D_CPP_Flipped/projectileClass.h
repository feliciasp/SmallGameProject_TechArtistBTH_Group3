#pragma once
#ifndef PROJECTILECLASS_H
#define PROJECTILECLASS_H

#include "objectClass.h"

class projectileClass
{
public:
	projectileClass();
	projectileClass(const projectileClass & other);
	~projectileClass();

	bool initlialize(ID3D11Device* device, const char* filename);
	void shutdown();

	objectClass* getObj();

	void setIsDestroyed(bool check);
	bool getIsDestroyed();

	void setTranslationMatStart(XMMATRIX& other);
	void getTranslationMatStart(XMMATRIX& other);

	void setTransX(XMMATRIX& other);
	void getTransX(XMMATRIX& other);

	void moveProjectile(double dt);

	void resetProjectile();

	void setCheckIfObjHolder(bool check);
	bool getCheckIfObjHolder();

	void setGoesRight(bool check);
	bool getGoesRight();

	void setLifeTime(double value);
	double getLifeTime();

private:
	objectClass* obj;
	bool isDestroyed;
	XMMATRIX transStart;
	bool checkIfSetToObjHolder;
	bool goesRight; //true if goes to right of screen.
	
	float moveValX;
	XMMATRIX transX;
	double lifeTime;
};

#endif
