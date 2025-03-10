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
    float2 texCoord : TEXCOORD;
};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL, float2 TexCoord : TEXCOORDS)
{      
    VS_Out output = (VS_Out)0;

    float4x4 identityMatrix = { 1,0,0,0,
                                0,1,0,0,
                                0,0,1,0,
                                0,0,0,1, }; 

    

    float4 ViewSpace = float4(Position, 1.0f);
    ViewSpace = mul(ViewSpace, World);
    ViewSpace = mul(ViewSpace, View);
    ViewSpace = mul(ViewSpace, Projection);
    

    output.position = ViewSpace;


    output.texCoord = TexCoord;
    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    float4 color = diffuseTex.Sample(bilinearSampler, input.texCoord);
    return color;
}