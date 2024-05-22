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

cbuffer transformation
{
    float4x4 transformationMatrix;
};

VSOutput Main(VSInput input)
{
    VSOutput output = { mul(transformationMatrix,float4(input.position, 1.0)), float3(input.colour) };
    return output;
}