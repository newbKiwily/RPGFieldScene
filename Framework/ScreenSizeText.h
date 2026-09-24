#pragma once
#include "TextClass.h"
class GraphicsClass;

class ScreenSizeText :
    public TextClass
{
public:
    ScreenSizeText(int x, int y, GraphicsClass* graphicsClass);
    ~ScreenSizeText() {}

    bool Frame() override;
private:
    GraphicsClass* m_Graphics;
};

