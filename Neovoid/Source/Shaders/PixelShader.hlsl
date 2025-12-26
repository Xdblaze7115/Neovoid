Texture2D Texture : register(t0);
SamplerState TextureSampler : register(s0);

cbuffer Constant : register(b0)
{
    matrix Model;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
    float4 LightDirection;
};

struct PS_IN
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 direction_to_camera : TEXCOORD1;
};

float4 main(PS_IN input) : SV_Target
{
    // Normalize all vectors
    float3 normal = normalize(input.normal);
    float3 light_direction = normalize(LightDirection.xyz);
    float3 view_direction = normalize(input.direction_to_camera);
    
    // Properties
    float shininess = 256.0f; // Higher = sharper specular (more metallic)
    float specular_power = 0.5f; // Higher = brighter specular
    float ambient_strength = 0.1f; // Lower = darker ambient
    float diffuse_strength = 0.6f; // Lower = less diffuse
    float3 light_color = float3(1.0f, 1.0f, 1.0f); // Color of the light
    
    // Ambient Light
    float3 ambient_light = ambient_strength * light_color;
    
    // Diffuse Light
    float diffuse_amount = max(0.0f, dot(normal, light_direction));
    float3 diffuse_light = diffuse_strength * diffuse_amount * light_color;
    
    // Specular Light
    float3 reflect_direction = reflect(-light_direction, normal);
    float specular_amount = pow(max(0.0f, dot(view_direction, reflect_direction)), shininess);
    float3 specular_light = specular_power * specular_amount * light_color;
    
    // Combine all lighting
    float3 final_light_color = ambient_light + diffuse_light + specular_light;
    final_light_color = min(final_light_color, float3(1.0f, 1.0f, 1.0f));
    
    //return float4(final_light_color, 1.0f);
    return Texture.Sample(TextureSampler, input.texcoord) * float4(final_light_color, 1.0);
}