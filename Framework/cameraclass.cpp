////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	speed = 0.05f;
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	using namespace DirectX;
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	position = XMLoadFloat3(&m_position);
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	
	pitch = m_rotation.x;
	yaw = m_rotation.y;
	roll = m_rotation.z;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	lookAt = position + lookAt;
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}
void CameraClass::Update(float moveLeftRight, float moveBackForward, float camYaw, float camPitch)
{
	using namespace DirectX;

	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0.0f);

	m_forward = XMVector3Normalize(XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), camRotationMatrix));
	m_right = XMVector3Normalize(XMVector3TransformCoord(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), camRotationMatrix));
	
	m_up = XMVector3Normalize(XMVector3Cross(m_right, m_forward));

	XMVECTOR pos = XMLoadFloat3(&m_position);
	pos += moveLeftRight * m_right;
	pos += moveBackForward * m_forward;
	XMStoreFloat3(&m_position, pos);

	// 라디안 그대로 보관
	m_rotation.y = camYaw;
	m_rotation.x = camPitch;
}