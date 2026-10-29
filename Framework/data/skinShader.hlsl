cbuffer CameraBuffer : register(b0)
{
    float4x4 matView;
    float4x4 matProj;
};

cbuffer TransBuffer : register(b1)
{
    float4x4 matWorld;
};

cbuffer ColorBuffer : register(b2)
{
    float4 fColor;
};

cbuffer BoneBuffer : register(b3)
{
    float4x4 matBones[128];
};

float4x4 IdentityMatrix =
{
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
};

struct VertexInputType
{
    float3 position : POSITION;
    float2 tex : TEXCOORD;
    uint4 boneIdx : BONEID;
    float4 weight : WEIGHT;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD;
    float3 worldPosition : TEXCOORD1;
    float3 normal : NORMAL;
};

Texture2D shaderTexture;
SamplerState SampleType;

// Vertex Shader
PixelInputType vsMain(VertexInputType input)
{
    PixelInputType output;
	
    float finalWeight = 1 - (input.weight[0] + input.weight[1] + input.weight[2]);
	
    float4x4 boneTransform = matBones[input.boneIdx[0]] * input.weight[0];
    boneTransform += matBones[input.boneIdx[1]] * input.weight[1];
    boneTransform += matBones[input.boneIdx[2]] * input.weight[2];
    boneTransform += matBones[input.boneIdx[3]] * finalWeight;
	
    output.position = mul(float4(input.position, 1.f), boneTransform);
    output.position = mul(output.position, matWorld);
    output.worldPosition = output.position.xyz;
    output.normal = normalize(mul(mul(input.normal, (float3x3)boneTransform), (float3x3)matWorld));
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProj);
    
    output.tex = input.tex;

    return output;
}

#define NPC_NUM_LIGHTS 8

cbuffer NpcLightBuffer : register(b0)
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

cbuffer NpcPointColorBuffer : register(b1)
{
    float4 pointDiffuseColor[NPC_NUM_LIGHTS];
};

cbuffer NpcPointPositionBuffer : register(b2)
{
    float4 pointLightPosition[NPC_NUM_LIGHTS];
};

cbuffer NpcEyeBuffer : register(b3)
{
    float3 cameraPosition;
    float eyePadding;
};

float4 psMain(PixelInputType input) : SV_TARGET
{
    float4 textureColor = shaderTexture.Sample(SampleType, input.tex);
    float3 normal = normalize(input.normal);
    float3 viewDirection = normalize(cameraPosition - input.worldPosition);
    float3 lightDir = normalize(-lightDirection);
    float diffuseAmount = saturate(dot(normal, lightDir));
    float3 lighting = ambientColor.rgb + diffuseColor.rgb * diffuseAmount;
    float3 highlight = float3(0.0f, 0.0f, 0.0f);
    if (diffuseAmount > 0.0f)
    {
        highlight = specularColor.rgb * pow(saturate(dot(reflect(-lightDir, normal), viewDirection)), specularPower);
    }

    for (int i = 0; i < NPC_NUM_LIGHTS; ++i)
    {
        float3 toLight = pointLightPosition[i].xyz - input.worldPosition;
        float distanceToLight = max(length(toLight), 0.001f);
        float3 pointDir = toLight / distanceToLight;
        float strength = (i == 4) ? 44.0f : ((i >= 5) ? 8.4f : 3.6f);
        float attenuation = strength / distanceToLight;
        float pointDiffuse = saturate(dot(normal, pointDir));
        lighting += pointDiffuseColor[i].rgb * attenuation * pointDiffuse;
        if (pointDiffuse > 0.0f)
        {
            highlight += pointDiffuseColor[i].rgb * specularColor.rgb * attenuation *
                pow(saturate(dot(reflect(-pointDir, normal), viewDirection)), specularPower);
        }
    }
    return float4(saturate(lerp(textureColor.rgb, textureColor.rgb * lighting + highlight, 1.0f)), textureColor.a);
}
