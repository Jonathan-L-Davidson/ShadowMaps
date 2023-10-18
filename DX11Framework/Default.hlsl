cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;
    
    float4 AmbientLight;
    float4 DiffuseLight;
    float4 DiffuseMaterial;
    float3 LightDir;
    
    float4 SpecularLight;
    float4 SpecularMaterial;
    float  SpecPower;
    
    float3 CameraPos;
    
    
    float Time;
}

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 positionW : POSITION;
    float4 normW : NORMAL;
    float4 color : COLOR;
};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL)
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
    
    output.color = AmbientLight;
    
    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    float4 output = input.color;
    
    float4 posW = input.positionW; // Vertex position in worldspace.
    float4 normW = normalize(input.normW);
    
    // Calculate potential diffused amount:
    float4 potentialDiffuse = DiffuseLight * DiffuseMaterial;

    // Get intensity from normal and lightdir.
    // Lambert's cosine law: Cos(dot(N, L))
    float diffuseAmount = saturate(dot(-LightDir, normW.xyz));

    output += potentialDiffuse * diffuseAmount;

    // 1. Get dir from light to surface.
    float3 dirFromLight = normalize(posW.xyz - LightDir);
    
    // 2. reflection off of that.
    float3 reflection = reflect(dirFromLight, normW.xyz);
    
    // 3. dir towards camera.
    float3 dirToCamera = normalize(CameraPos - posW.xyz);
    
    float reflectionIntensity = saturate(dot(reflection, dirToCamera));
    reflectionIntensity = pow(reflectionIntensity, 5);
    output += (SpecularLight * SpecularMaterial) * reflectionIntensity;
    return output;
}