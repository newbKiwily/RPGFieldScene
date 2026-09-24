#include "CPUText.h"

CPUText::CPUText(int x, int y) :TextClass(x, y)
{

}

bool CPUText::Frame()
{
	char tempString[64];
	char cpuString[64];
	bool result;

	// Convert the cpu integer to string format.
	_itoa_s(CpuClass::GetInstance().GetCpuPercentage(), tempString, 10);

	// Setup the cpu string.
	strcpy_s(cpuString, "CPU = ");
	strcat_s(cpuString, tempString);
	strcat_s(cpuString, "%");

	// Update the sentence vertex buffer with the new string information.
	result = TextClass::UpdateSentence(m_sentence1, cpuString, 1.0f, 1.0f, 0.0f, m_deviceContext);
	if (!result)
	{
		return false;
	}

	return true;
}
