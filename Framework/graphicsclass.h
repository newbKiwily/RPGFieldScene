////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "PointLightClass.h"
#include "SkyboxShaderClass.h"
#include "TextClass.h"
#include <vector>
#include "BitmapShaderClass.h"
#include "BitmapClassOrtho.h"
#include "modelclassFBX.h"
#include "Textureshaderclass.h"
#include "ModelLoader.h"
#include "SkinModel.h"
#include "RMModel.h"
#include "oldLightShader.h"
using namespace std;
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	CameraClass* GetCamera();
	LightClass* m_Light;
	PointLightClass* m_pointLight1, * m_pointLight2, * m_pointLight3,*m_pointLight4,*m_pointLight5,*m_pointLight6, * m_pointLight7,*m_pointLight8;
	pair<int, int> getScreenSize();
	int getObjCount();
	bool isTitleRendering=true;
	int getPolyCount();
	void CreateRayFromScreen(float sx, float sy, XMVECTOR& rayOrigin, XMVECTOR& rayDir);
	bool RayIntersectAABB(XMVECTOR rayOrigin, XMVECTOR rayDir,const XMFLOAT3& minV, const XMFLOAT3& maxV,const XMMATRIX& world);
	bool isLeftMouseClick;
private:

	

private:
	CameraClass* m_Camera;
	ModelClass* landModel;
	ModelClass* landModel2;
	vector<ModelClass*> modelClasses;
	vector<BitmapClassOrtho*> bitmapClasses;
	LightShaderClass* m_LightShader;
	oldLightShader* m_oldLightShader;
	SkyboxShaderClass* m_skyboxShader;
	vector<TextClass*> textClasses;
	float size = 4000;
	const float half = size / 2.0f;
	int m_screenWidth;
	int m_screenHeight;
	int polyCount;
	BitmapShaderClass* bitmapShader;
	ModelLoader* m_modelLoader;
	SkinModel* m_skinModel;
	bool Render(float);
};

#endif