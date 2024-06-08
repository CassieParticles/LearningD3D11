SamplerState linearsampler : register(s0);
Texture2D ColourTexture : register(t0);

struct PSInput
{
    float4 position : SV_Position;
    float2 uv : UV0;
    
    float vertexBrightness : BRIGHTNESS;
};



struct PSOutput
{
    float4 colour : SV_Target0;
};

PSOutput Main(PSInput input)
{
    float3 colour = ColourTexture.Sample(linearsampler, input.uv).xyz;
    PSOutput output = { float4(mul(colour,input.vertexBrightness), 1.0) };
    return output;
}