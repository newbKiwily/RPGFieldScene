////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightclass.h"


LightClass::LightClass()
{
	
	isOnAmbient = true;
	isOnSpecular = true;
	isOnDiffuse = true;
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{	
	
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	m_onAmbientColor = m_ambientColor;
	return;
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	m_onDiffuseColor = m_diffuseColor;
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}

void LightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::SetSpecularPower(float power)
{
	m_specularPower = power;
	m_onSpecularPower = m_specularPower;
	return;
}

XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}

XMFLOAT4 LightClass::GetSpecularColor()
{
	return m_specularColor;
}

float LightClass::GetSpecularPower()
{
	return m_specularPower;
}

void LightClass::TurnOnOffAmbient()
{	
	if (!isOnAmbient)
	{
		m_ambientColor = m_onAmbientColor;
		isOnAmbient = true;
		return;
	}
	else
	{
		m_ambientColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		isOnAmbient = false;
		return;
	}
}

void LightClass::TurnOnOffSpecular()
{
	if (!isOnSpecular)
	{
		m_specularPower = m_onSpecularPower;
		isOnSpecular = true;
		return;
	}
	else
	{
		m_specularPower = 100000.0f;
		isOnSpecular = false;
		return;
	}
}

void LightClass::TurnOnOffDiffuse()
{
	if (!isOnDiffuse)
	{
		m_diffuseColor = m_onDiffuseColor;
		isOnDiffuse = true;
		return;
	}
	else
	{
		m_diffuseColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		isOnDiffuse = false;
		return;
	}
}
	
