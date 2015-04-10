#pragma once

#include "math_3d.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum OrthoMode
{
	OM_SCREEN, // range of 0-screenwidth
	OM_VIEW	   // range of -1 - 1
};

class GameCamera
{
public:
	GameCamera(void);
	~GameCamera(void);

	glm::vec3 getPosition() { return position;};
	void setPosition(const glm::vec3& _position){position = _position;};
	void OffsetPosition(glm::vec3 offset);
	void setOrthoMode(OrthoMode mode);

	float getFOV() { return fov;};
	void  setFOV(float _fov){ fov = _fov;};

	float getZNear(){return znear;};
	float getZFar(){return zfar;};
	void  setZPlanes(float _near, float _far){znear = _near; zfar = _far;};

	float getAspect(){return aspect;};
	void setAspectRatio(float ar){aspect = ar;};

	glm::mat4 View();
	glm::mat4 Projection();
	glm::mat4 Ortho();
	glm::mat4 VPMatrix();

	glm::vec2 GetDirection();
	glm::mat4 GetOrientation();
	void OffsetOrientation(float up, float right);
	void LookAt(glm::vec3 wPos);

	void Ortho(bool enable){isOrtho = enable;};

	// Movement
	glm::vec3 Left();
	glm::vec3 Right();
	glm::vec3 Up();
	glm::vec3 Forward();

	void OrthoZoomIn(float dist);
	void OrthoZoomOut(float dist);

	void SetScreen(float x, float y){screenWidth = x; screenHeight = y; xMax = xOrg+screenWidth; yMax = yOrg+screenHeight;};
	
private:
	OrthoMode m_orthoMode;
	bool isOrtho;
	glm::vec3 position;
	float horizontalAngle, verticalAngle, fov, znear, zfar, aspect;
	float xOrg, yOrg, xMax, yMax, screenWidth, screenHeight;
	float xZoom, yZoom, maxZoom;

	void Normalize();
};

