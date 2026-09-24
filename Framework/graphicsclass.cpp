////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "DDSTextureLoader.h"
#include "ScreenSizeText.h"
#include "ObjCountText.h"
#include "PolyCountText.h"
#include "FpsText.h"
#include "CPUText.h"
#include "Title.h"
#include "RMShader.h"
#include "TimeManager.h"
GraphicsClass::GraphicsClass()
{

	m_Camera = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_pointLight1 = 0;
	m_pointLight2 = 0;
	m_pointLight3 = 0;
	m_skyboxShader = 0;
	polyCount = 0;
	bitmapShader = 0;
	isTitleRendering = false;
	isLeftMouseClick = false;
	
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

	isTitleRendering = false;
	result = D3DClass::GetInstance().Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	m_modelLoader = new ModelLoader;

	
	//model - animated
	{
		m_skinModel = new SkinModel;

		m_skinModel = m_modelLoader->LoadModel(L"./data/NPC.fbx", aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_modelLoader->LoadAnimation(L"./data/NPCIdle.fbx", m_skinModel, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_modelLoader->LoadAnimation(L"./data/NPCCold.fbx", m_skinModel, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_modelLoader->LoadAnimation(L"./data/NPCClap.fbx", m_skinModel, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_modelLoader->LoadAnimation(L"./data/NPCIdle.fbx", m_skinModel, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_modelLoader->LoadAnimation(L"./data/NPCIdle.fbx", m_skinModel, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_modelLoader->LoadAnimation(L"./data/NPCIdle.fbx", m_skinModel, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
		m_skinModel->LoadTexture(L"./data/NPCTexture.dds");
		m_skinModel->SetNormalize(true);
		m_skinModel->SetSize(XMFLOAT3(10.0f, 10.0f, 10.0f));

		m_skinModel->SetCenter(XMFLOAT3(5.0f, -1.0f, 15.0f));
		m_skinModel->SetRotate(XMFLOAT3(0.0f, 90.0f, 0.0f));
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}


	m_Camera->SetPosition(0.0f, 7.0f, -34.0f);
	m_Camera->SetRotation(1.5f, 0.0f, 0.0f);
	
	TIMEMANAGER.Init();
	RM_SHADER.Init(D3DClass::GetInstance().GetDevice());

	// Create the model object.
	landModel = new ModelClass(false);
	landModel2 = new ModelClass(false);
	ModelClass* wolf = new ModelClass(false);
	ModelClass* streetLight1 = new ModelClass(false);
	ModelClass* streetLight2 = new ModelClass(false);
	ModelClass* streetLight3 = new ModelClass(false);
	ModelClass* streetLight4 = new ModelClass(false);

	ModelClass* streetLight5 = new ModelClass(false);
	ModelClass* streetLight6 = new ModelClass(false);

	ModelClass* board = new ModelClass(false);
	ModelClass* house1 = new ModelClass(false);
	ModelClass* house2 = new ModelClass(false);
	ModelClass* house3 = new ModelClass(false);
	ModelClass* campfire = new ModelClass(true);
	ModelClass* streetLight7 = new ModelClass(false);

	ModelClass* bush1 = new ModelClass(false);
	ModelClass* bush2 = new ModelClass(false);
	ModelClass* bush3 = new ModelClass(false);
	ModelClass* bush4 = new ModelClass(false);
	ModelClass* bush5 = new ModelClass(false);
	ModelClass* bush6 = new ModelClass(false);
	ModelClass* bush7 = new ModelClass(false);
	ModelClass* bush8= new ModelClass(false);


	ModelClass* bigTree = new ModelClass(false);
	result = landModel->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/land3.obj", L"./data/land34.dds", L"./data/land34Bump.dds", L"./data/dummyDiffuseMap.dds");
	polyCount += landModel->getPolygonCount();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
		return false;
	}
	result = landModel2->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/land4.obj", L"./data/land4.dds", L"./data/StreetLightBump.dds", L"./data/land4Diffuse.dds");
	//result = landModel2->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/land4.obj", L"./data/land4.dds", L"./data/StreetLightBump.dds", L"./data/dummyDiffuseMap.dds");
	polyCount += landModel2->getPolygonCount();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model1 object.", L"Error", MB_OK);
		return false;
	}
	result = wolf->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/wolf.obj", L"./data/wolf.dds", L"./data/wolfBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}
	
	result = streetLight1->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight.obj", L"./data/StreetLight.dds", L"./data/StreetLightBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}
	result = streetLight2->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight.obj", L"./data/StreetLight.dds", L"./data/StreetLightBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}
	result = streetLight3->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight.obj", L"./data/StreetLight.dds", L"./data/StreetLightBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}
	result = streetLight4->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight.obj", L"./data/StreetLight.dds", L"./data/StreetLightBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}
	result = streetLight5->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight2.obj", L"./data/StreetLight2.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = streetLight6->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight2.obj", L"./data/StreetLight2.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = board->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/board.obj", L"./data/board.dds", L"./data/boardBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = house1->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/House11.obj", L"./data/House1.dds", L"./data/House1Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = house2->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/House12.obj", L"./data/House2.dds", L"./data/House2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = house3->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/House13.obj", L"./data/House3.dds", L"./data/House3Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = campfire->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/campfire.obj", L"./data/campfire.dds", L"./data/StreetLightBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}

	result = streetLight7->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/StreetLight2.obj", L"./data/StreetLight2.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush1->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush2->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush3->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush4->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush5->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush6->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush7->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bush8->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bush.obj", L"./data/bush.dds", L"./data/StreetLight2Bump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}
	result = bigTree->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/bigTree.obj", L"./data/bigTree.dds", L"./data/bigTreeBump.dds", L"./data/dummyDiffuseMap.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model3 object.", L"Error", MB_OK);
		return false;
	}

	modelClasses.push_back(wolf);

	modelClasses.push_back(streetLight1);
	modelClasses.push_back(streetLight2);
	modelClasses.push_back(streetLight3);
	modelClasses.push_back(streetLight4);

	modelClasses.push_back(streetLight5);
	modelClasses.push_back(streetLight6);

	modelClasses.push_back(board);
	modelClasses.push_back(house1);
	modelClasses.push_back(house2);
	modelClasses.push_back(house3);
	modelClasses.push_back(campfire);

	modelClasses.push_back(streetLight7);
	modelClasses.push_back(bush1);
	modelClasses.push_back(bush2);
	modelClasses.push_back(bush3);
	modelClasses.push_back(bush4);
	modelClasses.push_back(bush5);
	modelClasses.push_back(bush6);
	modelClasses.push_back(bush7);
	modelClasses.push_back(bush8);
	modelClasses.push_back(bigTree);
	for (auto it : modelClasses)
	{
		polyCount += it->getPolygonCount();
	}
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the tree1 object.", L"Error", MB_OK);
		return false;
	}



	// 트리 배치 좌표들
	std::vector<XMFLOAT3> treePositions = {
		{ -70.0f, 28.0f, -20.0f },    // 중심
		{ -60.0f, 28.0f, -10.0f },    // +10, +10
		{ -60.0f, 28.0f, -30.0f },    // +10, -10
		{ -80.0f, 28.0f, -10.0f },    // -10, +10
		{ -80.0f, 28.0f, -30.0f },     // -10, -10

		{ -70.0f, 28.0f, -45.0f },    // 중심
		{ -60.0f, 28.0f, -35.0f },    // +10, +10
		{ -60.0f, 28.0f, -55.0f },    // +10, -10
		{ -80.0f, 28.0f, -35.0f },    // -10, +10
		{ -80.0f, 28.0f, -55.0f },     // -10, -10

		{ -70.0f, 28.0f, -70.0f },   // center
		{ -60.0f, 28.0f, -60.0f },   // +10, +10
		{ -60.0f, 28.0f, -80.0f },   // +10, -10
		{ -80.0f, 28.0f, -60.0f },   // -10, +10
		{ -80.0f, 28.0f, -80.0f },    // -10, -10
		
		{ -50.0f, 28.0f,  40.0f },   // 중심
		{ -40.0f, 28.0f,  50.0f },   // +10, +10
		{ -40.0f, 28.0f,  30.0f },   // +10, -10
		{ -60.0f, 28.0f,  50.0f },   // -10, +10
		{ -60.0f, 28.0f,  30.0f },    // -10, -10

		{ -80.0f, 28.0f,  40.0f },   // 중심
		{ -70.0f, 28.0f,  50.0f },   // +10, +10
		{ -70.0f, 28.0f,  30.0f },   // +10, -10
		{ -90.0f, 28.0f,  50.0f },   // -10, +10
		{ -90.0f, 28.0f,  30.0f },    // -10, -10

		{ 80.0f, 28.0f,  55.0f },    // 중심
		{ 90.0f, 28.0f,  65.0f },    // +10, +10
		{ 90.0f, 28.0f,  45.0f },    // +10, -10
		{ 70.0f, 28.0f,  65.0f },    // -10, +10
		{ 70.0f, 28.0f,  45.0f },     // -10, -10

		{ 40.0f, 28.0f,  55.0f },    // 중심
		{ 50.0f, 28.0f,  65.0f },    // +10, +10
		{ 50.0f, 28.0f,  45.0f },    // +10, -10
		{ 30.0f, 28.0f,  65.0f },    // -10, +10
		{ 30.0f, 28.0f,  45.0f },     // -10, -10

		{ 80.0f, 28.0f,  -55.0f },    // 중심
		{ 90.0f, 28.0f,  -45.0f },    // +10, +10
		{ 90.0f, 28.0f,  -65.0f },    // +10, -10
		{ 70.0f, 28.0f,  -45.0f },    // -10, +10
		{ 70.0f, 28.0f,  -65.0f },     // -10, -10

		{ 80.0f, 28.0f,  -20.0f },    // 중심
		{ 90.0f, 28.0f,  -10.0f },    // +10, +10
		{ 90.0f, 28.0f,  -30.0f },    // +10, -10
		{ 70.0f, 28.0f,  -10.0f },    // -10, +10
		{ 70.0f, 28.0f,  -30.0f }     // -10, -10


	};

	// 트리 카피해서 여러개 생성
	for (auto& pos : treePositions)
	{
		ModelClass* t = new ModelClass(false);
		result = t->Initialize(D3DClass::GetInstance().GetDevice(), L"./data/tree.obj", L"./data/tree.dds", L"./data/treeBump.dds", L"./data/dummyDiffuseMap.dds");

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize tree clone object.", L"Error", MB_OK);
			return false;
		}

		// 위치 저장 (직접 만든 변수) → Render에서 사용
		t->posX = pos.x;
		t->posY = pos.y;
		t->posZ = pos.z;

		modelClasses.push_back(t);
		polyCount += t->getPolygonCount();
	}
	bitmapShader = new BitmapShaderClass;
	if (!bitmapShader)
	{
		return false;
	}	

	result = bitmapShader->Initialize(D3DClass::GetInstance().GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap shader object.", L"Error", MB_OK);
		return false;
	}
	bitmapClasses.push_back(new Title(D3DClass::GetInstance().GetDevice(), screenWidth, screenHeight, L"./data/title_3.dds", 1280, 720, 0, 0));

	for (auto it = bitmapClasses.begin(); it != bitmapClasses.end(); it++)
	{
		result = (*it)->Initialize();
		
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
			return false;
		}
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}
	m_oldLightShader = new oldLightShader;
	if (!m_oldLightShader)
		return false;


	// Initialize the light shader object.
	result = m_LightShader->Initialize(D3DClass::GetInstance().GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	result = m_oldLightShader->Initialize(D3DClass::GetInstance().GetDevice(),hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}
	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light->SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
	m_Light->SetDirection(0.0f, 5.0f, 1.0f);
	m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularPower(1000000.0f);

	m_pointLight1 = new PointLightClass;
	m_pointLight2 = new PointLightClass;
	m_pointLight3 = new PointLightClass;
	m_pointLight4 = new PointLightClass;
	m_pointLight5 = new PointLightClass;
	m_pointLight6 = new PointLightClass;
	m_pointLight7 = new PointLightClass;
	m_pointLight8 = new PointLightClass;
	m_pointLight1->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);
	m_pointLight2->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);
	m_pointLight3->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);
	m_pointLight4->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);
	m_pointLight5->SetDiffuseColor(0.001f, 0.0f, 0.0f, 1.0f);
	m_pointLight6->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);
	m_pointLight7->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);
	m_pointLight8->SetDiffuseColor(1.0f, 0.75f, 0.0f, 1.0f);

	// 오브젝트들 뒤에 배치하도록 Z 값을 양수 방향으로 설정
	m_pointLight1->SetPosition(13.0f, 10.0f, 4.0f);     
	m_pointLight2->SetPosition(-11.0f, 10.0f, 26.0f);    
	m_pointLight3->SetPosition(13.0f, 10.0f, 26.0f);     
	m_pointLight4->SetPosition(-11.0f, 10.0f, 4.0f);
	m_pointLight5->SetPosition(0.0f, 3.0f, 15.0f);
	m_pointLight6->SetPosition(-33.0f, 10.0f, -55.0f);
	m_pointLight7->SetPosition(30.0f, 10.0f, -50.0f);
	m_pointLight8->SetPosition(80.0f, 5.0f, 15.0f);

	m_skyboxShader = new SkyboxShaderClass();
	result = m_skyboxShader->Initialize(D3DClass::GetInstance().GetDevice(), hwnd, L"./data/skymap6.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the skybox shader object.", L"Error", MB_OK);
		return false;
	}

	textClasses.push_back(new ScreenSizeText(30, 40,this));
	textClasses.push_back(new ObjCountText(30, 20, this));
	textClasses.push_back(new PolyCountText(30, 60,this));
	textClasses.push_back(new FpsText(30, 80));
	textClasses.push_back(new CPUText(30, 100));
	XMMATRIX baseViewMatrix;
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	for (auto it = textClasses.begin(); it != textClasses.end(); it++)
	{
		result = (*it)->Initialize(D3DClass::GetInstance().GetDevice(), D3DClass::GetInstance().GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);

		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
			return false;
		}
	}
	isTitleRendering = true;
	return true;
}


void GraphicsClass::Shutdown()
{	
	if (bitmapShader)
	{
		bitmapShader->Shutdown();
		delete bitmapShader;
		bitmapShader = 0;
	}
	for (auto it = bitmapClasses.begin(); it != bitmapClasses.end(); it++)
	{
		if ((*it))
		{
			(*it)->Shutdown();
			delete (*it);
		}
	}
	if (landModel)
	{
		delete landModel;
		landModel = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}



	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	if (m_pointLight1)
		delete m_pointLight1;
	if (m_pointLight2)
		delete m_pointLight2;
	if (m_pointLight3)
		delete m_pointLight3;
	if (m_skyboxShader)
	{
		m_skyboxShader->Shutdown();
		delete m_skyboxShader;
	}
	for (auto it = textClasses.begin(); it != textClasses.end(); it++)
	{
		if ((*it))
		{
			(*it)->Shutdown();
			delete (*it);
		}
	}
	return;
}

bool GraphicsClass::Frame()
{
	bool result;


	for (auto it = textClasses.begin(); it != textClasses.end(); it++)
	{
		if (!(*it)->Frame())
			continue;
	}
	// Update the rotation variable each frame.

	TIMEMANAGER.Update(144.0f);

	// Render the graphics scene.
	result = Render(0.0001f);
	if (!result)
	{
		return false;
	}
	if (isLeftMouseClick)
	{
		isLeftMouseClick = false;   

		float cx = m_screenWidth * 0.5f;
		float cy = m_screenHeight * 0.5f;

		XMVECTOR rayStartPoint, rayDirection;
		CreateRayFromScreen(cx, cy, rayStartPoint, rayDirection);

		for (auto model : modelClasses)
		{	
			if (!model->iscollider)
				continue;

			XMMATRIX world = XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(0.0f, 0.0f, 15.0f);

			if (RayIntersectAABB(rayStartPoint, rayDirection,
				model->m_minVertex, model->m_maxVertex,
				world))
			{
				m_pointLight5->SetDiffuseColor(m_pointLight5->m_diffuseColor.x * 1.01f, m_pointLight5->m_diffuseColor.y, m_pointLight5->m_diffuseColor.z, 1.0f);
			}
		}
	}


	return true;
}

CameraClass* GraphicsClass::GetCamera()
{
	return m_Camera;
}


pair<int, int> GraphicsClass::getScreenSize()
{
	return { m_screenWidth,m_screenHeight };
}

int GraphicsClass::getObjCount()
{	
	
	return modelClasses.size();
}

int GraphicsClass::getPolyCount()
{
	return polyCount;
}

bool GraphicsClass::Render(float rotation)
{
	bool result;

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix,titleMatrix;
	XMMATRIX worldLandMatrix;
	ID3D11DeviceContext* context = D3DClass::GetInstance().GetDeviceContext();

	D3DClass::GetInstance().BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	D3DClass::GetInstance().GetWorldMatrix(worldMatrix);
	D3DClass::GetInstance().GetWorldMatrix(worldLandMatrix);
	D3DClass::GetInstance().GetWorldMatrix(titleMatrix);
	D3DClass::GetInstance().GetProjectionMatrix(projectionMatrix);
	D3DClass::GetInstance().GetOrthoMatrix(orthoMatrix);
	worldMatrix = XMMatrixRotationY(rotation);
	// 카메라 위치로 이동 (Skybox는 항상 카메라 중심)
	XMFLOAT3 camPos = m_Camera->GetPosition();
	XMMATRIX skyWorld = XMMatrixTranslation(camPos.x, camPos.y, camPos.z);
	
	// SkyboxShaderClass를 이용해 큐브맵 렌더
	result = m_skyboxShader->Render(
		context,
		skyWorld,
		viewMatrix,
		projectionMatrix
	);
	if (!result) {
		MessageBox(NULL, L"Skybox render failed", L"Error", MB_OK);
		return false;
	}
	
	
	XMFLOAT4 pdiffuseColor[8];
	XMFLOAT4 plightPosition[8];
	pdiffuseColor[0] = m_pointLight1->GetDiffuseColor();
	pdiffuseColor[1] = m_pointLight2->GetDiffuseColor();
	pdiffuseColor[2] = m_pointLight3->GetDiffuseColor();
	pdiffuseColor[3] = m_pointLight4->GetDiffuseColor();
	pdiffuseColor[4] = m_pointLight5->GetDiffuseColor();
	pdiffuseColor[5] = m_pointLight6->GetDiffuseColor();
	pdiffuseColor[6] = m_pointLight7->GetDiffuseColor();
	pdiffuseColor[7] = m_pointLight8->GetDiffuseColor();

	plightPosition[0] = m_pointLight1->GetPosition();
	plightPosition[1] = m_pointLight2->GetPosition();
	plightPosition[2] = m_pointLight3->GetPosition();
	plightPosition[3] = m_pointLight4->GetPosition();
	plightPosition[4] = m_pointLight5->GetPosition();
	plightPosition[5] = m_pointLight6->GetPosition();
	plightPosition[6] = m_pointLight7->GetPosition();
	plightPosition[7] = m_pointLight8->GetPosition();

	
	landModel->Render(context);
	result = m_LightShader->Render(
		context,
		landModel->GetIndexCount(),
		worldLandMatrix*XMMatrixScaling(5.0f,5.0f,5.0f),
		viewMatrix, projectionMatrix,
		landModel->GetTextureArray(),
		m_Light->GetDirection(),
		m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(),
		m_Light->GetSpecularColor(),
		m_Light->GetSpecularPower(),
		pdiffuseColor,
		plightPosition
	);
	if (!result)
		return false;
	landModel2->Render(context);
	result = m_LightShader->Render(
		context,
		landModel2->GetIndexCount(),
		worldLandMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f)*XMMatrixTranslation(0.0f, 0.1f, 0.0f),
		viewMatrix, projectionMatrix,
		landModel2->GetTextureArray(),
		m_Light->GetDirection(),
		m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(),
		m_Light->GetSpecularColor(),
		m_Light->GetSpecularPower(),
		pdiffuseColor,
		plightPosition
	);
	if (!result)
		return false;
	result = m_oldLightShader->Render(
		context,
		m_skinModel->GetIndexCount(),
		worldMatrix * XMMatrixTranslation(0.0f, 10000.0f, 0.0f), viewMatrix, projectionMatrix,
		m_skinModel->GetTexture(),
		m_Light->GetDirection(),
		m_Light->GetAmbientColor(),
		m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(),
		m_Light->GetSpecularColor(),
		m_Light->GetSpecularPower()
	);
	if (!result)
		return false;

	RM_SHADER.SetShaderParameters(D3DClass::GetInstance().GetDeviceContext(), viewMatrix, projectionMatrix);
	m_skinModel->Render(D3DClass::GetInstance().GetDeviceContext());
	XMFLOAT3 mov(m_skinModel->GetCenter());
	if (m_skinModel->GetAnimationList().size() != 0)
	{
		

		if (!m_skinModel->GetAnimation(6).isPlaying()&&m_pointLight5->GetDiffuseColor().x>0.5f&& m_pointLight5->GetDiffuseColor().x < 3.5f)
		{
			m_skinModel->PlayAni(1);
			
		}
		else if (!m_skinModel->GetAnimation(6).isPlaying() && m_pointLight5->GetDiffuseColor().x >= 3.5f)
		{
			m_skinModel->PlayAni(3);
		}
		else if (!m_skinModel->GetAnimation(6).isPlaying()&&m_pointLight5->GetDiffuseColor().x<=0.5f)
			m_skinModel->PlayAni(2);

	}
	/*modelClasses[0]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[0]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(0.15f, 0.15f, 0.15f), viewMatrix, projectionMatrix,
		modelClasses[0]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;*/
	modelClasses[1]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[1]->GetIndexCount(),
		worldMatrix*XMMatrixTranslation(12.0f,0.0f,4.0f), viewMatrix, projectionMatrix,
		modelClasses[1]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[2]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[2]->GetIndexCount(),
		worldMatrix * XMMatrixTranslation(-12.0f, 0.0f, 26.0f), viewMatrix, projectionMatrix,
		modelClasses[2]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[3]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[3]->GetIndexCount(),
		worldMatrix * XMMatrixTranslation(12.0f, 0.0f, 26.0f), viewMatrix, projectionMatrix,
		modelClasses[3]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[4]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[4]->GetIndexCount(),
		worldMatrix * XMMatrixTranslation(-12.0f, 0.0f, 4.0f), viewMatrix, projectionMatrix,
		modelClasses[4]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[5]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[5]->GetIndexCount(),
		worldMatrix* XMMatrixScaling(3.0f, 5.0f, 3.0f) * XMMatrixTranslation(80.0f, 0.0f, 15.0f), viewMatrix, projectionMatrix,
		modelClasses[5]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[6]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[6]->GetIndexCount(),
		worldMatrix  * XMMatrixScaling(3.0f, 5.0f, 3.0f) * XMMatrixTranslation(30.0f,0.0f,-50.0f), viewMatrix, projectionMatrix,
		modelClasses[6]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[7]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[7]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(0.06f, 0.06f, 0.06f) * XMMatrixRotationY(XM_PI / 2)*XMMatrixTranslation(-20.0f,0.0f,-55.0f), viewMatrix, projectionMatrix,
		modelClasses[7]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[8]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[8]->GetIndexCount(),
		worldMatrix*XMMatrixScaling(3.0f, 3.0f, 3.0f) * XMMatrixRotationY(XM_PI) * XMMatrixTranslation(40.0f, 10.0f, -55.0f), viewMatrix, projectionMatrix,
		modelClasses[8]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[9]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[9]->GetIndexCount(),
		worldMatrix*XMMatrixScaling(3.0f,3.0f,3.0f)* XMMatrixRotationY(XM_PI / 2)*XMMatrixTranslation(60.0f,14.0f,20.0f), viewMatrix, projectionMatrix,
		modelClasses[9]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[10]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[10]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(3.0f, 3.0f, 3.0f)  *XMMatrixRotationY(3*(XM_PI/2)) *XMMatrixTranslation(0.0f,9.0f,-55.0f), viewMatrix, projectionMatrix,
		modelClasses[10]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[11]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[11]->GetIndexCount(),
		worldMatrix*XMMatrixScaling(5.0f,5.0f,5.0f)*XMMatrixTranslation(0.0f,0.1f,15.0f), viewMatrix, projectionMatrix,
		modelClasses[11]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[12]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[12]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(3.0f, 5.0f, 3.0f) * XMMatrixTranslation(-33.0f, 0.0f, -50.0f), viewMatrix, projectionMatrix,
		modelClasses[12]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[13]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[13]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f)*XMMatrixTranslation(8.0f, 0.0f, 0.0f), viewMatrix, projectionMatrix,
		modelClasses[13]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[14]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[14]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f)*XMMatrixTranslation(15.0f, 0.0f, 5.0f), viewMatrix, projectionMatrix,
		modelClasses[14]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[15]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[15]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(-8.0f, 0.0f, 0.0f), viewMatrix, projectionMatrix,
		modelClasses[15]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[16]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[16]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(-15.0f, 0.0f, 5.0f), viewMatrix, projectionMatrix,
		modelClasses[16]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[17]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[17]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(8.0f, 0.0f, 30.0f), viewMatrix, projectionMatrix,
		modelClasses[17]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[18]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[18]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(15.0f, 0.0f, 25.0f), viewMatrix, projectionMatrix,
		modelClasses[18]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[19]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[19]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(-8.0f, 0.0f, 30.0f), viewMatrix, projectionMatrix,
		modelClasses[19]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[20]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[20]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(5.0f, 5.0f, 5.0f) * XMMatrixTranslation(-15.0f, 0.0f, 25.0f), viewMatrix, projectionMatrix,
		modelClasses[20]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	modelClasses[21]->Render(D3DClass::GetInstance().GetDeviceContext());
	result = m_LightShader->Render(D3DClass::GetInstance().GetDeviceContext(), modelClasses[21]->GetIndexCount(),
		worldMatrix*XMMatrixScaling(8.0f,8.0f,8.0f)*XMMatrixTranslation(0.0f,5.0f,55.0f), viewMatrix, projectionMatrix,
		modelClasses[21]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;
	/*modelClasses[22]->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), modelClasses[22]->GetIndexCount(),
		worldMatrix * XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixTranslation(-50.0f, 28.0f, 50.0f), viewMatrix, projectionMatrix,
		modelClasses[22]->GetTextureArray(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pdiffuseColor, plightPosition);
	if (!result)
		return false;*/
	int treeStartIndex = 22;

	// 공통 스케일
	XMMATRIX treeScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	for (int i = treeStartIndex; i < modelClasses.size(); i++)
	{
		ModelClass* tree = modelClasses[i];

		// 트리 렌더링
		tree->Render(context);

		bool ok = m_LightShader->Render(
			context,
			tree->GetIndexCount(),
			worldMatrix *
			treeScale *
			XMMatrixTranslation(tree->posX, tree->posY, tree->posZ),
			viewMatrix,
			projectionMatrix,
			tree->GetTextureArray(),
			m_Light->GetDirection(),
			m_Light->GetAmbientColor(),
			m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(),
			m_Light->GetSpecularColor(),
			m_Light->GetSpecularPower(),
			pdiffuseColor,
			plightPosition
		);

		if (!ok) return false;
	}
	D3DClass::GetInstance().TurnOnAlphaBlending();
	for (auto it = textClasses.begin(); it != textClasses.end(); it++)
	{
		result = (*it)->Render(D3DClass::GetInstance().GetDeviceContext(), XMMatrixIdentity(), orthoMatrix);
		if (!result) return false;
	}

	D3DClass::GetInstance().TurnOffAlphaBlending();

	D3DClass::GetInstance().TurnZBufferOff();
	

	if (isTitleRendering)
	{	
		result = bitmapClasses[0]->Render(D3DClass::GetInstance().GetDeviceContext());
		if (!result) return false;
		result = bitmapShader->Render(
			D3DClass::GetInstance().GetDeviceContext(),
			bitmapClasses[0]->GetIndexCount(),
			titleMatrix,
			XMMatrixIdentity(),
			orthoMatrix,
			bitmapClasses[0]->GetTexture()
		);
		D3DClass::GetInstance().TurnZBufferOn();
		
	}
	D3DClass::GetInstance().EndScene();

	return true;
}

void GraphicsClass::CreateRayFromScreen(float sx, float sy,	XMVECTOR& rayStartPoint,XMVECTOR& rayDirection)
{
	
	XMMATRIX projMatrix;
	D3DClass::GetInstance().GetProjectionMatrix(projMatrix);

	XMMATRIX viewMatrix;
	m_Camera->GetViewMatrix(viewMatrix);

	float px = ((2.0f * sx) / m_screenWidth - 1.0f) / projMatrix.r[0].m128_f32[0];
	float py = -((2.0f * sy) / m_screenHeight - 1.0f) / projMatrix.r[1].m128_f32[1];

	XMVECTOR rayInView = XMVectorSet(px, py, 1.0f, 0.0f);
	rayInView = XMVector3Normalize(rayInView);

	XMMATRIX invView = XMMatrixInverse(nullptr, viewMatrix);

	rayStartPoint = XMVector3TransformCoord(XMVectorZero(), invView);
	rayDirection = XMVector3TransformNormal(rayInView, invView);
	rayDirection = XMVector3Normalize(rayDirection);
}

bool GraphicsClass::RayIntersectAABB(XMVECTOR rayStartPoint, XMVECTOR rayDirection,
	const XMFLOAT3& minV, const XMFLOAT3& maxV,
	const XMMATRIX& world)
{
	// 1) 로컬 AABB → 월드 좌표로 변환
	XMVECTOR minLocal = XMLoadFloat3(&minV);
	XMVECTOR maxLocal = XMLoadFloat3(&maxV);

	// 두 코너를 world transform
	XMVECTOR wMin = XMVector3TransformCoord(minLocal, world);
	XMVECTOR wMax = XMVector3TransformCoord(maxLocal, world);

	// real min/max 재정렬
	XMVECTOR boxMin = XMVectorMin(wMin, wMax);
	XMVECTOR boxMax = XMVectorMax(wMin, wMax);

	float tmin = 0.0f;
	float tmax = FLT_MAX;

	for (int i = 0; i < 3; i++)
	{
		float origin = rayStartPoint.m128_f32[i];
		float dir = rayDirection.m128_f32[i];
		float minB = boxMin.m128_f32[i];
		float maxB = boxMax.m128_f32[i];

		if (fabs(dir) < 0.000001f)
		{
			if (origin < minB || origin > maxB)
				return false;
		}
		else
		{
			float ood = 1.0f / dir;
			float t1 = (minB - origin) * ood;
			float t2 = (maxB - origin) * ood;

			if (t1 > t2) std::swap(t1, t2);

			tmin = max(tmin, t1);
			tmax = min(tmax, t2);

			if (tmin > tmax)
				return false;
		}
	}

	return true;
}