#pragma once

#ifndef D3DCLASS_H
#define D3DCLASS_H

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

//linking
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class d3dClass
{
	public:
		d3dClass();
		d3dClass(const d3dClass* other);
		~d3dClass();

		bool initialize(int width, int height, bool vsync, HWND hwnd, bool fullscreen);
		bool initializeMatrices(int width, int height, float screenDepth, float screenNear);
		void shutdown();

		void beginScene(float x, float y, float z, float w);
		void endScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContect();

		void getProjMatrix(XMMATRIX& matrix);
		void getWorldMatrix(XMMATRIX& matrix);
		//void getOrtoMatrix(XMMATRIX& matrix);		///?????????????????????

		//void getVideoCardInfo(char* desc, int& mem);

	private:
		bool vsync_enabled;

		XMMATRIX projMatrix;
		XMMATRIX worldMatrix;
		XMMATRIX viewMatrix;

		//int videoCardMem;
		//char videoCardDesc[128]
		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;

		ID3D11RenderTargetView* renderTargetBackBuffer;

		ID3D11Texture2D* depthStencilBuffer;
		//ID3D11DepthStencilState* depthStencilState;	///??????????????????????????
		ID3D11DepthStencilView* depthStencilView;

		//ID3D11RasterizerState* rasterState;		///??????????????????????????


};

#endif