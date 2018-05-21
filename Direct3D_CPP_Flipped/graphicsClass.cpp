#pragma once

#include "graphicsClass.h"

//ANNIES COOL TEST COMMENT = RAD

graphicsClass::graphicsClass()
{
	direct3D = 0;					//always init pointers to null for safety
	shaders = 0;
}

graphicsClass::graphicsClass(const graphicsClass & other)
{
}

graphicsClass::~graphicsClass()
{
}

bool graphicsClass::initialize(int width, int height, HWND hwnd, HINSTANCE hInstance)
{
	//create d3dClass object and then call d3dClass init function. 
	bool result;

	//crreate direct3d obj
	direct3D = new d3dClass;
	if (!direct3D)
	{
		MessageBox(NULL, L"Error creating d3d",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//init direct3d obj
	result = direct3D->initialize(width, height, VSYNC_ENABLED, hwnd, FULL_SCREEN);
	if (!result)
	{
		MessageBox(NULL, L"Error initializing d3d",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = direct3D->initializeMatrices(width, height, SCREEN_DEPTH, SCREEN_NEAR);
	//creat shaders class obj
	shaders = new shaderClass;
	if (!shaders)
	{
		MessageBox(NULL, L"Error create shaders obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//init and crreate shaders
	result = shaders->createShaderClass(direct3D->GetDevice());
	if (!result)
	{
		MessageBox(NULL, L"Error initializing shaders obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//set shaders
	result = shaders->setShaders(direct3D->GetDeviceContect());
	if (!result)
	{
		MessageBox(NULL, L"Error set shaders obj",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;


	return true;
}

void graphicsClass::shutdown()
{
	if (direct3D)
	{
		direct3D->shutdown();
		delete direct3D;
		direct3D = 0;
	}
	
	if (shaders)
	{
		shaders->shutdown();
		delete shaders;
		shaders = 0;
	}
}

bool graphicsClass::frame(objectClass* object, XMMATRIX view, XMMATRIX proj, int type, std::string name, XMVECTOR camPos, int weaponType, int hurt, int frameCount, int currentFrame, int currentAnimation, bool flipped)
{
 	bool result;
	//render graphics scene
	result = render(object, view, proj, type, name, camPos, direct3D->getRenderTargetBackBuffer(), direct3D->getDepthStencilView(), weaponType, hurt, frameCount, currentFrame, currentAnimation, flipped);
	if (!result)
	{
		MessageBox(NULL, L"Error rendering",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

d3dClass* graphicsClass::getD3D()
{
	return this->direct3D;
}

shaderClass * graphicsClass::getShaders()
{
	return this->shaders;
}

bool graphicsClass::render(objectClass* object, XMMATRIX view, XMMATRIX proj, int type, std::string name, XMVECTOR camPos, ID3D11RenderTargetView* renderTargetBackBuffer, ID3D11DepthStencilView* depthStencilView, int weaponType, int hurt, int frameCount, int currentFrame, int currentAnimation, bool flipped)
{
	HRESULT result;
	XMMATRIX tempWorld;

	object->getWorldMatrix(tempWorld);
	XMMatrixTranspose(tempWorld);

	for (int i = 0; i < object->getMeshCount(); i++)
	{
		object->setVtrxIndexBufferToPipline(direct3D->GetDeviceContect(), i);
		//redner using shaders
		result = shaders->render(direct3D->GetDeviceContect(), object->getVertexCount(i), tempWorld, view, proj, type, name, camPos, renderTargetBackBuffer, depthStencilView, weaponType, hurt, frameCount, currentFrame, currentAnimation, flipped);
		if (!result)
		{
			MessageBox(NULL, L"Error rendering tri1",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}

	return true;
}

void graphicsClass::endScene()
{
	direct3D->endScene();
}

void graphicsClass::beginScene()
{
	//clear buffer to begin the scene
	direct3D->beginScene(1.0f, 1.0f, 1.0f, 1.0f);
}
