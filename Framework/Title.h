#pragma once
#include "BitmapClassOrtho.h"
class Title :
    public BitmapClassOrtho
{

public:
    Title(ID3D11Device* device, int screenWidth, int screenHeight, const WCHAR* textureFilename, int bitmapWidth, int bitmapHeight, int positionX, int positionY);
    ~Title();
    bool Render(ID3D11DeviceContext*) override;
};

