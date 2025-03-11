SamplerState bilinearSampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;
}

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 positionW : POSITION;

};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL, float2 TexCoord : TEXCOORDS)
{
    VS_Out output = (VS_Out) 0;

    float4 Pos4 = float4(Position, 1.0f);
    output.position = mul(Pos4, World);
    output.positionW = output.position;
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    float4 baseWhite = float4(1,1,1,1);
    return baseWhite * (input.position.z / input.positionW.w);

}
