#include "SkyboxShaderClass.h"
#include "DDSTextureLoader.h"
SkyboxShaderClass::SkyboxShaderClass()
{
    m_vertexShader = 0;
    m_pixelShader = 0;
    m_layout = 0;
    m_matrixBuffer = 0;
    radius = 50.0f;
    
}

SkyboxShaderClass::~SkyboxShaderClass() {}

bool SkyboxShaderClass::Initialize(ID3D11Device* device, HWND hwnd, const WCHAR* texturefile)
{   

    return InitializeShader(device, hwnd, L"./data/skyBoxShader.hlsl",texturefile);
}

void SkyboxShaderClass::Shutdown()
{   
    ShutdownShader();
    if (m_skyVB) { m_skyVB->Release(); m_skyVB = nullptr; }
    if (m_skyIB) { m_skyIB->Release(); m_skyIB = nullptr; }
    if (m_skySRV) { m_skySRV->Release(); m_skySRV = nullptr; }
    if (m_skySampler) { m_skySampler->Release(); m_skySampler = nullptr; }
    if (m_skyDepthState) { m_skyDepthState->Release(); m_skyDepthState = nullptr; }
    if (m_skyRasterState) { m_skyRasterState->Release(); m_skyRasterState = nullptr; }
}

bool SkyboxShaderClass::Render(ID3D11DeviceContext* deviceContext,
    XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
    deviceContext->OMSetDepthStencilState(m_skyDepthState, 0);
    deviceContext->RSSetState(m_skyRasterState);

    // 버텍스/인덱스 버퍼 설정
    UINT stride = sizeof(XMFLOAT3);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, &m_skyVB, &stride, &offset);
    deviceContext->IASetIndexBuffer(m_skyIB, DXGI_FORMAT_R32_UINT, 0);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    if (!SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, m_skySRV, m_skySampler))
        return false;



    RenderShader(deviceContext, m_skyIndexCount);
    deviceContext->OMSetDepthStencilState(nullptr, 0);
    deviceContext->RSSetState(nullptr);
    return true;
}

bool SkyboxShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, const WCHAR* filename, const WCHAR* texturefile)
{   
    HRESULT result;
    ID3D10Blob* vertexShaderBuffer = 0;
    ID3D10Blob* pixelShaderBuffer = 0;
    ID3D10Blob* errorMessage = 0;

    // Compile shaders
    result = D3DCompileFromFile(filename, NULL, NULL, "SkyboxVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
    if (FAILED(result))
    {
        MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt", filename, MB_OK);
    }

    result = D3DCompileFromFile(filename, NULL, NULL, "SkyboxPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
    if (FAILED(result))
    {
        MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt", filename, MB_OK);
    }

    // Create shaders
    device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
    device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);

    // Define input layout
    D3D11_INPUT_ELEMENT_DESC layoutDesc[1];
    layoutDesc[0].SemanticName = "POSITION";
    layoutDesc[0].SemanticIndex = 0;
    layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    layoutDesc[0].InputSlot = 0;
    layoutDesc[0].AlignedByteOffset = 0;
    layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    layoutDesc[0].InstanceDataStepRate = 0;

    device->CreateInputLayout(layoutDesc, 1, vertexShaderBuffer->GetBufferPointer(),
        vertexShaderBuffer->GetBufferSize(), &m_layout);

    vertexShaderBuffer->Release();
    pixelShaderBuffer->Release();

    // Matrix buffer
    D3D11_BUFFER_DESC matrixBufferDesc = {};
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

    CreateSphere(device,texturefile,hwnd);

    return true;
}

void SkyboxShaderClass::ShutdownShader()
{
    if (m_matrixBuffer) { m_matrixBuffer->Release(); m_matrixBuffer = 0; }
    if (m_layout) { m_layout->Release(); m_layout = 0; }
    if (m_pixelShader) { m_pixelShader->Release(); m_pixelShader = 0; }
    if (m_vertexShader) { m_vertexShader->Release(); m_vertexShader = 0; }
}



bool SkyboxShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext,
    XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* cubeMap, ID3D11SamplerState* sampler)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    MatrixBufferType* dataPtr;

    XMMATRIX WVP = worldMatrix * viewMatrix * projectionMatrix;
    WVP = XMMatrixTranspose(WVP);

    deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    dataPtr = (MatrixBufferType*)mappedResource.pData;
    dataPtr->WVP = WVP;
    deviceContext->Unmap(m_matrixBuffer, 0);

    deviceContext->VSSetConstantBuffers(0, 1, &m_matrixBuffer);
    deviceContext->PSSetShaderResources(0, 1, &cubeMap);
    deviceContext->PSSetSamplers(0, 1, &sampler);

    return true;
}

void SkyboxShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    deviceContext->IASetInputLayout(m_layout);
    deviceContext->VSSetShader(m_vertexShader, 0, 0);
    deviceContext->PSSetShader(m_pixelShader, 0, 0);
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

void SkyboxShaderClass::CreateSphere(ID3D11Device* device,const WCHAR* filename, HWND hwnd)
{


    vertices[0] = { XMFLOAT3(-radius,  radius, -radius) };
    vertices[1] = { XMFLOAT3(radius,  radius, -radius) };
    vertices[2] = { XMFLOAT3(radius,  radius,  radius) };
    vertices[3] = { XMFLOAT3(-radius,  radius,  radius) };
    vertices[4] = { XMFLOAT3(-radius, -radius, -radius) };
    vertices[5] = { XMFLOAT3(radius, -radius, -radius) };
    vertices[6] = { XMFLOAT3(radius, -radius,  radius) };
    vertices[7] = { XMFLOAT3(-radius, -radius,  radius) };

    unsigned long temp_indices[] = {

        1, 2, 6, 1, 6, 5,

        0, 4, 7, 0, 7, 3,

        0, 1, 2, 0, 2, 3,

        4, 5, 6, 4, 6, 7,

        3, 2, 6, 3, 6, 7,

        0, 1, 5, 0, 5, 4
    };

    memcpy(indices, temp_indices, sizeof(temp_indices));
    m_skyIndexCount = _countof(indices);

    CreateSkyBoxBuffer(device,filename,hwnd);
}

bool SkyboxShaderClass::CreateSkyBoxBuffer(ID3D11Device* device,const WCHAR* filename,HWND hwnd)
{   

    HRESULT hr;

    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = sizeof(SkyVertex) * _countof(vertices);
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinit = {};
    vinit.pSysMem = vertices;
    hr = device->CreateBuffer(&vbd, &vinit, &m_skyVB);
    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to create skybox vertex buffer", L"Error", MB_OK);
        return false;
    }

    // 인덱스 버퍼 생성
    D3D11_BUFFER_DESC ibd = {};
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = sizeof(unsigned long) * m_skyIndexCount;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinit = {};
    iinit.pSysMem = indices;
    hr = device->CreateBuffer(&ibd, &iinit, &m_skyIB);
    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to create skybox index buffer", L"Error", MB_OK);
        return false;
    }


    hr = CreateDDSTextureFromFileEx(
        device,
        filename,
        0,
        D3D11_USAGE_IMMUTABLE,
        D3D11_BIND_SHADER_RESOURCE,
        0,
        D3D11_RESOURCE_MISC_TEXTURECUBE,
        false,
        nullptr,
        &m_skySRV
    );

    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to load skymap.dds", L"Error", MB_OK);
        return false;
    }

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = device->CreateSamplerState(&sampDesc, &m_skySampler);
    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to create skybox sampler", L"Error", MB_OK);
        return false;
    }

    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    hr = device->CreateDepthStencilState(&dsDesc, &m_skyDepthState);
    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to create skybox depth state", L"Error", MB_OK);
        return false;
    }

    D3D11_RASTERIZER_DESC rsDesc = {};
    rsDesc.CullMode = D3D11_CULL_NONE;
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.FrontCounterClockwise = false;
    hr = device->CreateRasterizerState(&rsDesc, &m_skyRasterState);
    if (FAILED(hr)) {
        MessageBox(hwnd, L"Failed to create skybox rasterizer state", L"Error", MB_OK);
        return false;
    }
}
