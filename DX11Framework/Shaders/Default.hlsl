Texture2D diffuseTex : register(t0);
Texture2D displacementTex : register(t1);
Texture2D normalTex : register(t2);
Texture2D specularTex : register(t3);
SamplerState bilinearSampler : register(s0);

#define MAX_LIGHTS 240

struct SimpleLight
{
    float4 Position;
	
    float3 Rotation;
    int Type;

    float3 DiffuseColor;
    int padding;

    float3 SpecColor;
    float SpecPower;
    float FalloffDistance;
    float FalloffDropDistance;
    float FalloffGradientCoefficiency;
    int padding2;
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

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 positionW : POSITION;
    float4 normW : NORMAL;
    float2 texCoord : TEXCOORDS;
};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL, float2 TexCoord : TEXCOORDS)
{      
    VS_Out output = (VS_Out)0;
        
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
    if (UseTexture > 0 && UseDiffuse > 0)
    {
        texColor = diffuseTex.Sample(bilinearSampler, input.texCoord);
    }

    //////////////// AMBIENT ////////////////
    float4 ambient = AmbientLight * texColor;

    
    float4 diffuse;
    float4 specular;
    float4 previousDiffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 previousSpecular = float4(0.0f, 0.0f, 0.0f, 0.0f);
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        SimpleLight currentLight = lights[i];
        if (currentLight.Type != 1)
        {
            continue;
        }
        
        // Distance from light to object.
        float lightDistance = distance(posW, currentLight.Position);
        float3 lightDir = normalize(posW - currentLight.Position); // From light to model position.

        // Create a gredient based off of the distance & falloff (https://www.ths-concepts.co.uk/how-to-calculate-gradients/)
        float falloffGradient = saturate(currentLight.FalloffDistance / ((lightDistance + currentLight.FalloffDropDistance) * currentLight.FalloffGradientCoefficiency));
        
        //////////////// DIFFUSE ////////////////
        // Calculate potential diffused amount:
        float4 potentialDiffuse = float4(currentLight.DiffuseColor, 1.0f) * texColor;

        // Get intensity from normal and lightdir.
        // Dot product compares the vector's rotation to the other vector, 1 is when they're the same, -1 is the inverse.
        float diffuseAmount = saturate(dot(-lightDir, normW.xyz));

        
        //// DIFFUSE COLOUR ////
        diffuse += ((potentialDiffuse * diffuseAmount) * falloffGradient);
        
        //////////////// SPECULAR ////////////////
        // 1. Get dir from light to surface.
        float3 dirFromLight = normalize(currentLight.Position.xyz - posW.xyz);
    
        // 2. reflection off of that.
        float3 reflection = reflect(lightDir, normW.xyz);
    
        // 3. dir towards camera.
        float3 dirToCamera = normalize(CameraPos - posW.xyz);
    
        // Check the specular intensity based off of the texture, if it doesnt have that, just use the base specpower.
        float specTextureReflect = 1;
        if (UseTexture > 0 && UseSpecular > 0)
        {
            specTextureReflect = specularTex.Sample(bilinearSampler, input.texCoord);
        }
    
        // Get the dot product from the reflection.
        float reflectionIntensity = saturate(dot(reflection, dirToCamera));
        reflectionIntensity = pow((reflectionIntensity * specTextureReflect), currentLight.SpecPower);
    
        //// SPECULAR COLOUR ////
        specular += ((float4(currentLight.SpecColor, 1.0f) * SpecularMaterial) * reflectionIntensity);
    }
   
    // I compiled all of the lighting types into this one line so it's easier for me to understand.
    float4 output = ambient + diffuse + specular;
    return output;
}