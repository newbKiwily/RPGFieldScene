#include "ScreenSizeText.h"
#include "graphicsclass.h"

ScreenSizeText::ScreenSizeText(int x, int y, GraphicsClass* graphicsClass) :TextClass(x, y), m_Graphics(graphicsClass)
{

}

bool ScreenSizeText::Frame()
{
	char widthStr[64];
	char heightStr[64];
	char screenString[64];
	bool result;
	auto screenSize = m_Graphics->getScreenSize();
	// 정수 -> 문자열로 변환
	_itoa_s(screenSize.first, widthStr, 10);
	_itoa_s(screenSize.second, heightStr, 10);

	// "ScreenSize = " + width + " x " + height 형식으로 조합
	strcpy_s(screenString, "ScreenSize = ");

	strcat_s(screenString, widthStr);

	strcat_s(screenString, " x ");

	strcat_s(screenString, heightStr);

	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, screenString, 0.0f, 1.0f, 0.0f, m_deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}


