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

		bool render(ID3D11DeviceContext* devCon, int indexCount, XMMATRIX world, XMMATRIX view, XMMATRIX proj, int type, std::string name, std::string name2, XMVECTOR camPos, ID3D11RenderTargetView* renderTargetBackBuffer, ID3D11DepthStencilView* depthStencilView, XMMATRIX joints[30], int weaponType, int hurt, int frameCount, int currentFrame, int currentAnimation, bool flipped);
		bool createShaderClass(ID3D11Device* device);
		bool createTextureReasourceAndTextureView(ID3D11Device* device, std::string name);
		bool createNormalMapInfo(ID3D11Device * device, std::string name);


		bool setShaders(ID3D11DeviceContext* devContext);
		
		void shutdown();

	private:
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D11InputLayout* vertexLayout;
		ID3D11Buffer* constBuffer;
		ID3D11Buffer* playerConstBuffer;
		ID3D11GeometryShader* geometryShader;

		//normal
		texImage normalMap;
		/*ID3D11Texture2D *normalTexture;
		ID3D11ShaderResourceView* textureViewNorm;*/
		std::vector<ID3D11Texture2D*> normalTexture;
		std::vector<ID3D11ShaderResourceView*> textureViewNorm;
		std::vector<texImage> matNameHolderNormal;

		//texture2
		texImage texture;
		std::vector<ID3D11Texture2D*> textureInfo;
		std::vector<ID3D11ShaderResourceView*> textureRescourceView;
		ID3D11SamplerState* textureSample;
		ID3D11SamplerState* textureSampleSmoothed;

		//no trsansformation shaders
		ID3D11VertexShader* vertexShaderNoTransformation;
		ID3D11PixelShader* pixelShaderNoShading;

		//Sprite shaders
		ID3D11PixelShader* pixelShaderSprite;

		ID3D11PixelShader* pixelShaderEnemy;

		ID3D11PixelShader* pixelShaderPickup;

		ID3D11BlendState* transparency;

		struct cBuffer
		{
			XMMATRIX world;
			XMMATRIX view;
			XMMATRIX proj;
			XMMATRIX joints[30];
			XMVECTOR camPos;
			int hurtColor;
		};

		struct playerCBuffer
		{
			int currentFrame;
			int frameCount;
			int flipped;
			int currentAnimation;
		};

		bool createShaders(ID3D11Device* device);
		bool createConstantBuffer(ID3D11Device* device);
		bool createPlayerConstantBuffer(ID3D11Device* device);

		bool createSamplerDesc(ID3D11Device* device);

		bool createBlendState(ID3D11Device* device);

		bool setShaderParameters(ID3D11DeviceContext* devCon, XMMATRIX world, XMMATRIX view, XMMATRIX proj, XMVECTOR camPos, int hurt = 0);
		bool setPlayerShaderParameters(ID3D11DeviceContext* devCon, bool flipped, int frameCount, int currentFrame, int currentAnimation);
		bool setEnemyShaderParameters(ID3D11DeviceContext* devCon, XMMATRIX world, XMMATRIX view, XMMATRIX proj, XMVECTOR camPos, XMMATRIX joints[30], int jointCount, int hurt = 0);

		void renderShader(ID3D11DeviceContext* devCon, int indexCount, std::string name, std::string name2);
		void renderShaderScreenSpace(ID3D11DeviceContext* devCon, int indexCount, std::string name);
		void renderShaderSprite(ID3D11DeviceContext* devCon, int indexCount, std::string name, int weaponType);
		void renderEnemy(ID3D11DeviceContext* devCon, int indexCount, std::string name, std::string name2);
		void renderPickup(ID3D11DeviceContext* devCon, int indexCount, std::string name);

		std::vector<texImage> matNameHolder;

};

#endif
