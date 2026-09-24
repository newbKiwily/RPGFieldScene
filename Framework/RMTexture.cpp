#include "pch.h"
#include "RMTexture.h"
#include "DDSTextureLoader.h"
#include "d3dclass.h"
//Load Texture
ID3D11ShaderResourceView* RMTexture::LoadTexture(wstring fileName)
{
    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11Resource* tex = nullptr;

    HRESULT hr = DirectX::CreateDDSTextureFromFile(
        D3DClass::GetInstance().GetDevice(),
        fileName.c_str(),
        &tex,
        &srv
    );

    if (FAILED(hr))
        return nullptr;

    SAFE_RELEASE(tex);
    return srv;
}

//Load Resource
Texture* RMTexture::loadResource(wstring fileName, void* param)
{
	Texture* tex = new Texture;
	tex->name = MYUTIL::getFileName(fileName.c_str());
	tex->data = LoadTexture(fileName);


	if (!tex->data) {
		SAFE_DELETE(tex);
	}

	return tex;
}

//Delete Texture
void RMTexture::releaseResource(Texture* data)
{
	SAFE_DELETE(data);
}
