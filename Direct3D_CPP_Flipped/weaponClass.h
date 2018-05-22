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

	void setBboxMaxWeaponRight(XMVECTOR vector);
	void setBboxMinWeaponRight(XMVECTOR vector);

	XMVECTOR getBboxMaxWeaponRight();
	XMVECTOR getBboxMinWeaponRight();

	void setBboxMaxWeaponLeft(XMVECTOR vector);
	void setBboxMinWeaponLeft(XMVECTOR vector);

	int getDamage();
	void setDamage(int dmg);

	XMVECTOR getBboxMaxWeaponLeft();
	XMVECTOR getBboxMinWeaponLeft();

	collisionClass* getCollisionClass();

public:
	collisionClass* collision;

	XMVECTOR bboxMaxLeft;
	XMVECTOR bboxMinLeft;

	XMVECTOR bboxMaxRight;
	XMVECTOR bboxMinRight;
	int tonsOfDmg;
};

#endif // !WEAPONCLASS_H
