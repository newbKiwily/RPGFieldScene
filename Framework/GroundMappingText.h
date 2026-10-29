#pragma once
#include "TextClass.h"
#include <cstdio>

class GroundMappingText : public TextClass
{
public:
    GroundMappingText(int x, int y, const bool* colorBlend, const bool* normalMap)
        : TextClass(x, y), m_colorBlend(colorBlend), m_normalMap(normalMap) {}

    bool Frame() override
    {
        char status[64];
        sprintf_s(status, "B Blend %s | N Normal %s",
            *m_colorBlend ? "ON" : "OFF", *m_normalMap ? "ON" : "OFF");
        return UpdateSentence(m_sentence1, status, 1.0f, 1.0f, 0.2f, m_deviceContext);
    }

private:
    const bool* m_colorBlend;
    const bool* m_normalMap;
};
