struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 cameraPos : POSITION2;
};

struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 cameraPos : POSITION2;
};

[maxvertexcount(3)]
void GS_main(
	triangle VS_OUT input[3], 
	inout TriangleStream< GS_OUT > outputStream
)
{
	for (uint i = 0; i < 3; i++)
	{
		GS_OUT output = (GS_OUT)0;

		output.Pos = input[i].Pos;
		output.TexCoord = input[i].TexCoord;
		output.Normal = input[i].Normal;
		output.Color = input[i].Color;
		output.pointOnSurface = input[i].pointOnSurface;

		output.cameraPos = input[i].cameraPos;

		outputStream.Append(output);
		
	}
}