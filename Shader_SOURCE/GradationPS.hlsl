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
    float4 sample = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    float3 color = sample.rgb;
    color = (1 - color) * float3(255/255, 203.f/255.f, 107.f/255.f);
    
    float alpha = sample.a;
    alpha = In.UV.y ;
    alpha = 1 - alpha;
    alpha = alpha ;
    
    return float4(color.rgb, alpha);
}