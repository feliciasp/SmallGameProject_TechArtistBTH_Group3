#include "weaponClass.h"

weaponClass::weaponClass()
{
	bboxMinRight = { 0.0f, 0.0f };
	bboxMaxRight = { 0.0f,0.0f };
	bboxMinLeft = { 0.0f, 0.0f };
	bboxMaxLeft = { 0.0f,0.0f };
	tonsOfDmg = 0;
}



weaponClass::weaponClass(weaponClass & other)
{
}

weaponClass::~weaponClass()
{
}

void weaponClass::shutdown()
{
	collision = 0;
}

void weaponClass::setBboxMaxWeaponRight(XMVECTOR vector)
{
	this->bboxMaxRight = vector;
}

void weaponClass::setBboxMinWeaponRight(XMVECTOR vector)
{
	this->bboxMinRight = vector;
}

XMVECTOR weaponClass::getBboxMaxWeaponRight()
{
	return this->bboxMaxRight;
}

XMVECTOR weaponClass::getBboxMinWeaponRight()
{
	return this->bboxMinRight;
}

collisionClass * weaponClass::getCollisionClass()
{
	return this->collision;
}

void weaponClass::setBboxMaxWeaponLeft(XMVECTOR vector)
{
	this->bboxMaxLeft = vector;
}

void weaponClass::setBboxMinWeaponLeft(XMVECTOR vector)
{
	this->bboxMinLeft = vector;
}

XMVECTOR weaponClass::getBboxMaxWeaponLeft()
{
	return this->bboxMaxLeft;
}

XMVECTOR weaponClass::getBboxMinWeaponLeft()
{
	return this->bboxMinLeft;
}
