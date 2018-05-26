cbuffer constBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
};
struct VS_IN
{
	float3 Pos			: POSITION;
	float3 Normal		: NORMAL;
	float3 Color		: COLOR;
	float2 TexCoord		: TEXCOORD;
	float4 Weights		: WEIGHT;
	int4 Joints			: JOINT;
	float3 Tangent		: TANGENT;
	float3 Binormal		: BINORMAL;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	//float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 Tangent : TANGENT;
};

VS_OUT VS2_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	//matrix transform = mul(world, mul(view, proj));

	output.Pos = float4(input.Pos, 1);
	output.Pos = mul(output.Pos, world);
	output.Normal = input.Normal;
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;
	//output.pointOnSurface = mul(input.Pos, world);
	//output.Tangent = float4(input.Tanget, 1.0f);
	
	return output;
}