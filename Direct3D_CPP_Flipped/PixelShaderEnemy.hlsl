Texture2D texture1	: register(t0);
Texture2D normMap : register(t1);
SamplerState textureSample;
struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
	float3 Color : COLOR;
	float4 pointOnSurface : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 cameraPos : POSITION2;
	int hurtColor : HURT;
	float4 Tangent : TANGENT;

};

float4 main(VS_OUT input) : SV_TARGET
{

	float4 colorShaded;
	float4 color;

	if (input.hurtColor != 2)
	{
		input.cameraPos.z = -4.0f;
		input.cameraPos.y -= 2.0f;

		input.Normal = normalize(input.Normal);

		//////NORMAL MAP
		//////Load normal from normal map
		//float4 normalMap = normMap.Sample(textureSample, input.TexCoord);
		////Change normal map range from [0, 1] to [-1, 1]
		//normalMap = (2.0f*normalMap) - 1.0f;
		////Make sure tangent is completely orthogonal to normal
		//input.Tangent = normalize(input.Tangent - dot(input.Tangent, input.Normal)*input.Normal);
		////Create the biTangent
		//float3 biTangent = cross(input.Normal, input.Tangent);
		////Create the "Texture Space mat"
		//float3 vecTang = float3(input.Tangent.x, input.Tangent.y, input.Tangent.z);
		//float3 vecNorm = float3(input.Normal.x, input.Normal.y, input.Normal.z);
		//float3x3 texSpaceMat = float3x3(vecTang, biTangent, vecNorm);
		////Convert normal from normal map to texture space and store in input.Normal
		//input.Normal = normalize(float4(mul(normalMap, texSpaceMat),1.0f));


		float4 ambient = float4(0.2f, 0.2f, 0.2f, 1.0f);
		float4 lightColor = float4(1.0f, 0.7f, 0.4f, 1.0f);
		float4 lightSource = input.cameraPos; //same as our camera since that is where we want our light to come from
		float4 lightDir = lightSource - input.pointOnSurface;
		float lightDistance = length(lightDir);
		lightDir = normalize(lightDir);
		float diffConstant = dot(lightDir.xyz, input.Normal.xyz);
		color = texture1.Sample(textureSample, input.TexCoord);




		colorShaded = color * lightColor * diffConstant * 3;
		colorShaded += ambient;

		if (input.hurtColor == 1)
		{
			colorShaded = colorShaded * float4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (input.hurtColor == 3)
		{
			colorShaded = colorShaded * float4(0.0f, 0.8f, 1.0f, 1.0f);
		}

		//color += colorShaded;
		//float3 colorShaded = input.Color * diffConstant;

	}
	if (input.hurtColor == 2)
	{
		color = colorShaded = texture1.Sample(textureSample, input.TexCoord);
		
	}

	return float4(colorShaded.xyz, color.w);
}