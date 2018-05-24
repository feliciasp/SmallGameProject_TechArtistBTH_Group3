#include "cameraClass.h"

cameraClass::cameraClass()
{
	camPos = { 0,0,0 };
	camTarget = { 0,0,0 };
	camUp = { 0,0,0 };

	view = XMMatrixIdentity();
}

cameraClass::cameraClass(const cameraClass & other)
{
}

cameraClass::~cameraClass()
{
}


void cameraClass::setPosition(float x, float y, float z, float w)
{
	camPos = { x, y, z, w };

	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

void cameraClass::updateTarget(float x, float y)
{
	camTarget = { x, y + 2, 0.0f, 0.0f };
}

void cameraClass::updatePosition(float x, float y)
{
	camPos = { x, y + 3, XMVectorGetZ(camPos), XMVectorGetW(camPos) };
}

void cameraClass::updatePositionZ(float z)
{
	camPos = { XMVectorGetX(camPos), XMVectorGetY(camPos), z, XMVectorGetW(camPos) };
}



XMVECTOR cameraClass::getPosition()
{
	return this->camPos;
}

void cameraClass::createViewMatrix()
{
	view = XMMatrixLookAtLH(camPos, camTarget, camUp);
}

void cameraClass::getViewMat(XMMATRIX & viewMat)
{
	viewMat = this->view;
}

void cameraClass::setTempX(float x)
{
	this->tempX = x;
}

void cameraClass::setTempY(float y)
{
	this->tempY = y;
}

float cameraClass::getTempX()
{
	return this->tempX;
}

float cameraClass::getTempY()
{
	return this->tempY;
}

void cameraClass::reset()
{
	this->camPos = { 0.0f, 0.0f, -20.0f, 0.0f };
	this->camTarget = { 0.0f, 5.0f, 0.0f, 0.0f };

}
