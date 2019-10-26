#include "Camera.h"
#include "glm.hpp"
#include <iostream>
#include <freeglut.h>

std::shared_ptr<CCamera> CCamera::CameraPtr;
glm::mat4 CCamera::VPMat;
glm::mat4 CCamera::proj;
glm::mat4 CCamera::view;
glm::vec3 CCamera::camPos;
glm::vec3 CCamera::camLookDir;
glm::vec3 CCamera::camUpDir;
glm::vec3 CCamera::camTar;
glm::vec3 CCamera::Front;
glm::vec3 CCamera::Up;
glm::vec3 CCamera::Right;

std::shared_ptr<CCamera> CCamera::GetInstance()
{
	if (CameraPtr == nullptr)
	{
		CameraPtr = std::shared_ptr<CCamera>(new CCamera);
		CCamera::initializeCamera();
	}
	return CameraPtr;
}

CCamera::~CCamera()
{
	CameraPtr = nullptr;
}

void CCamera::DestroyInstance()
{
	CameraPtr = nullptr;
}

void CCamera::initializeCamera()
{
	std::wcout << "Initialising Camera...\n";
	
	camPos = glm::vec3(0.0f, 0.0f, 5.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, 1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	camTar = glm::vec3(0.0f, 0.0f, 0.0f);
	Front = glm::vec3{ 0.0f, 0.0f, 0.0f };
	Right = glm::vec3{ 0.0f, 0.0f, 0.0f };
	Up = glm::vec3{ 0.0f, 0.0f, 0.0f };
	std::wcout << "Initialised Camera\n";
}

void CCamera::Tick(float deltaTime)
{
	if (mouseMode)
	{
		camTar = camPos - Front;
		glm::vec3 tempUp = { 0.0f, 1.0f, 0.0f };

		Front = glm::normalize(camPos - (camTar + camLookDir));
		Right = glm::normalize(glm::cross(tempUp, Front));
		camUpDir = glm::normalize(glm::cross(Front, Right));

		view = glm::lookAt(camPos, camPos - Front, camUpDir);
		proj = glm::perspective(FOV / 2, (float)Utility::SCR_WIDTH / (float)Utility::SCR_HEIGHT, minRenderDistance, maxRenderDistance);
	}
	else
	{
		if (orbitCam) {
			timeElapsed += deltaTime;
			camPos.x = sin(timeElapsed) * radius;
			camPos.z = cos(timeElapsed) * radius;
			//camTar = glm::vec3(0.0f, 0.0f, 0.0f);
			if (followCam) {
				camTar = glm::vec3(camFollowTar + lookDirFromFollow);
				if (!staticCam) {
					camPos.x = (sin(timeElapsed) * radius) + camFollowTar.x;
					camPos.y = camFollowTar.y + height;
					camPos.z = (cos(timeElapsed) * radius) + camFollowTar.z;
				}
			}
			view = glm::lookAt(camPos, camTar, camUpDir);
			if (orthoMode) {
				halfw = (float)Utility::SCR_WIDTH * 0.5f;
				halfh = (float)Utility::SCR_HEIGHT * 0.5f;
				proj = glm::ortho(-halfw, halfw, -halfh, halfh, minRenderDistance, maxRenderDistance);
			}
			else {
				proj = glm::perspective(FOV / 2, (float)Utility::SCR_WIDTH / (float)Utility::SCR_HEIGHT, minRenderDistance, maxRenderDistance);
			}
		}
		else {
			camPos = glm::vec3(camPos);
			camTar = glm::vec3(0.0f, 0.0f, 0.0f);
			if (followCam) {
				camTar = glm::vec3(camFollowTar + lookDirFromFollow);
				if (!staticCam) {
					camPos.x = camFollowTar.x;
					camPos.y = camFollowTar.y + height;
					camPos.z = camFollowTar.z;
				}
			}
			view = glm::lookAt(camPos, camTar, camUpDir);
			if (orthoMode) {
				halfw = (float)Utility::SCR_WIDTH * 0.5f;
				halfh = (float)Utility::SCR_HEIGHT * 0.5f;
				proj = glm::ortho(-halfw, halfw, -halfh, halfh, minRenderDistance, maxRenderDistance);
			}
			else {
				proj = glm::perspective(FOV / 2, (float)Utility::SCR_WIDTH / (float)Utility::SCR_HEIGHT, minRenderDistance, maxRenderDistance);
			}
		}
	}
	VPMat = proj * view;
}

void CCamera::SwitchMode(MODE _mode, glm::vec3 _target, glm::vec3 _camPos, glm::vec3 _lookDirFromFollow, GLfloat _radius, GLfloat _height)
{

	switch (_mode)
	{
	case CCamera::ORBIT:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Orbit\n";
		}
		this->mouseMode = false;
		this->staticCam = true;
		this->orbitCam = true;
		this->followCam = false;
		this->radius = _radius;
		this->height = _height;
		this->camPos = _camPos;
		this->camTar = _target;
		this->camFollowTar = _target;
		this->lookDirFromFollow = _lookDirFromFollow;
		this->activeMode = _mode;
		break;
	}
	case CCamera::FOLLOW:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Follow\n";
		}
		this->mouseMode = false;
		this->staticCam = false;
		this->orbitCam = false;
		this->followCam = true;
		this->camPos = _camPos;
		this->camTar = _target;
		this->lookDirFromFollow = _lookDirFromFollow;
		this->camFollowTar = _target;
		this->radius = _radius;
		this->height = _height;
		this->activeMode = _mode;
		break;
	}
	case CCamera::FOLLOW_ORBIT:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Follow\n";
		}
		this->mouseMode = false;
		this->staticCam = false;
		this->orbitCam = true;
		this->followCam = true;
		this->camPos = _camPos;
		this->camTar = _target;
		this->lookDirFromFollow = _lookDirFromFollow;
		this->camFollowTar = _target;
		this->radius = _radius;
		this->height = _height;
		this->activeMode = _mode;
		break;
	}
	case CCamera::FOLLOW_STATIC:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Follow\n";
		}
		this->mouseMode = false;
		this->staticCam = true;
		this->orbitCam = false;
		this->followCam = true;
		this->camPos = _camPos;
		this->camStartPos = glm::vec4(camPos.x, camPos.y, camPos.z, 1);
		this->camTar = _target;
		this->camFollowTar = _target;
		this->lookDirFromFollow = _lookDirFromFollow;
		this->radius = _radius;
		this->height = _height;
		this->activeMode = _mode;
		break;
	}
	case CCamera::ORTH:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Orth\n";
		}
		this->orthoMode = true;
		this->mouseMode = false;
		this->activeMode = _mode;
		break;
	}
	case CCamera::PRESPECTIVE:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Perspective\n";
		}
		this->mouseMode = false;
		this->orthoMode = false;
		this->activeMode = _mode;
		break;
	}
	case CCamera::MOUSE:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Mouse\n";
		}
		this->mouseMode = true;
		this->activeMode = _mode;
	}
	case CCamera::PRESET1:
	{
		if (_mode != activeMode) {
			std::wcout << "Switching Camera Mode To Orbit\n";
		}
		this->activeMode = _mode;
		break;
	}
	default: {

		break;
	}
	}
}
