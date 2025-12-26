Texture2D Texture : register(t0);
SamplerState TextureSampler : register(s0);

struct PS_IN
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 direction_to_camera : TEXCOORD1;
};

float4 main(PS_IN input) : SV_Target
{
    return Texture.Sample(TextureSampler, input.texcoord);
}