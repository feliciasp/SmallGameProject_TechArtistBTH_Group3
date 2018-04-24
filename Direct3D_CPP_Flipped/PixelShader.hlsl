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


float4 PS_main(VS_OUT input) : SV_TARGET
{
	input.cameraPos.z = -4.0f;
input.cameraPos.y -= 2.0f;

float4 ambient = float4(0.0f, 0.0f, 0.1f, 1.0f);
float4 lightColor = float4(1.0f, 0.7f, 0.4f, 1.0f);
float4 lightSource = input.cameraPos; //same as our camera since that is where we want our light to come from
float4 lightDir = lightSource - input.pointOnSurface;
float lightDistance = length(lightDir);
lightDir = normalize(lightDir);
float diffConstant = dot(lightDir.xyz, input.Normal.xyz);
float4 color = texture1.Sample(textureSample, input.TexCoord);
float4 colorShaded;


colorShaded = color * lightColor * diffConstant;
colorShaded += ambient;

//color += colorShaded;
//float3 colorShaded = input.Color * diffConstant;

return float4(colorShaded.xyz, color.w);
}