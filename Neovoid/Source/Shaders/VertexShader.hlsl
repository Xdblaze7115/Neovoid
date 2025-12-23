cbuffer CBuffer : register(b0)
{
    matrix Model;
    matrix View;
    matrix Projection;
};

struct VS_IN
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    float4 local_pos = float4(input.position, 1.0f);
    float4 world_pos = mul(local_pos, Model);
    float4 view_pos = mul(world_pos, View);
    output.position = mul(view_pos, Projection);
    output.color = input.color;
    return output;
}