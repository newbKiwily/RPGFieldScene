#include "ObjCountText.h"
#include "graphicsclass.h"

ObjCountText::ObjCountText(int x, int y, GraphicsClass* graphicsClass) :TextClass(x, y), m_Graphics(graphicsClass)
{

}

bool ObjCountText::Frame()
{
	char tempString[64];
	char objString[64];
	bool result;
	int ObjCount = m_Graphics->getObjCount();
	// Convert the cpu integer to string format.
	_itoa_s(ObjCount, tempString, 10);

	// Setup the cpu string.
	strcpy_s(objString, "Obj= ");
	strcat_s(objString, tempString);


	// Update the sentence vertex buffer with the new string information.
	result = UpdateSentence(m_sentence1, objString, 0.0f, 1.0f, 0.0f, m_deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
