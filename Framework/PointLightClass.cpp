////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PointLightClass.h"


PointLightClass::PointLightClass()
{
	isOndiffuse = true;
}


PointLightClass::PointLightClass(const PointLightClass& other)
{
}


PointLightClass::~PointLightClass()
{
}


void PointLightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	onOffdiffuseColor = m_diffuseColor;
	return;
}



void PointLightClass::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT4(x, y, z, 1.0f);
	return;
}

XMFLOAT4 PointLightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


XMFLOAT4 PointLightClass::GetPosition()
{
	return m_position;
}

void PointLightClass::TurnOnOffDiffuse()
{
	if (!isOndiffuse)
	{
		m_diffuseColor = onOffdiffuseColor;
		isOndiffuse = true;
		return;
	}
	else
	{
		m_diffuseColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		isOndiffuse = false;
		return;
	}
}

void PointLightClass::IncIntensity()
{
	m_diffuseColor = XMFLOAT4(m_diffuseColor.x*Intensity_amount, m_diffuseColor.y *Intensity_amount, m_diffuseColor.z * Intensity_amount, m_diffuseColor.w);
}

void PointLightClass::DecIntensity()
{
	m_diffuseColor = XMFLOAT4(m_diffuseColor.x / Intensity_amount, m_diffuseColor.y / Intensity_amount, m_diffuseColor.z / Intensity_amount, m_diffuseColor.w);
}
