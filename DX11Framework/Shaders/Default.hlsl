Texture2D diffuseTex : register(t0);
Texture2D displacementTex : register(t1);
Texture2D normalTex : register(t2);
Texture2D specularTex : register(t3);
SamplerState bilinearSampler : register(s0);
Texture2D shadowMap : register(t0);

#define MAX_LIGHTS 3
#define LIGHT_DISABLED 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2
#define LIGHT_DIRECTIONAL 3

struct SimpleLight
{
    float4 Position;

    float3 Rotation;
    int Type;

    float3 DiffuseColor;
    float ConeCoef;

    float3 SpecColor;
    float SpecPower;

    float4x4 View;
    float4x4 Projection;

    float FalloffDistance;
    int ShadowCaster;
    int pad1;
    int pad2;
};

cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;

    float4 AmbientLight;
    float4 DiffuseMaterial;
    float4 SpecularMaterial;

    SimpleLight lights[MAX_LIGHTS];

    float3 CameraPos;
    uint UseTexture;

    uint UseDiffuse;
    uint UseDisplacement;
    uint UseNormal;
    uint UseSpecular;
}

struct LightInfo
{
    float distance;
    float3 direction;
    int lightIndex;
};

float4 CalculateDiffuse(LightInfo lightInfo, float4 pixelPos, float4 pixelNorm, float4 texColor, SimpleLight light)
{
	// Calculate potential diffused amount:
    float4 potentialDiffuse = float4(light.DiffuseColor, 1.0f) * texColor;

	// Get intensity from normal and lightdir.
	// Dot product compares the vector's rotation to the other vector, 1 is when they're the same, -1 is the inverse.
    float diffuseAmount = saturate(dot(-lightInfo.direction, pixelNorm.xyz));

	// Create a gredient based off of the distance & falloff (https://www.ths-concepts.co.uk/how-to-calculate-gradients/)
	//float falloffGradient = saturate(light.FalloffDistance / ((lightInfo.distance + light.FalloffDropDistance) * light.FalloffGradientCoefficiency));
    return (potentialDiffuse * diffuseAmount);
}

float4 CalculateSpecular(LightInfo lightInfo, float4 pixelPos, float4 pixelNorm, float specSample, SimpleLight light, float3 cameraPos)
{
    //////////////// SPECULAR ////////////////
    // 1. Get dir from light to surface.
    float3 dirFromLight = normalize(light.Position.xyz - pixelPos.xyz);
    
    // 2. reflection off of that.
    float3 reflection = reflect(-dirFromLight, pixelNorm.xyz);
    
    // 3. dir towards camera.
    float3 dirToCamera = normalize(CameraPos - pixelPos.xyz);

	// Get the dot product from the reflection.
    float reflectionIntensity = saturate(dot(reflection, dirToCamera));
    reflectionIntensity = pow((reflectionIntensity * specSample), light.SpecPower);
    
    return ((float4(light.SpecColor, 1.0f) * specSample) * reflectionIntensity) / (lightInfo.distance / 3);
};

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 positionW : POSITION;
    float4 normW : NORMAL;
    float2 texCoord : TEXCOORDS;
};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL, float2 TexCoord : TEXCOORDS)
{
    VS_Out output = (VS_Out) 0;

	// Move our normal to world space.
    float4 normW = mul(float4(Normal, 0), World);
    normW = normalize(normW);
    output.normW = normW;

    float4 Pos4 = float4(Position, 1.0f);
    output.position = mul(Pos4, World);
    output.positionW = output.position;
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.texCoord = TexCoord;
    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    float4 posW = input.positionW; // Vertex position in worldspace.
    float4 normW = normalize(input.normW);

	//////////////// TEXTURE ////////////////
    float4 texColor = DiffuseMaterial;
    if (UseTexture && UseDiffuse)
    {
        texColor = diffuseTex.Sample(bilinearSampler, input.texCoord);
    }
	
	// Check the specular intensity based off of the texture, if it doesnt have that, just use the base specpower.
    float specTextureReflect = 1;
    if (UseTexture > 0 && UseSpecular > 0)
    {
        specTextureReflect = specularTex.Sample(bilinearSampler, input.texCoord);
    }

	//////////////// AMBIENT ////////////////
    float4 ambient = AmbientLight * texColor;

    float4 diffuse = 0;
    float4 specular = 0;
    float cone = 1.0f;
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].Type == LIGHT_DISABLED)
        {
            continue;
        }
        
        LightInfo light;
        light.distance = distance(posW, lights[i].Position);
        light.direction = (lights[i].Type == LIGHT_DIRECTIONAL) ? -lights[i].Rotation : normalize(posW - lights[i].Position); // From light to pixel position.
        light.lightIndex = i;
        
        cone = 1.0f;
        if (lights[i].Type == LIGHT_SPOT)
        {
            cone = dot(-light.direction, lights[i].Rotation.xyz);

            if (cone <= lights[i].ConeCoef)
            {
                cone = 0.0f;
            }
        }
        
        float falloff = 1.0f;
        if (lights[i].Type != LIGHT_DIRECTIONAL)
        {
            falloff = lights[i].FalloffDistance / (light.distance * light.distance);
        }
        
        diffuse += (CalculateDiffuse(light, posW, normW, texColor, lights[i]) * cone) * falloff;
			
        //specular += CalculateSpecular(light, posW, normW, specTextureReflect, lights[i], CameraPos) * cone / lights[i].ConeCoef;

    }

	// I compiled all of the lighting types into this one line so it's easier for me to understand.
    return ambient + diffuse + specular;
}
