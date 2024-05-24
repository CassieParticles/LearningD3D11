struct VSInput
{
    float3 position : POSITION;
    float3 colour : COLOR0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 colour : COLOR0;
};

cbuffer camera : register(b1)
{
    float4x4 cameraMatrix;
}

cbuffer transformation : register(b2)
{
    float4x4 transformationMatrix;
};

VSOutput Main(VSInput input)
{
    float4x4 finalMatrix = mul(cameraMatrix,transformationMatrix);

    VSOutput output = { mul(finalMatrix, float4(input.position, 1.0)), float3(input.colour) };
    return output;
}