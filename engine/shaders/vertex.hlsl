struct VSInput
{
    float3 position : POSITION;
    float3 colour : COLOR0;
    uint vertexID : SV_VertexID;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 uv : UV0;
    
    float vertexBrightness:BRIGHTNESS;
};

StructuredBuffer<float> brightnessBuffer : register(t0);

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
    
    float vertexBrightness = brightnessBuffer.Load(input.vertexID);
    float4x4 finalMatrix = mul(cameraMatrix,transformationMatrix);

    VSOutput output = { mul(finalMatrix, float4(input.position, 1.0)), float2(input.colour.xy), vertexBrightness };
    return output;
}