#pragma once
#ifndef COLLISIONCLASS_H
#define COLLISIONCLASS_H

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class collisionClass
{
	private:

	public:
		collisionClass();
		collisionClass(const collisionClass& other);
		~collisionClass();

		bool checkCollision(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max);
		bool checkCollisionY(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max);

		bool checkCollisionTop(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max);
		bool checkCollisionLeft(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max);
		bool checkCollisionRight(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max);
		bool checkCollisionBot(XMVECTOR bbox1Min, XMVECTOR bbox1Max, XMVECTOR bbox2Min, XMVECTOR bbox2Max);

};

#endif