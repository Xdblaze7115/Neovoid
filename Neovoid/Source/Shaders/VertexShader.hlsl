cbuffer Constant : register(b0)
{
    matrix Model;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
    float4 LightDirection;
};

struct VS_IN
{
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 direction_to_camera: TEXCOORD1;
};

VS_OUT main(VS_IN input)
{
    VS_OUT output;
    float4 local_position = float4(input.position, 1.0f);
    float4 world_position = mul(local_position, Model);
    float4 view_position = mul(world_position, View);
    float4 projection_position = mul(view_position, Projection);
    
    output.position = projection_position;
    output.texcoord = input.texcoord;
    output.normal = mul(float4(input.normal, 0.0f), Model).xyz;
    output.direction_to_camera = normalize(CameraPosition.xyz - world_position.xyz);
    return output;
}