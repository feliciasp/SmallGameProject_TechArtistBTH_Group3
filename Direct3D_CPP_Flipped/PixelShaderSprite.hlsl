cbuffer playerConstBuffer : register(b0)
{
	int currentFrame;
	int frameCount;
	int flipped;
	int currentAnimation;
}

Texture2D texture1	: register(t0);
Texture2D texture2 : register(t1);
Texture2D texture3 : register(t2);
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
	float4 lightSource = input.cameraPos; //same as our camera since that is where we want our light to come from
	float4 lightDir = lightSource - input.pointOnSurface;
	lightDir = normalize(lightDir);
	float diffConstant = dot(lightDir.xyz, input.Normal.xyz);
	
	float frameSkipU = (1.0f / 10);
	float frameSkipV = (1.0f / 8);
	float initialUStep = input.TexCoord.x / 10;
	float initialVStep = input.TexCoord.y / 8;
	input.TexCoord.x = input.TexCoord.x / 10 + (frameSkipU * (currentFrame - 1));
	input.TexCoord.y = input.TexCoord.y / 8 + (frameSkipV * (currentAnimation - 1));
	if (flipped == true)
		input.TexCoord.x = (frameSkipU * currentFrame) - initialUStep;

	float4 color = texture1.Sample(textureSample, input.TexCoord);
	float4 hat = texture3.Sample(textureSample, input.TexCoord);
	float4 weapon = texture2.Sample(textureSample, input.TexCoord);
	if (hat.a == 1)
	{
		color = hat;
	}
	if (weapon.a == 1)
	{
		color = weapon;
	}

	return float4(color);
}