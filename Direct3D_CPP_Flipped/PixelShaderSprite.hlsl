cbuffer playerConstBuffer : register(b0)
{
	int frameCount;
	int currentFrame;
	int test;
	bool flipped;
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
};


float4 main(VS_OUT input) : SV_TARGET
{
	float4 lightSource = input.cameraPos; //same as our camera since that is where we want our light to come from
	float4 lightDir = lightSource - input.pointOnSurface;
	lightDir = normalize(lightDir);
	float diffConstant = dot(lightDir.xyz, input.Normal.xyz);
	
	float frameSkip = (1.0f / frameCount);
	float initialUStep = input.TexCoord.x / frameCount;
	input.TexCoord.x = input.TexCoord.x / frameCount + (frameSkip * (currentFrame - 1));
	if (flipped == true)
		input.TexCoord.x = (frameSkip * currentFrame) - initialUStep;

	float4 color = texture1.Sample(textureSample, input.TexCoord);

	return float4(color);
}