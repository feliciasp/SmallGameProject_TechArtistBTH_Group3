#include "d3dClass.h"

d3dClass::d3dClass()
{
	swapChain = 0;
	device = 0;
	deviceContext = 0;
	renderTargetBackBuffer = 0;
	depthStencilBuffer = 0;
	depthStencilView = 0;
	
	//depthStencilState = 0;
	//rasterState = 0;
}

d3dClass::d3dClass(const d3dClass * other)
{
}

d3dClass::~d3dClass()
{
}

bool d3dClass::initialize(int width, int height, bool vsync, HWND hwnd, bool fullscreen)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_VIEWPORT viewport;

	//init swap chain
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;		//set to 1 back buffer
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	//no multisampling
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	//discard back buffer contants adter presenting
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	if (fullscreen)
	{
		swapChainDesc.Windowed = FALSE;
	}
	else
	{
		swapChainDesc.Windowed = TRUE;
	}

	//create swap chain, direct3D device and direct3D device context
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, NULL, &deviceContext);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating swapchain and devices",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//we need to get pointer to backbuffer and attack it to swap chain.
	ID3D11Texture2D* ptrBackBuffer = nullptr;
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&ptrBackBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error attaching swapchain to backbuffer",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//create render target view with back buffer ptr
	result = device->CreateRenderTargetView(ptrBackBuffer, NULL, &renderTargetBackBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating render target view",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	ptrBackBuffer->Release();
	ptrBackBuffer = 0;

	//create depth buffer
	//init 
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencilBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating depth buffer 2D texture",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//we do not create a deapthStencil desc 
	//create deapth stencil view
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = device->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating depthstancilview",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//bind render target view and depth buffer to output render pipeline
	deviceContext->OMSetRenderTargets(1, &renderTargetBackBuffer, depthStencilView);

	//viewport setup for rendering
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	//create viewport 
	deviceContext->RSSetViewports(1, &viewport);

	return true;
}

bool d3dClass::initializeMatrices(int width, int height, float screenDepth, float screenNear)
{
	//setup the proj mat
	float fieldOfView = 3.14159 / 4.0f;
	float screenAspect = (float)width / (float)height;
	
	this->projMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
	this->projMatrixOrto = XMMatrixOrthographicLH(width/60, height/60, 0.1f, 1000.0f);

	//world mat
	this->worldMatrix = XMMatrixIdentity();
	
	//viewmatrix is created in camera class

	return true;
}

void d3dClass::shutdown()
{
	//if we shutdown in fullscreenmode exceptions will be trhown, to avoid that force windowed mode
	if (swapChain)
	{
		swapChain->SetFullscreenState(false, NULL);
	}
	if (depthStencilView)
	{
		depthStencilView->Release();
		depthStencilView = 0;
	}
	if (depthStencilBuffer)
	{
		depthStencilBuffer->Release();
		depthStencilBuffer = 0;
	}
	if (renderTargetBackBuffer)
	{
		renderTargetBackBuffer->Release();
		renderTargetBackBuffer = 0;
	}
	if (deviceContext)
	{
		deviceContext->Release();
		deviceContext = 0;
	}
	if (device)
	{
		device->Release();
		device = 0;
	}
	if (swapChain)
	{
		swapChain->Release();
		swapChain = 0;
	}
}

//BeginScene will be called whenever we are going to draw a new 3D scene at the beginning of each frame. All it does is initializes the buffers so they are blank and ready to be drawn to.
void d3dClass::beginScene(float x, float y, float z, float w)
{
	float color[4];

	//Setup color to clear the buffer to
	color[0] = x;
	color[1] = y;
	color[2] = z;
	color[3] = w;

	//clear backbuffer
	deviceContext->ClearRenderTargetView(renderTargetBackBuffer, color);
	//clear depthstencil
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void d3dClass::endScene()
{
	swapChain->Present(0, 0);
}

ID3D11Device * d3dClass::GetDevice()
{
	return this->device;
}

ID3D11DeviceContext * d3dClass::GetDeviceContect()
{
	return this->deviceContext;
}

void d3dClass::getProjMatrix(XMMATRIX & matrix)
{
	matrix = this->projMatrix;
}

void d3dClass::getWorldMatrix(XMMATRIX & matrix)
{
	matrix = this->worldMatrix;
}

void d3dClass::getOrtoProjMat(XMMATRIX & matrix)
{
	matrix = this->projMatrixOrto;
}
