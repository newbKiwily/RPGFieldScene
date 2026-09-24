#pragma once
#include "TextClass.h"
class GraphicsClass;

class PolyCountText :
    public TextClass
{
public:
    PolyCountText(int x, int y, GraphicsClass* graphicsClass);
    ~PolyCountText() {}

    bool Frame() override;                                      //나중에 모델이 추가 또는 삭제될 시 폴리카운터도 그에 맞게 동적으로 수정되도록 고쳐야함
private:
    GraphicsClass* m_Graphics;
};