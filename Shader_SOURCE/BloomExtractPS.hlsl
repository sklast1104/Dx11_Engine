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
    float3 color = (float4) 0.f;
        
    float2 uv = In.Pos.xy / Resolution;
        
    color = postProcessTexture.Sample(anisotropicSampler, In.UV);
    
    float l = (color.r + color.g + color.b) / 3;
    
    if (l > 0.7f)
    {
        return float4(color, 1.0f);
        
        
        
    }
    else
    {
        return float4(0.f, 0.f, 0.f, 1.f);
    }
    
    return float4(color, 1.f);
}