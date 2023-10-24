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
    
    float packing;
    
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
    float4 color : COLOR;
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
    float4 output = input.color;
    
    float4 texColor = DiffuseMaterial;
    if (UseTexture > 0)
    {
        texColor = diffuseTex.Sample(bilinearSampler, input.texCoord);
    }
    
    //////////////// AMBIENT ////////////////
    float4 ambient = AmbientLight * texColor;

    //////////////// DIFFUSE ////////////////
    float4 posW = input.positionW;
    float4 normW = normalize(input.normW);
    
    // Calculate potential diffused amount:
    float4 potentialDiffuse = DiffuseLight * texColor;
    
    // Get intensity from normal and lightdir.
    // Lambert's cosine law: Cos(dot(N, L))
    float diffuseAmount = saturate(dot(LightRotation, normW.xyz));
    
    float4 color = potentialDiffuse * diffuseAmount;
    return color;
    
    // TODO: Rework ALL of this garbo.
    /*
    float4 posW = input.positionW; // Vertex position in worldspace.
    float4 normW = normalize(input.normW);
    
    float4 lightPos = mul(LightPosition, World);
    float3 lightDir = normalize(posW - lightPos); // From light to model position.
    
    float spotlightIntensity = dot(lightDir, LightRotation);
    
    //////////////// DIFFUSE ////////////////
    // Calculate potential diffused amount:
    float4 potentialDiffuse = DiffuseLight * DiffuseMaterial;

    // Get intensity from normal and lightdir.
    // Lambert's cosine law: Cos(dot(N, L))
    float diffuseAmount = saturate(dot(-lightDir, normW.xyz));


    
    //////////////// SPECULAR ////////////////
    // 1. Get dir from light to surface.
    float3 dirFromLight = normalize(posW.xyz - lightPos.xyz);
    
    // 2. reflection off of that.
    float3 reflection = reflect(-dirFromLight, normW.xyz);
    
    // 3. dir towards camera.
    float3 dirToCamera = normalize(CameraPos - posW.xyz);
    
    // Get the dot product from the reflection.
    float reflectionIntensity = saturate(dot(reflection, dirToCamera));
    reflectionIntensity = pow(reflectionIntensity, 5);   
    
    //////////////// Lighting Compilation //////////////// 
    float4 diffuse = (potentialDiffuse * diffuseAmount);
    float4 specular = (SpecularLight * SpecularMaterial) * reflectionIntensity;

    float4 colour;
        
    // I compiled all of the lighting types into this one line so it's easier for me to understand.
    output = (ambient + diffuseAmount + specular);
    
    return output;
    */
}