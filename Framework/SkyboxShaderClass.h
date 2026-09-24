#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
using namespace std;

class SkyboxShaderClass
{
private:
    struct MatrixBufferType
    {
        XMMATRIX WVP;
    };
    struct SkyVertex 
    { 
        XMFLOAT3 pos; 
    };
public:
    SkyboxShaderClass();
    ~SkyboxShaderClass();

    bool Initialize(ID3D11Device*, HWND, const WCHAR*);
    void Shutdown();
    bool Render(ID3D11DeviceContext* deviceContext,
        XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

private:
    bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
    void ShutdownShader();
    bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX,
        ID3D11ShaderResourceView*, ID3D11SamplerState*);
    void RenderShader(ID3D11DeviceContext*, int);
    void CreateSphere(ID3D11Device* device,const WCHAR*, HWND hwnd);
    bool CreateSkyBoxBuffer(ID3D11Device* device,const WCHAR* ,HWND hwnd);
private:
    ID3D11VertexShader* m_vertexShader;
    ID3D11PixelShader* m_pixelShader;
    ID3D11InputLayout* m_layout;
    ID3D11Buffer* m_matrixBuffer;

    float radius;
    SkyVertex vertices[8];
    unsigned long indices[36];
    int m_skyIndexCount = 0;

    ID3D11Buffer* m_skyVB = nullptr;
    ID3D11Buffer* m_skyIB = nullptr;

    ID3D11ShaderResourceView* m_skySRV = nullptr;
    ID3D11SamplerState* m_skySampler = nullptr;

    ID3D11DepthStencilState* m_skyDepthState = nullptr;
    ID3D11RasterizerState* m_skyRasterState = nullptr;
};