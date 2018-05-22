#include "collisionClass.h"

collisionClass::collisionClass()
{
}

collisionClass::collisionClass(const collisionClass & other)
{
}

collisionClass::~collisionClass()
{
}

bool collisionClass::checkCollision(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max)
{
	bool check1 = false;
	bool check2 = false;
	if (XMVectorGetX(bbox1Max) >= XMVectorGetX(bbox2Min) && XMVectorGetX(bbox1Min) <= XMVectorGetX(bbox2Max))
	{
		check1 = true;
	}
	if (XMVectorGetY(bbox1Max) >= XMVectorGetY(bbox2Min) && XMVectorGetY(bbox1Min) <= XMVectorGetY(bbox2Max))
	{
		check2 = true;
	}
	if (check1 == true && check2 == true)
	{
		return true;
	}
	return false;
}

bool collisionClass::checkCollisionTop(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max)
{
	bool check1 = false;
	bool check2 = false;
	if (XMVectorGetX(bbox1Max) - 0.1f >= XMVectorGetX(bbox2Min) && XMVectorGetX(bbox1Min) + 0.1f <= XMVectorGetX(bbox2Max))
	{
		check1 = true;
	}
	if (XMVectorGetY(bbox1Max) >= XMVectorGetY(bbox2Min) && XMVectorGetY(bbox1Max) <= XMVectorGetY(bbox2Max))
	{
		check2 = true;
	}
	if (check1 == true && check2 == true)
	{
		return true;
	}
	return false;
}

bool collisionClass::checkCollisionLeft(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max)
{
	bool check1 = false;
	bool check2 = false;
	if (XMVectorGetX(bbox1Min) >= XMVectorGetX(bbox2Min) && XMVectorGetX(bbox1Min) <= XMVectorGetX(bbox2Max))
	{
		check1 = true;
	}
	if (XMVectorGetY(bbox1Max) - 0.1f >= XMVectorGetY(bbox2Min) && XMVectorGetY(bbox1Min) + 0.1f <= XMVectorGetY(bbox2Max))
	{
		check2 = true;
	}
	if (check1 == true && check2 == true)
	{
		return true;
	}
	return false;
}

bool collisionClass::checkCollisionRight(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max)
{
	bool check1 = false;
	bool check2 = false;
	if (XMVectorGetX(bbox1Max) >= XMVectorGetX(bbox2Min) && XMVectorGetX(bbox1Max) <= XMVectorGetX(bbox2Max))
	{
		check1 = true;
	}
	if (XMVectorGetY(bbox1Max) - 0.1f >= XMVectorGetY(bbox2Min) && XMVectorGetY(bbox1Min) + 0.1f <= XMVectorGetY(bbox2Max))
	{
		check2 = true;
	}
	if (check1 == true && check2 == true)
	{
		return true;
	}
	return false;
}

bool collisionClass::checkCollisionBot(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max)
{

	bool check1 = false;
	bool check2 = false;
	if (XMVectorGetX(bbox1Max) - 0.1f >= XMVectorGetX(bbox2Min) && XMVectorGetX(bbox1Min) + 0.1f <= XMVectorGetX(bbox2Max))
	{
		check1 = true;
	}
	if (XMVectorGetY(bbox1Min) >= XMVectorGetY(bbox2Min) && XMVectorGetY(bbox1Min) <= XMVectorGetY(bbox2Max))
	{
		check2 = true;
	}
	if (check1 == true && check2 == true)
	{
		return true;
	}
	return false;
}
