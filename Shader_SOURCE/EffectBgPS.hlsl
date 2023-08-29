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
    float4 color = albedoTexture.Sample(anisotropicSampler, float2(In.UV.x + delta * 0.9, In.UV.y));
    
     //In.UV;
    color.a = (1 - (In.UV.y + 0.5));
    
    return color;
}