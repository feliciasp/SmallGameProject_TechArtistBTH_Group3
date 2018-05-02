cbuffer playerConstBuffer : register(b0)
{
	int currentFrame;
	int frameCount;
	int flipped;
	int currentAnimation;
}

Texture2D texture1	: register(t0);
SamplerState textureSample;
struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 cameraPos : POSITION2;
	float4 Tangent : TANGENT;
};


float4 main(VS_OUT input) : SV_TARGET
{
	float frameSkipU = (1.0f / 8);
	float initialUStep = input.TexCoord.x / 8;
	input.TexCoord.x = input.TexCoord.x / 8 + (frameSkipU * (currentFrame - 1));

	float4 color = texture1.Sample(textureSample, input.TexCoord);

	return float4(color);
}