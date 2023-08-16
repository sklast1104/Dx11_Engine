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
    float4 color;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    float alpha;
    
    if (In.UV.x > hpPercent)
    {
        alpha = 1;
    }
    else
    {
        alpha = 0;
    }
    
    return float4(color.r, color.g, color.b, 1-alpha);
}