cbuffer constBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
	matrix joints[30];
	float4 cameraPos;
	int hurtColor;
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
	float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 cameraPos : POSITION2;
	int hurtColor : HURT;
	float3 Tangent : TANGENT;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	matrix transform = mul(world, mul(view, proj));

	float4 newPos = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 newNormal = float4(0.0f, 0.0f, 0.0f, 0.0f);
	output.Pos = float4(input.Pos, 1);

	if (input.Joints.x != -1)
	{
		matrix animation = joints[input.Joints.x] * input.Weights.x;
		newPos += mul(output.Pos, animation);
		newNormal += mul(input.Normal, animation);
	}

	if (input.Joints.y != -1)
	{
		matrix animation = joints[input.Joints.y] * input.Weights.y;
		newPos += mul(output.Pos, animation);
		newNormal += mul(input.Normal, animation);
	}

	if (input.Joints.z != -1)
	{
		matrix animation = joints[input.Joints.z] * input.Weights.z;
		newPos += mul(output.Pos, animation);
		newNormal += mul(input.Normal, animation);
	}

	if (input.Joints.w != -1)
	{
		matrix animation = joints[input.Joints.w] * input.Weights.w;
		newPos += mul(output.Pos, animation);
		newNormal += mul(input.Normal, animation);
	}

	if (input.Joints.x != -1 || input.Joints.y != -1 || input.Joints.z != -1 || input.Joints.w != -1)
	{
		output.Pos.xyz = newPos.xyz;
		input.Pos = newPos.xyz;
		input.Normal = newNormal.xyz;
	}


	float4 normal = mul(float4(input.Normal, 0.0f), world);
	output.Pos = mul(output.Pos, transform);
	output.Normal = normal.xyz;
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;
	output.pointOnSurface = mul(float4(input.Pos, 1.0f), world);
	output.cameraPos = cameraPos;
	output.hurtColor = hurtColor;
	output.Tangent = input.Tangent;

	return output;
}