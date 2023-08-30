#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float3 color0 = postProcessTexture.Sample(anisotropicSampler, In.UV).rgb;
    float3 color1 = postProcessTexture2.Sample(anisotropicSampler, In.UV).rgb;
    
    
    
    //return float4(color0, 1.f);
    //return float4((1.f * color0), 1.0f);
    float4 final = float4(color1 + (0.2f * color0), 1.0f);
    float r = saturate(final.r);
    float g = saturate(final.g);
    float b = saturate(final.b);
    
    return float4(r, g, b, 1.f);
    
    return float4(color1 + 0.0f * color0, 1.0f);
}