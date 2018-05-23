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

	void resetFireEnemy();

	objectClass* getObj();

	void setIsDestroyed(bool check);
	bool getIsDestroyed();

	void setTranslationMatStart(XMMATRIX& other);
	void getTranslationMatStart(XMMATRIX& other);

	void setTransX(XMMATRIX& other);
	void getTransX(XMMATRIX& other);

	void setBoundingBoxMaxLeft(XMVECTOR other);
	void setBoundingBoxMinLeft(XMVECTOR other);
	void setBoundingBoxMaxRight(XMVECTOR other);
	void setBoundingBoxMinRight(XMVECTOR other);
	XMVECTOR getBoundingBoxMaxLeft();
	XMVECTOR getBoundingBoxMinLeft();
	XMVECTOR getBoundingBoxMaxRight();
	XMVECTOR getBoundingBoxMinRight();

	void moveProjectile(double dt);
	void moveRrojToCertainDestination(double dt);
	void setDestinationPoint(XMVECTOR other);
	void setDestinationStart(XMVECTOR other);

	void resetProjectile();

	void setProjectileType(int value);
	int getProjectileType();

	void setCheckIfObjHolder(bool check);
	bool getCheckIfObjHolder();

	void setGoesRight(bool check);
	bool getGoesRight();

	void setLifeTime(double value);
	double getLifeTime();

	void updateAnimation(double dt);
	int getCurrentFrame();
	void setFrameCount(int other);
	int getFrameCount();
	void setCurrentAnimation(int other);
	int getCurrentAnimation();
	void setAnimationCount(int other);
	int getAnimationCount();

private:
	objectClass* obj;
	bool isDestroyed;
	XMMATRIX transStart;
	XMVECTOR transDestination;
	XMVECTOR transDestinationStart;
	bool checkIfSetToObjHolder;
	bool goesRight; //true if projectile goes to right of screen.
	int projectileType; //0 = FIREBALL, 1 = FROSTBOLT

	float moveValX;
	float moveValY;
	XMMATRIX transX;
	double lifeTime;

	XMVECTOR bboxMaxLeft;
	XMVECTOR bboxMinLeft;
	XMVECTOR bboxMaxRight;
	XMVECTOR bboxMinRight;

	int currentFrame;
	int frameCount;
	int currentAnimation;
	int animationCount;
	float animationSpeed;
	float currentTime;
};

#endif
