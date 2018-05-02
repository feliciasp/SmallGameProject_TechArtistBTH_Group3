cbuffer constBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
	float4 cameraPos;
	int hurtColor;
};
struct VS_IN
{
	float3 Pos : POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	float2 TexCoord : TEXCOORD;
	float3 Tangent : TANGENT;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 cameraPos : POSITION2;
	int hurtColor : HURT;
	//float4 Tangent : TANGENT;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	matrix transform = mul(world, mul(view, proj));

	output.Pos = float4(input.Pos, 1);
	output.Pos = mul(output.Pos, transform);
	output.Normal = mul(input.Normal, world);
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;
	output.pointOnSurface = mul(input.Pos, world);
	output.cameraPos = cameraPos;
	output.hurtColor = hurtColor;
	//output.Tangent = float4(input.Tangent, 1.0f);

	return output;
}