Texture2D texture1	: register(t0);
SamplerState textureSample;
struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Color : COLOR;
	//float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
};


float4 PS2_main(VS_OUT input) : SV_TARGET
{
	//float4 lightSource = float4(0.0f, 5.0f, -5.0f, 1.0f); //same as our camera since that is where we want our light to come from
	//float4 lightDir = lightSource - input.pointOnSurface;
	//lightDir = normalize(lightDir);
	//float diffConstant = dot(lightDir.xyz, input.Normal.xyz);

	float4 color = texture1.Sample(textureSample, input.TexCoord);
	//float3 colorShaded = color * diffConstant + (0.2 * input.Color);
	//float3 colorShaded = input.Color * diffConstant;
	float4 color2 = color;

	return float4(color);
}