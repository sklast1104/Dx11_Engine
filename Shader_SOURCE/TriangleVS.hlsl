
struct VSIn
{
    float3 Pos : POSITIONT;
    float4 Color : COLOR;
};

struct VSOut
 {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VSOut main(VSIn In)
{
    VSOut Out;
    Out.Pos = float4(In.Pos, 1.0f);
    Out.Color = In.Color;
    return Out;
}