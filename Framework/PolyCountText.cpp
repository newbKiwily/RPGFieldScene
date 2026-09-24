#include "PolyCountText.h"
#include "graphicsclass.h"
PolyCountText::PolyCountText(int x, int y, GraphicsClass* graphicsClass) :TextClass(x, y), m_Graphics(graphicsClass)
{
}

bool PolyCountText::Frame()
{
	char tempString[64];
	char polyString[64];
	bool result;
	int polygonCount = m_Graphics->getPolyCount();

	// Convert the cpu integer to string format.
	_itoa_s(polygonCount, tempString, 10);

	// Setup the cpu string.
	strcpy_s(polyString, "Ploygon = ");
	strcat_s(polyString, tempString);


	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, polyString, 0.0f, 1.0f, 0.0f, m_deviceContext);
	if (!result)
	{
		return false;
	}
	return true;
}
