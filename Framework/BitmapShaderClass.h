#ifndef _BITMAPSHADERCLASS_H_
#define _BITMAPSHADERCLASS_H_

#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <fstream>

using namespace std;
using namespace DirectX;

class BitmapShaderClass
{
private:
    struct MatrixBufferType
    {
        XMMATRIX world;
        XMMATRIX view;
        XMMATRIX projection;
    };

public:
    BitmapShaderClass();
    BitmapShaderClass(const BitmapShaderClass&);
    ~BitmapShaderClass();

    bool Initialize(ID3D11Device*, HWND);
    void Shutdown();
    bool Render(ID3D11DeviceContext*, int indexCount,
        XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
        ID3D11ShaderResourceView* texture);

private:
    bool InitializeShader(HWND, const WCHAR* filename);
    void ShutdownShader();
    void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

    bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX,
        ID3D11ShaderResourceView*);
    void RenderShader(ID3D11DeviceContext*, int indexCount);

private:
    ID3D11VertexShader* m_vertexShader;
    ID3D11PixelShader* m_pixelShader;
    ID3D11InputLayout* m_layout;
    ID3D11Buffer* m_matrixBuffer;
    ID3D11SamplerState* m_sampleState;

    ID3D11Device* m_device;  // Create* È£Ãâ¿ë
};

#endif
