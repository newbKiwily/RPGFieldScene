#define _LIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>

using namespace DirectX;

class PointLightClass
{
public:
	PointLightClass();
	PointLightClass(const PointLightClass&);
	~PointLightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetPosition(float, float, float);

	XMFLOAT4 GetDiffuseColor();
	XMFLOAT4 GetPosition();
	void TurnOnOffDiffuse();
	void IncIntensity();
	void DecIntensity();
	XMFLOAT4 m_diffuseColor;
private:

	XMFLOAT4 m_position;
	float Intensity_amount = 1.2f;
	bool isOndiffuse;
	
	XMFLOAT4 onOffdiffuseColor;
	
};

