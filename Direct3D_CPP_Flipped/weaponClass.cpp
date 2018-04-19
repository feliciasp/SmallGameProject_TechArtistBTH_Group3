#include "weaponClass.h"

weaponClass::weaponClass()
{
	bboxMin = { 0.0f, 0.0f };
	bboxMax = { 0.0f,0.0f };
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

void weaponClass::setBboxMaxWeapon(XMVECTOR vector)
{
	this->bboxMax = vector;
}

void weaponClass::setBboxMinWeapon(XMVECTOR vector)
{
	this->bboxMin = vector;
}

XMVECTOR weaponClass::getBboxMaxWeapon()
{
	return this->bboxMax;
}

XMVECTOR weaponClass::getBboxMinWeapon()
{
	return this->bboxMin;
}

collisionClass * weaponClass::getCollisionClass()
{
	return this->collision;
}
