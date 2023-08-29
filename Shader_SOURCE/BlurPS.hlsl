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

static const float weights[5] = { 0.0545, 0.2442, 0.4026, 0.2442, 0.0545 };

float4 main(VSOut In) : SV_TARGET
{
    float3 color = (float4) 0.f;
        
    float2 uv = In.Pos.xy / Resolution;
        
    int i;
    int j;
    

    for (i = 0; i < 5; i++)
    {
        color += weights[i] * postProcessTexture.Sample(anisotropicSampler, In.UV + float2(1.f / 1280.f, 1.f / 720.f) * float(i - 2)).rgb;
    }
    
    return float4(color, 1.f);
}