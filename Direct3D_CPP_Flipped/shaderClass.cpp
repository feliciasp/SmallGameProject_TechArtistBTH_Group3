#include "shaderClass.h"

shaderClass::shaderClass()
{
	vertexShader = 0;
	pixelShader = 0;
	vertexLayout = 0;
	constBuffer = 0;
	geometryShader = 0;
	
	textureSample = 0;
	vertexShaderNoTransformation = 0;
	pixelShaderNoShading = 0;

	normalTexture = 0;
	textureViewNorm = 0;
}

shaderClass::shaderClass(const shaderClass & other)
{
}

shaderClass::~shaderClass()
{
}

bool shaderClass::render(ID3D11DeviceContext * devCon, int indexCount, XMMATRIX world, XMMATRIX view, XMMATRIX proj, int type, std::string name, XMVECTOR camPos, int hurt, int frameCount, int currentFrame, int currentAnimation, bool flipped)
{
	bool result;

	//set shader parameters that we will use for rendering
	result = setShaderParameters(devCon, world, view, proj, camPos, hurt);
	if (!result)
	{
		MessageBox(NULL, L"Error setting shader parameters",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//render buffer with shader
	if (type == 1)
	{
		renderShaderScreenSpace(devCon, indexCount, name);
	}

	else if (type == 2)
	{
		result = setPlayerShaderParameters(devCon, flipped, frameCount, currentFrame, currentAnimation);
		if (!result)
		{
			MessageBox(NULL, L"Error setting player shader parameters",
				L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		renderShaderSprite(devCon, indexCount, name);
	}

	else if (type == 3)
	{
		renderEnemy(devCon, indexCount, name);
	}

	else if (type == 4)
	{
		result = setPlayerShaderParameters(devCon, flipped, frameCount, currentFrame, currentAnimation);
		renderPickup(devCon, indexCount, name);
	}
	else
	{
		renderShader(devCon, indexCount, name);
	}
	

	return true;
}

bool shaderClass::createShaderClass(ID3D11Device * device)
{
	HRESULT result;
	result = createShaders(device);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating Shaders",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	
	result = createConstantBuffer(device);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error createing cBuffer2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	result = createPlayerConstantBuffer(device);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating player cBuffer2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	result = createBlendState(device);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating blend state",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	result = createSamplerDesc(device);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating sampler view2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	/*result = createTextureReasourceAndTextureView(device, "texture1.jpg");
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating resource and texture view2",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}*/
	return true;
}

//initializing
bool shaderClass::setShaders(ID3D11DeviceContext * devContext)
{
	devContext->OMSetBlendState(transparency, NULL, 0xffffffff);
	
	devContext->VSSetShader(vertexShader, nullptr, 0);
	devContext->GSSetShader(geometryShader, nullptr, 0);
	devContext->PSSetShader(pixelShader, nullptr, 0);
	/*devContext->PSSetShaderResources(0, 1, &textureRescourceView[0]);
	devContext->PSSetSamplers(0, 1, &textureSample);*/

	devContext->IASetInputLayout(vertexLayout);
	devContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

bool shaderClass::createTextureReasourceAndTextureView(ID3D11Device* device, std::string name)
{
	for (int j = 0; j < matNameHolder.size(); j++)
	{
		if (matNameHolder[j].nameMat == name)
		{
			OutputDebugString(L"\nMaterial was already been created\n");
			return true;
		}
	}
	HRESULT result;

	texture.texPixels = stbi_load(name.c_str(), &texture.texWidth, &texture.texHeight, &texture.texBBP, 4);
	if (!texture.texPixels)
	{
		std::wstring test = L"ERROR";
		MessageBox(0, test.c_str(), L"TEST", MB_OK);
		return false;
	}
	texture.nameMat = name;

	matNameHolder.push_back(texture);


	ID3D11Texture2D* tempTexture = nullptr;
	textureInfo.push_back(tempTexture);
	ID3D11ShaderResourceView* tempShaderResource = nullptr;
	textureRescourceView.push_back(tempShaderResource);

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = matNameHolder[textureRescourceView.size() - 1].texWidth;
	textureDesc.Height = matNameHolder[textureRescourceView.size() - 1].texHeight;
	textureDesc.MipLevels = textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.MiscFlags = 0;
	textureDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA texData;
	ZeroMemory(&texData, sizeof(texData));
	texData.pSysMem = (void*)matNameHolder[textureRescourceView.size() - 1].texPixels;
	texData.SysMemPitch = matNameHolder[textureRescourceView.size() - 1].texWidth * 4 * sizeof(char);
	result = device->CreateTexture2D(&textureDesc, &texData, &textureInfo[textureRescourceView.size() - 1]);
		//Describe shader resource view
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc, sizeof(viewDesc));
	viewDesc.Format = textureDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = textureDesc.MipLevels;
	viewDesc.Texture2D.MostDetailedMip = 0;
	result = device->CreateShaderResourceView(textureInfo[textureRescourceView.size() - 1], &viewDesc, &textureRescourceView[textureRescourceView.size() - 1]);

	stbi_image_free(matNameHolder[textureRescourceView.size() - 1].texPixels);

	OutputDebugString(L"\nMaterial was created\n");
	return true;

}

bool shaderClass::createSamplerDesc(ID3D11Device * device)
{
	HRESULT result;
	//Describe sampler desc
	D3D11_SAMPLER_DESC texSampDesc;
	ZeroMemory(&texSampDesc, sizeof(texSampDesc));
	texSampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	texSampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	texSampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	texSampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	texSampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	texSampDesc.MinLOD = 0;
	texSampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&texSampDesc, &textureSample);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating shader resource view",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	

	return true;
}

bool shaderClass::createBlendState(ID3D11Device * device)
{
	HRESULT result;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
	rtbd.DestBlendAlpha = D3D11_BLEND_ONE;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;
	
	result = device->CreateBlendState(&blendDesc, &transparency);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating blend state",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	
	return true;
}

bool shaderClass::createShaders(ID3D11Device* device)
{
	HRESULT result;

	//create vertex shader
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(
		L"VertexShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_5_0",		// shader model (target)
		0,				// shader compile options			// here DEBUGGING OPTIONS
		0,				// effect compile options
		&pVS,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
	);
	result = device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &this->vertexShader);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating vertexShader",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	//create vertex shader
	ID3DBlob* pVS2 = nullptr;
	D3DCompileFromFile(
		L"VertexShaderNoTransform.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS2_main",		// entry point
		"vs_5_0",		// shader model (target)
		0,				// shader compile options			// here DEBUGGING OPTIONS
		0,				// effect compile options
		&pVS2,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
	);
	result = device->CreateVertexShader(pVS2->GetBufferPointer(), pVS2->GetBufferSize(), nullptr, &this->vertexShaderNoTransformation);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating vertexShader no transformation",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	
	//input layout for vtx shader
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	result = device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &this->vertexLayout);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating vertexLayout",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	result = device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS2->GetBufferPointer(), pVS2->GetBufferSize(), &this->vertexLayout);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating vertexLayout",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	pVS->Release();
	pVS = 0;
	pVS2->Release();
	pVS2 = 0;

	//pixelShader
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(
		L"PixelShader.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_5_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	result = device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &this->pixelShader);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating pixelShader",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	// we do not need anymore this COM object, so we release it.
	pPS->Release();
	pPS = 0;

	//pixelShader
	ID3DBlob* pPS2 = nullptr;
	D3DCompileFromFile(
		L"PixelShaderNoShading.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS2_main",		// entry point
		"ps_5_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS2,			// double pointer to ID3DBlob		
		nullptr			// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);
	result = device->CreatePixelShader(pPS2->GetBufferPointer(), pPS2->GetBufferSize(), nullptr, &this->pixelShaderNoShading);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating pixelShader",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	// we do not need anymore this COM object, so we release it.
	pPS2->Release();
	pPS2 = 0;

	//pixelShader sprite
	ID3DBlob* pPSSprite = nullptr;
	D3DCompileFromFile(
		L"PixelShaderSprite.hlsl",
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		0,
		0,
		&pPSSprite,
		nullptr
	);
	result = device->CreatePixelShader(pPSSprite->GetBufferPointer(), pPSSprite->GetBufferSize(), nullptr, &this->pixelShaderSprite);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating sprite pixelShader",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	pPSSprite->Release();
	pPSSprite = 0;

	//pixelShader enemy
	ID3DBlob* pPSEnemy = nullptr;
	D3DCompileFromFile(
		L"PixelShaderEnemy.hlsl",
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		0,
		0,
		&pPSEnemy,
		nullptr
	);
	result = device->CreatePixelShader(pPSEnemy->GetBufferPointer(), pPSEnemy->GetBufferSize(), nullptr, &this->pixelShaderEnemy);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating sprite pixelShader",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	pPSEnemy->Release();
	pPSEnemy = 0;

	ID3DBlob* pPSPickup = nullptr;
	D3DCompileFromFile(
		L"PickUpPixelShader.hlsl",
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		0,
		0,
		&pPSPickup,
		nullptr
	);
	result = device->CreatePixelShader(pPSPickup->GetBufferPointer(), pPSPickup->GetBufferSize(), nullptr, &this->pixelShaderPickup);

	pPSPickup->Release();
	pPSPickup = 0;

	//geometryShader
	ID3DBlob * pGS = nullptr;
	D3DCompileFromFile(
		L"GeometryShader.hlsl",
		nullptr,
		nullptr,
		"GS_main",
		"gs_5_0",
		0,
		0,
		&pGS,
		nullptr
	);

	result = device->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &this->geometryShader);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating geometryShader",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	pGS->Release();
	pGS = 0;

	return true;
}

bool shaderClass::createConstantBuffer(ID3D11Device * device)
{
	HRESULT result;

	D3D11_BUFFER_DESC testBufferDesc;
	testBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	testBufferDesc.ByteWidth = sizeof(cBuffer);
	testBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	testBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	testBufferDesc.MiscFlags = 0;
	testBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&testBufferDesc, nullptr, &constBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating cBuffer",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

bool shaderClass::createPlayerConstantBuffer(ID3D11Device * device)
{
	HRESULT result;

	D3D11_BUFFER_DESC playerBufferDesc;
	playerBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	playerBufferDesc.ByteWidth = sizeof(playerCBuffer);
	playerBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	playerBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	playerBufferDesc.MiscFlags = 0;
	playerBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&playerBufferDesc, nullptr, &playerConstBuffer);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creating cBuffer",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

bool shaderClass::setShaderParameters(ID3D11DeviceContext *devCon, XMMATRIX world, XMMATRIX view, XMMATRIX proj, XMVECTOR camPos, int hurt)
{
	//used to set global variables in the shader easier and more accessble
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResources;
	cBuffer* dataPtr;
	unsigned int bufferNumber;

	//transpose matrices
	world = XMMatrixTranspose(world);
	view = XMMatrixTranspose(view);
	proj = XMMatrixTranspose(proj);

	//LOCK cosntantbufffer, set new matrtices, unlock it
	//map new values
	result = devCon->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResources);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error mapping to cosnt buffer",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//ptr to data in the constant buffer
	dataPtr = (cBuffer*)mappedResources.pData;
	//copy matrices into the c buffer
	dataPtr->world = world;
	dataPtr->view = view;
	dataPtr->proj = proj;
	dataPtr->camPos = camPos;
	dataPtr->hurtColor = hurt;
	//unlock it
	devCon->Unmap(constBuffer, 0);

	//set updated constant buffer in the HLSL vertexshader
	//set pos of constant buffer in vertex shader
	bufferNumber = 0;
	//set conatnbuffer in hte vtx shader wioth the updated values
	devCon->VSSetConstantBuffers(bufferNumber, 1, &constBuffer);

	return true;
}

bool shaderClass::setPlayerShaderParameters(ID3D11DeviceContext * devCon, bool flipped, int frameCount, int currentFrame, int currentAnimation)
{
	HRESULT result;

	D3D11_MAPPED_SUBRESOURCE mappedResources;
	playerCBuffer* dataPtr;
	unsigned int bufferNumber;

	result = devCon->Map(playerConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResources);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error mapping to const player buffer",
			L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	dataPtr = (playerCBuffer*)mappedResources.pData;
	dataPtr->flipped = flipped;
	dataPtr->currentFrame = currentFrame;
	dataPtr->currentAnimation = currentAnimation;

	devCon->Unmap(playerConstBuffer, 0);

	bufferNumber = 0;

	devCon->PSSetConstantBuffers(bufferNumber, 1, &playerConstBuffer);

	return true;
}

//secound func called in rander func. setShaderParam is before to ensure everything is setup correctly
void shaderClass::renderShader(ID3D11DeviceContext * devCon, int indexCount, std::string name)
{
	//Set vertex Layout
	devCon->IASetInputLayout(vertexLayout);
	//set vertex and pixel shaders the wil be used to render triangle
	devCon->VSSetShader(vertexShader, nullptr, 0);
	devCon->PSSetShader(pixelShader, nullptr, 0);
	
	for (int i = 0; i < matNameHolder.size(); i++)
	{
		if (matNameHolder[i].nameMat == name)
		{
			devCon->PSSetShaderResources(0, 1, &textureRescourceView[i]);
		}
	}
	//devCon->PSSetSamplers(0, 1, &textureSample);

	//render triangle
	devCon->Draw(indexCount, 0);
}

void shaderClass::renderShaderScreenSpace(ID3D11DeviceContext * devCon, int indexCount, std::string name)
{
	//Set vertex Layout
	devCon->IASetInputLayout(vertexLayout);
	//set vertex and pixel shaders the wil be used to render triangle
	devCon->VSSetShader(vertexShaderNoTransformation, nullptr, 0);
	devCon->PSSetShader(pixelShaderNoShading, nullptr, 0);

	for (int i = 0; i < matNameHolder.size(); i++)
	{
		if (matNameHolder[i].nameMat == name)
		{
			devCon->PSSetShaderResources(0, 1, &textureRescourceView[i]);
		}
	}

	//devCon->PSSetSamplers(0, 1, &textureSample);

	//render triangle
	devCon->Draw(indexCount, 0);
}

void shaderClass::renderShaderSprite(ID3D11DeviceContext * devCon, int indexCount, std::string name)
{
	devCon->IASetInputLayout(vertexLayout);
	devCon->VSSetShader(vertexShader, nullptr, 0);
	devCon->PSSetShader(pixelShaderSprite, nullptr, 0);

	for (int i = 0; i < matNameHolder.size(); i++)
	{
		if (matNameHolder[i].nameMat == name)
		{
			devCon->PSSetShaderResources(0, 1, &textureRescourceView[i]);
		}

		if (matNameHolder[i].nameMat == "ShovelSpriteSheet.png")
		{
			devCon->PSSetShaderResources(1, 1, &textureRescourceView[i]);
		}
	}
	//devCon->PSSetSamplers(0, 1, &textureSample);

	//render triangle
	devCon->Draw(indexCount, 0);
}

void shaderClass::renderEnemy(ID3D11DeviceContext * devCon, int indexCount, std::string name)
{
	//Set vertex Layout
	devCon->IASetInputLayout(vertexLayout);
	//set vertex and pixel shaders the wil be used to render triangle
	devCon->VSSetShader(vertexShader, nullptr, 0);
	devCon->PSSetShader(pixelShaderEnemy, nullptr, 0);

	for (int i = 0; i < matNameHolder.size(); i++)
	{
		if (matNameHolder[i].nameMat == name)
		{
			devCon->PSSetShaderResources(0, 1, &textureRescourceView[i]);
		}
	}
	//devCon->PSSetSamplers(0, 1, &textureSample);

	//render triangle
	devCon->Draw(indexCount, 0);
}

void shaderClass::renderPickup(ID3D11DeviceContext * devCon, int indexCount, std::string name)
{
	devCon->IASetInputLayout(vertexLayout);
	devCon->VSSetShader(vertexShader, nullptr, 0);
	devCon->PSSetShader(pixelShaderPickup, nullptr, 0);

	for (int i = 0; i < matNameHolder.size(); i++)
	{
		if (matNameHolder[i].nameMat == name)
		{
			devCon->PSSetShaderResources(0, 1, &textureRescourceView[i]);
		}
	}

	devCon->Draw(indexCount, 0);
}

void shaderClass::shutdown()
{
	if (vertexShader)
	{
		vertexShader->Release();
		vertexShader = 0;
	}
	if (pixelShader)
	{
		pixelShader->Release();
		pixelShader = 0;
	}
	if (vertexShader)
	{
		vertexLayout->Release();
		vertexLayout = 0;
	}
	if (constBuffer)
	{
		constBuffer->Release();
		constBuffer = 0;
	}
	if (geometryShader)
	{
		geometryShader->Release();
		geometryShader = 0;
	}
	if (textureSample)
	{
		textureSample->Release();
		textureSample = 0;
	}
	if (vertexShaderNoTransformation)
	{
		vertexShaderNoTransformation->Release();
		vertexShaderNoTransformation = 0;
	}
	if (pixelShaderNoShading)
	{
		pixelShaderNoShading->Release();
		pixelShaderNoShading = 0;
	}
	if (normalTexture)
	{
		normalTexture->Release();
		normalTexture = 0;
	}
	if (textureViewNorm)
	{
		textureViewNorm->Release();
		textureViewNorm = 0;
	}
}


void shaderClass::createNormalMapInfo(ID3D11Device * device)
{
	HRESULT result;
	normalMap.texHeight = 1024;
	normalMap.texWidth = 1024;
	normalMap.texPixels = stbi_load("normal_3.jpg", &normalMap.texHeight, &normalMap.texWidth, &normalMap.texBBP, 4);

	// -------------DESCRIBE TEXTURE--------------
	D3D11_TEXTURE2D_DESC normalMapInfo;
	ZeroMemory(&normalMapInfo, sizeof(normalMapInfo));
	normalMapInfo.Width = normalMap.texWidth;
	normalMapInfo.Height = normalMap.texHeight;
	normalMapInfo.MipLevels = normalMapInfo.ArraySize = 1;
	normalMapInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	normalMapInfo.SampleDesc.Count = 1;
	normalMapInfo.SampleDesc.Quality = 0;
	normalMapInfo.Usage = D3D11_USAGE_DEFAULT;
	normalMapInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	normalMapInfo.MiscFlags = 0;
	normalMapInfo.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA normalMapData;
	ZeroMemory(&normalMapData, sizeof(normalMapData));
	normalMapData.pSysMem = (void*)normalMap.texPixels;
	normalMapData.SysMemPitch = normalMap.texWidth * 4 * sizeof(char);

	result = device->CreateTexture2D(&normalMapInfo, &normalMapData, &normalTexture);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creatibg normal map",
			L"Error", MB_OK | MB_ICONERROR);
	}

	// ------------DESCRIBE SHADER RESOURCE VIEW-------------
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDescNorm;
	ZeroMemory(&viewDescNorm, sizeof(viewDescNorm));
	viewDescNorm.Format = normalMapInfo.Format;
	viewDescNorm.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDescNorm.Texture2D.MipLevels = normalMapInfo.MipLevels;
	viewDescNorm.Texture2D.MostDetailedMip = 0;
	result = device->CreateShaderResourceView(normalTexture, &viewDescNorm, &textureViewNorm);
	if (FAILED(result))
	{
		MessageBox(NULL, L"Error creatibg normal map2",
			L"Error", MB_OK | MB_ICONERROR);
	}

	stbi_image_free(normalMap.texPixels);

}