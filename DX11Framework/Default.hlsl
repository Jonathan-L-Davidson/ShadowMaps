Texture2D diffuseTex : register(t0);
SamplerState bilinearSampler : register(s0);


cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;
    
    float4 AmbientLight;
    float4 DiffuseLight;
    float4 DiffuseMaterial;
    
    float4 LightPosition;
    float3 LightRotation;
    float  LightFalloff;
    
    float4 SpecularLight;
    float4 SpecularMaterial;
    float  SpecPower;
    
    float3 CameraPos;
    uint UseTexture;
}

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 positionW : POSITION;
    float4 normW : NORMAL;
    float2 texCoord : TEXCOORDS;
    float4 lightPositionW : LIGHT_POSITION;
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
    
    output.lightPositionW = LightPosition;
    output.texCoord = TexCoord;
    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    float4 posW = input.positionW; // Vertex position in worldspace.
    float4 normW = normalize(input.normW);
    
    // Worldspace light calculations.
    float4 lightPos = input.lightPositionW;
    float3 lightDir = normalize(posW - lightPos); // From light to model position.
  
    
    //////////////// TEXTURE ////////////////
    float4 texColor = DiffuseMaterial;
    if (UseTexture > 0)
    {
        texColor = diffuseTex.Sample(bilinearSampler, input.texCoord);
    }
    
    // Distance from light to object.
    float lightDistance = distance(posW, lightPos);

    
    //////////////// AMBIENT ////////////////
    float4 ambient = AmbientLight * texColor;
    
    
    
    //////////////// DIFFUSE ////////////////
    // Calculate potential diffused amount:
    float4 potentialDiffuse = DiffuseLight * texColor;

    // Get intensity from normal and lightdir.
    // Dot product compares the vector's rotation to the other vector, 1 is when they're the same, -1 is the inverse.
    float diffuseAmount = saturate(dot(-lightDir, normW.xyz));

    //// DIFFUSE COLOUR ////
    float4 diffuse = potentialDiffuse * diffuseAmount;
    
    
    
    
    //////////////// SPECULAR ////////////////
    // 1. Get dir from light to surface.
    float3 dirFromLight = normalize(lightPos.xyz - posW.xyz);
    
    // 2. reflection off of that.
    float3 reflection = reflect(lightDir, normW.xyz);
    
    // 3. dir towards camera.
    float3 dirToCamera = normalize(CameraPos - posW.xyz);
    
    // Get the dot product from the reflection.
    float reflectionIntensity = saturate(dot(reflection, dirToCamera));
    reflectionIntensity = pow(reflectionIntensity, 5 * lightDistance);
    
    //// SPECULAR COLOUR ////
    float4 specular = (SpecularLight * SpecularMaterial) * reflectionIntensity;
    
    //////////////// Lighting Compilation ////////////////
    // Create a gredient based off of the distance & falloff (https://www.ths-concepts.co.uk/how-to-calculate-gradients/)
    float falloffGradient = saturate(LightFalloff / lightDistance);
    
    
    // I compiled all of the lighting types into this one line so it's easier for me to understand.
    float4 output = ambient + ((diffuse + specular) * falloffGradient);
    
    return output;
}