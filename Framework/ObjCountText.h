#pragma once
#include "TextClass.h"
class GraphicsClass;

class ObjCountText :
    public TextClass
{
public:

    ObjCountText(int x, int y, GraphicsClass* graphicsClass);
    ~ObjCountText() {}
    bool Frame() override;
private:
    GraphicsClass* m_Graphics;

};

