cbuffer MatrixBuffer
{
    matrix WVP;
};

TextureCube SkyMap;
SamplerState SampleType;

struct VertexInputType
{
    float3 position : POSITION;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD0;
};

PixelInputType SkyboxVertexShader(VertexInputType input)
{
    PixelInputType output;
    output.position = mul(float4(input.position, 1.0f), WVP).xyww;
    output.texCoord = input.position;

    return output;
}


float4 SkyboxPixelShader(PixelInputType input) : SV_TARGET
{
    return SkyMap.Sample(SampleType, input.texCoord);
}
