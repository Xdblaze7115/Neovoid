cbuffer Constant : register(b0)
{
    matrix Model;
    matrix View;
    matrix Projection;
};

struct VS_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    float4 local_pos = float4(input.position, 1.0f);
    float4 world_pos = mul(local_pos, Model);
    float4 view_pos = mul(world_pos, View);
    float4 projection_pos = mul(view_pos, Projection);
    
    output.position = projection_pos;
    output.normal = input.normal;
    output.texcoord = input.texcoord;
    return output;
}