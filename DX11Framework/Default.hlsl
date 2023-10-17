cbuffer ConstantBuffer : register(b0)
{
    float4x4 Projection;
    float4x4 View;
    float4x4 World;
    float4 DiffuseLight;
    float4 DiffuseMaterial;
    float3 LightDir;
    float Time;
}

struct VS_Out
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VS_Out VS_main(float3 Position : POSITION, float3 Normal : NORMAL)
{   
    
    
    
    VS_Out output = (VS_Out)0;

    float4 Pos4 = float4(Position, 1.0f);
    output.position = mul(Pos4, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    
    output.color = DiffuseMaterial;
    
    return output;
}

float4 PS_main(VS_Out input) : SV_TARGET
{
    float4 output = input.color;
    
    //const float4 kRGBToYPrime = float4(0.299f, 0.587f, 0.114f, output.w);
    //const float4 kRGBToI = float4(0.596, -0.275, -0.321, output.w);
    //const float4 kRGBToQ = float4(0.212, -0.523, 0.311, output.w);

    //const float4 kYIQToR = float4(1.0, 0.956, 0.621, output.w);
    //const float4 kYIQToG = float4(1.0, -0.272, -0.647, output.w);
    //const float4 kYIQToB = float4(1.0, -1.107, 1.704, output.w);

    //float YPrime = dot(output, kRGBToYPrime);
    //float I = dot(output, kRGBToI);
    //float Q = dot(output, kRGBToQ);
    
    //float hue = atan2(Q, I);
    
    //float chroma = sqrt(I * I + Q * Q);

    //hue += (input.position.x + cos(Time)) / 200;
    //hue += (input.position.y + sin(Time)) / 200;

    //Q = chroma * sin(hue);
    //I = chroma * cos(hue);

    //float4 yIQ = float4(YPrime, I, Q, 0);

    //return float4(dot(yIQ, kYIQToR), dot(yIQ, kYIQToG), dot(yIQ, kYIQToB), output.w);    
    return output;
}