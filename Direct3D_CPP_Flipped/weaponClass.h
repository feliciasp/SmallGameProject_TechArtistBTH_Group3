#pragma once
#ifndef WEAPONCLASS_H
#define WEAPONCLASS_H 

#include <DirectXMath.h>
#include "collisionClass.h"

using namespace DirectX;

class weaponClass
{
public:
	weaponClass();
	weaponClass(weaponClass& other);
	~weaponClass();
	
	void shutdown();

	void setBboxMaxWeapon(XMVECTOR vector);
	void setBboxMinWeapon(XMVECTOR vector);

	XMVECTOR getBboxMaxWeapon();
	XMVECTOR getBboxMinWeapon();

	collisionClass* getCollisionClass();

public:

	collisionClass* collision;

	XMVECTOR bboxMax;
	XMVECTOR bboxMin;
	int tonsOfDmg;
};

#endif // !WEAPONCLASS_H
