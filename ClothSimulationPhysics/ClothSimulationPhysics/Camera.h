#pragma once
#include "Resource.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <freeglut.h>
#include <iostream>

class CCamera
{
public:
	~CCamera();
	enum MODE {
		ORBIT,
		FOLLOW,
		FOLLOW_ORBIT,
		FOLLOW_STATIC,
		ORTH,
		PRESPECTIVE,
		MOUSE,
		PRESET1
	};
	static std::shared_ptr<CCamera> GetInstance();
	static void DestroyInstance();
	static void initializeCamera();
	void Tick(float deltaTime);
	void SwitchMode(MODE _mode, glm::vec3 _target, glm::vec3 _camPos, glm::vec3 _lookDirFromFollow, GLfloat _radius, GLfloat _height);
	void UpdateTarget(glm::vec3 _target) { camFollowTar = _target; };

	static glm::mat4 GetProjectionMatrix()
	{
		return proj;
	}

	static glm::mat4 GetViewMatrix()
	{
		return view;
	}

	static glm::mat4 GetVPMatrix()
	{
		return VPMat;
	};
	static glm::vec3& GetPos()
	{
		return camPos;
	}
	static glm::vec3& GetLookDir()
	{
		return camLookDir;
	}
	static glm::vec3 GetFront() { return Front; };
	static glm::vec3 GetRight() { return Right; };
	static glm::vec3 GetUpDir() { return camUpDir; };

private:

	glm::vec4 camStartPos = glm::vec4(0.0f, 0.0f, 15.0f, 1.0f);
	static glm::vec3 camPos;
	static glm::vec3 camLookDir;
	static glm::vec3 camUpDir;

	glm::mat4 rotMat;
	glm::vec4 newPos;

	static glm::mat4 view;
	static glm::vec3 Front, Up, Right;
	static glm::vec3 camTar;
	glm::vec3 camFollowTar;
	static glm::mat4 proj;
	static glm::mat4 VPMat;


	float halfw = 0.0f;
	float halfh = 0.0f;
	float maxRenderDistance = 20000.0f;
	float minRenderDistance = 0.1f;
	float FOV = 90.0f;
	float timeElapsed = 0.0f;

	float DistanceFromTarget = 50;

	GLfloat radius = 3.0f;
	GLfloat height = 3.0f;
	glm::vec3 lookDirFromFollow = glm::vec3(0.0f, 0.0f, 0.0f);

	bool staticCam = true;
	bool orbitCam = false;
	bool followCam = true;
	bool orthoMode = false;
	bool mouseMode = false;

	int activeMode = -1;

	static std::shared_ptr<CCamera> CameraPtr;

};