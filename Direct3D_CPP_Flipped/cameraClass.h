#pragma once

#ifndef CAMERACLASS_H
#define CAMERACLASS_H

#include <directxmath.h>
using namespace DirectX;

class cameraClass
{
	public:
		cameraClass();
		cameraClass(const cameraClass& other);
		~cameraClass();

		void setPosition(float x,float y,float z, float w);
		void updatePosition(float x, float y);
		void updateTarget(float x, float y);
		XMVECTOR getPosition();

		void createViewMatrix();
		void getViewMat(XMMATRIX& viewMat);

		void setTempX(float x);
		void setTempY(float y);
		float getTempX();
		float getTempY();

		void reset();

	private:
		XMVECTOR camPos;
		XMVECTOR camTarget;
		XMVECTOR camUp;

		float tempX;
		float tempY;

		XMMATRIX view;
};

#endif
