
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VSOut
 {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

cbuffer Transform : register(b0)
{
    float4 Pos;
}

VSOut main(VSIn In)
{
    VSOut Out;
    
    Out.Pos = float4(In.Pos, 1.0f);
    Out.Pos += Pos;
    Out.Color = In.Color;
    
    return Out;
}