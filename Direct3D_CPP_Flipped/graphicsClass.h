#pragma once
#ifndef GRAPHICSCLASS_H
#define GRAPHICSCLASS_H

#include "d3dClass.h"
#include "shaderClass.h"
#include "objectClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;	//render according to user monitor or as fast as possible
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class graphicsClass
{
	public:
		graphicsClass();
		graphicsClass(const graphicsClass& other);
		~graphicsClass();

		bool initialize(int width, int height, HWND hwnd, HINSTANCE hInstance);
		void shutdown();
		bool frame(objectClass* object, XMMATRIX view, XMMATRIX proj, int type, std::string name, XMVECTOR camPos, int weaponType, int hurt = 0, int frameCount = 1, int currentFrame = 1, int currentAnimation = 1, bool flipped = false);
		void endScene();
		void beginScene();

		d3dClass* getD3D();
		shaderClass* getShaders();

	private:
		d3dClass* direct3D;
		shaderClass* shaders;

		bool render(objectClass* obj, XMMATRIX view, XMMATRIX proj, int type, std::string name, XMVECTOR camPos, ID3D11RenderTargetView* renderTargetBackBuffer, ID3D11DepthStencilView* depthStencilView, int weaponType, int hurt, int frameCount, int currentFrame, int currentAnimation, bool flipped);

};

#endif