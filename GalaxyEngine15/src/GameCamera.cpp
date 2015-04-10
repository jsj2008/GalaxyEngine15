#include "..\include\GameCamera.h"

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

static inline float RadiansToDegrees(float radians) {
	return radians * 180.0f / (float)M_PI;
}

GameCamera::GameCamera(void):horizontalAngle(0), verticalAngle(0), fov(45.f), znear(.1f), zfar(1000), aspect(800/600),
							 xOrg(0), yOrg(0), xMax(0), yMax(0), xZoom(1), yZoom(1), maxZoom(1.25), m_orthoMode(OM_SCREEN)
{
	// Set all the defaults
	isOrtho = false;
}


GameCamera::~GameCamera(void)
{
}

glm::mat4 GameCamera::View()
{
	return GetOrientation()* glm::scale(glm::mat4(), glm::vec3(xZoom, yZoom, 0)) * glm::translate(glm::mat4(), -position);
}

// returns the translated camera
glm::mat4 GameCamera::Projection()
{
	if(isOrtho)
	{		
		if(m_orthoMode == OM_SCREEN)
			return glm::ortho(xOrg, xMax, yOrg, yMax, -10.0f, 10.f);

		if(m_orthoMode == OM_VIEW)
			return glm::ortho(0.f, 1.0f * aspect, 0.0f, 1.0f, -10.0f, 10.f);
	}

	return glm::perspective(fov, aspect, znear, zfar);
}

glm::mat4 GameCamera::VPMatrix()
{
	return Projection()*View();
}

// Stationary ortho projection matrix
glm::mat4 GameCamera::Ortho()
{
	return glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -10.0f, 10.f);
}

glm::mat4 GameCamera::GetOrientation()
{
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, verticalAngle, glm::vec3(1,0,0));
	orientation = glm::rotate(orientation, horizontalAngle, glm::vec3(0,1,0));
	return orientation;
}

glm::vec2 GameCamera::GetDirection()
{
	return glm::vec2(horizontalAngle, verticalAngle);
}

void GameCamera::OffsetOrientation(float up, float right)
{
	horizontalAngle += right;
	verticalAngle   += up;

	Normalize();
}

void GameCamera::LookAt(glm::vec3 wPos)
{
	glm::vec3 dir = glm::normalize(wPos - position);

	verticalAngle = RadiansToDegrees(asinf(-dir.y));
	horizontalAngle = -RadiansToDegrees(atan2f(-dir.x, -dir.z));

	Normalize();
}

void GameCamera::Normalize() {
	horizontalAngle = fmodf(horizontalAngle, 360.0f);
	//fmodf can return negative values, but this will make them all positive
	if(horizontalAngle < 0.0f)
		horizontalAngle += 360.0f;

	if(verticalAngle > MaxVerticalAngle)
		verticalAngle = MaxVerticalAngle;
	else if(verticalAngle < -MaxVerticalAngle)
		verticalAngle = -MaxVerticalAngle;
}

// Movement functions
glm::vec3 GameCamera::Right()
{
	glm::vec4 right = glm::inverse(GetOrientation()) * glm::vec4(1,0,0,1);
	return glm::vec3(right);
}

glm::vec3 GameCamera::Up()
{
	glm::vec4 up = glm::inverse(GetOrientation()) * glm::vec4(0,1,0,1);
	return glm::vec3(up);
}

glm::vec3 GameCamera::Forward()
{
	glm::vec4 forward = glm::inverse(GetOrientation()) * glm::vec4(0,0,-1,1);
	return glm::vec3(forward);
}

void GameCamera::OrthoZoomIn(float dist)
{
	xZoom += (dist);
	yZoom += (dist);

	if(xZoom > maxZoom)
		xZoom = maxZoom;
	if(yZoom > maxZoom)
		yZoom = maxZoom;
}

void GameCamera::OrthoZoomOut(float dist)
{
	xZoom -= (dist);
	yZoom -= (dist);

	if(xZoom < 1)
		xZoom = 1;
	if(yZoom < 1)
		yZoom = 1;
}

void GameCamera::OffsetPosition(glm::vec3 offset)
{
	position += offset;
}

void GameCamera::setOrthoMode(OrthoMode mode)
{
	m_orthoMode = mode;
}