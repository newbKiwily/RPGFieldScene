#pragma once
#include "TextClass.h"
#include "FpsClass.h"
class FpsText :
    public TextClass
{
public:
    FpsText(int x, int y);
    ~FpsText() {}
    bool Frame() override;
};

