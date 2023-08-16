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
    //color = albedoTexture.Sample(anisotropicSampler, In.UV);
    
    float4 color = (float4) 0.0f;
    
    color = float4(0, 0, 0, In.UV.x + fadeVal);
    
    return color;
}