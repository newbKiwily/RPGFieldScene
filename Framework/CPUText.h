#pragma once
#include "TextClass.h"
#include "CpuClass.h"

class CPUText :
    public TextClass
{
public:
    CPUText(int x, int y);
    ~CPUText() {}
    bool Frame() override;

private:
};

