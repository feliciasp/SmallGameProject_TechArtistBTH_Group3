#pragma once
#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include "stb_image2.h"				//for reading image



#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <fstream>
#include <vector>

//linking
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment (lib, "winmm.lib")

using namespace DirectX;

struct texImage
{
	int texWidth;
	int texHeight;
	int texBBP;
	unsigned char* texPixels;
	std::string nameMat;
};
class shaderClass
{
	public:
		shaderClass();
		shaderClass(const shaderClass& other);
		~shaderClass();

		bool render(ID3D11DeviceContext* devCon, int indexCount, XMMATRIX world, XMMATRIX view, XMMATRIX proj, int type, std::string name, XMVECTOR camPos, int frameCount, int currentFrame, bool flipped);
		bool createShaderClass(ID3D11Device* device);
		bool createTextureReasourceAndTextureView(ID3D11Device* device, std::string name);
		
		bool setShaders(ID3D11DeviceContext* devContext);
		
		void shutdown();

	private:
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D11InputLayout* vertexLayout;
		ID3D11Buffer* constBuffer;
		ID3D11Buffer* playerConstBuffer;
		ID3D11GeometryShader* geometryShader;

		//texture2
		texImage texture;
		std::vector<ID3D11Texture2D*> textureInfo;
		std::vector<ID3D11ShaderResourceView*> textureRescourceView;
		ID3D11SamplerState* textureSample;

		//no trsansformation shaders
		ID3D11VertexShader* vertexShaderNoTransformation;
		ID3D11PixelShader* pixelShaderNoShading;

		//Sprite shaders
		ID3D11PixelShader* pixelShaderSprite;

		ID3D11BlendState* transparency;

		struct cBuffer
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
			XMVECTOR camPos;
		};

		struct playerCBuffer
		{
			int frameCount;
			int currentFrame;
			int test;
			bool flipped;
		};

		bool createShaders(ID3D11Device* device);
		bool createConstantBuffer(ID3D11Device* device);
		bool createPlayerConstantBuffer(ID3D11Device* device);

		bool createSamplerDesc(ID3D11Device* device);

		bool createBlendState(ID3D11Device* device);

		bool setShaderParameters(ID3D11DeviceContext* devCon, XMMATRIX world, XMMATRIX view, XMMATRIX proj, XMVECTOR camPos);
		bool setPlayerShaderParameters(ID3D11DeviceContext* devCon, bool flipped, int frameCount, int currentFrame);
		void renderShader(ID3D11DeviceContext* devCon, int indexCount, std::string name);
		void renderShaderScreenSpace(ID3D11DeviceContext* devCon, int indexCount, std::string name);
		void renderShaderSprite(ID3D11DeviceContext* devCon, int indexCount, std::string name);

		std::vector<texImage> matNameHolder;

};

#endif
