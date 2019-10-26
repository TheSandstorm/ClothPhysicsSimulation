#pragma once
#include <glm.hpp>
class Physics
{
public:
	static bool isMouseColidingSphere(glm::vec3 _rayDirection, glm::vec3 _CameraPosition, glm::vec3 _Object);
	static bool isMouseColidingQuad(glm::vec3 _rayDirection, glm::vec3 _CameraPosition, glm::vec3 _Object);
	static bool isMouseColidingCube(glm::vec3 _rayDirection, glm::vec3 _CameraPosition, glm::vec3 _Object);
};