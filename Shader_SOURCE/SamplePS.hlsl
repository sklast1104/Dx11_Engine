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
    float4 color = (float4) 0.f;
        
    float2 resolution = Resolution;
    
    float2 uv = In.Pos.xy / resolution;
        
    color = postProcessTexture.Sample(anisotropicSampler, In.UV);
   
    color += float4(0.f, 0.f, 0.f, 1.f);
    
    //color.r *= 2.5f;
    
    return color;
}