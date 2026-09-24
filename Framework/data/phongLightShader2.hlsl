
#define NUM_LIGHTS 8

cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer CameraBuffer
{
    float3 cameraPosition;
    float padding;
};

cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

Texture2D shaderTextures[3];
SamplerState SampleType;

cbuffer PointLightColorBuffer
{
    float4 pointDiffuseColor[NUM_LIGHTS];
};

cbuffer PointLightPositionBuffer
{
    float4 pointLightPosition[NUM_LIGHTS];
};

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 viewDirection : TEXCOORD1;
    float3 lightPos1 : TEXCOORD2;
    float3 lightPos2 : TEXCOORD3;
    float3 lightPos3 : TEXCOORD4;
    float3 lightPos4 : TEXCOORD5; 
    float3 lightPos5 : TEXCOORD6;
    float3 lightPos6 : TEXCOORD7;
    float3 lightPos7 : TEXCOORD8;
    float3 lightPos8 : TEXCOORD9;
};

PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4 worldPosition;

    input.position.w = 1.0f;
    output.position = mul(input.position, worldMatrix);
    worldPosition = output.position;
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.tex = input.tex;

    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    output.tangent = normalize(mul(input.tangent, (float3x3) worldMatrix));
    output.binormal = normalize(mul(input.binormal, (float3x3) worldMatrix));

    worldPosition = mul(input.position, worldMatrix);
    output.viewDirection = normalize(cameraPosition.xyz - worldPosition.xyz);

    output.lightPos1 = pointLightPosition[0].xyz - worldPosition.xyz;
    output.lightPos2 = pointLightPosition[1].xyz - worldPosition.xyz;
    output.lightPos3 = pointLightPosition[2].xyz - worldPosition.xyz;
    output.lightPos4 = pointLightPosition[3].xyz - worldPosition.xyz;
    output.lightPos5 = pointLightPosition[4].xyz - worldPosition.xyz; 
    output.lightPos6 = pointLightPosition[5].xyz - worldPosition.xyz;
    output.lightPos7 = pointLightPosition[6].xyz - worldPosition.xyz;
    output.lightPos8 = pointLightPosition[7].xyz - worldPosition.xyz;
    return output;
}

float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
    float4 textureColor = shaderTextures[0].Sample(SampleType, input.tex);
    float4 bumpMap = shaderTextures[1].Sample(SampleType, input.tex);
    bumpMap = ((bumpMap - 0.5f) * 3.0f) + 0.5f;
    
    float3 bumpNormal = normalize(
        bumpMap.x * input.tangent +
        bumpMap.y * input.binormal +
        bumpMap.z * input.normal
    );

    float4 diffuseMap = shaderTextures[2].Sample(SampleType, input.tex);
    
    bool isWhite = (diffuseMap.r > 0.95f &&
                diffuseMap.g > 0.95f &&
                diffuseMap.b > 0.95f);

    float blendFactor = 3.0f;

// diffuseMap이 흰색이면 블렌딩하지 않음
    float4 baseColor;
    if (isWhite)
    {
        baseColor = textureColor;
    }
    else
    {
        baseColor = lerp(textureColor, diffuseMap, blendFactor);
    }
    

    float4 dcolor = ambientColor;
    float4 specular = float4(0, 0, 0, 0);

    float3 lightDir = normalize(-lightDirection);
    float lightIntensity = saturate(dot(bumpNormal, lightDir));

    if (lightIntensity > 0.0f)
    {
        dcolor += diffuseColor * lightIntensity;

        float3 reflection = normalize(2 * lightIntensity * bumpNormal - lightDir);
        float specPower = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
        specular = specPower * specularColor;
    }


    float4 pcolor1 = 0, pcolor2 = 0, pcolor3 = 0, pcolor4 = 0, pcolor5 = 0, pcolor6 = 0, pcolor7=0 ,pcolor8 = 0;

    // Light 1
    {
        float distance = length(input.lightPos1);
        float intens = (3.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos1)));
        pcolor1 = pointDiffuseColor[0] * intens;
    }

    // Light 2
    {
        float distance = length(input.lightPos2);
        float intens = (3.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos2)));
        pcolor2 = pointDiffuseColor[1] * intens;
    }

    // Light 3
    {
        float distance = length(input.lightPos3);
        float intens = (3.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos3)));
        pcolor3 = pointDiffuseColor[2] * intens;
    }


    {
        float distance = length(input.lightPos4);
        float intens = (3.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos4))); 
        pcolor4 = pointDiffuseColor[3] * intens;
    }
    
    {
        float distance = length(input.lightPos5);
        float intens = (40.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos5)));
        pcolor5 = pointDiffuseColor[4] * intens;
    }
    
    {
        float distance = length(input.lightPos6);
        float intens = (7.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos6)));
        pcolor6 = pointDiffuseColor[5] * intens;
    }
    
    {
        float distance = length(input.lightPos7);
        float intens = (7.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos7)));
        pcolor7 = pointDiffuseColor[6] * intens;
    }
    
    {
        float distance = length(input.lightPos8);
        float intens = (7.0f / distance) * saturate(dot(bumpNormal, normalize(input.lightPos8)));
        pcolor8 = pointDiffuseColor[7] * intens;
    }
    float4 pspec = 0;

    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos1), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos2), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos3), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos4), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos5), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos6), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos7), bumpNormal)), input.viewDirection)), specularPower);
    pspec += pow(saturate(dot(normalize(reflect(-normalize(input.lightPos8), bumpNormal)), input.viewDirection)), specularPower);
    float4 finalLight = saturate(dcolor + pcolor1 + pcolor2 + pcolor3 + pcolor4 + pcolor5 + pcolor6 + pcolor7 +pcolor8+ specular + pspec);
    return saturate(finalLight * baseColor);
}
