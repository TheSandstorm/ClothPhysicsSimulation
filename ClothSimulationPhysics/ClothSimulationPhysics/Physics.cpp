#include "Physics.h"
#include <cmath>

bool Physics::isMouseColidingSphere(glm::vec3 _rayDirection, glm::vec3 _CameraPosition, glm::vec3 _Object)
{
	float radius = 1.0f;
	glm::vec3 v = _Object - _CameraPosition;
	float a = glm::dot(_rayDirection, _rayDirection);
	float b = 2 * glm::dot(v, _rayDirection);
	float c = glm::dot(v, v) - radius * radius;
	float d = b * b - 4 * a* c;
	if (d > 0) {
		float x1 = (-b - sqrt(d)) / 2;
		float x2 = (-b + sqrt(d)) / 2;
		if (x1 >= 0 && x2 >= 0) return true; // intersects
		if (x1 < 0 && x2 >= 0) return true; // intersects
	}
	else if (d <= 0) {
		return false;// no intersection
	}
	return false;
}

bool Physics::isMouseColidingQuad(glm::vec3 _rayDirection, glm::vec3 _CameraPosition, glm::vec3 _Object)
{
	float Scale = 0.1f;

	glm::vec3 dirfrac;

	// r.dir is unit direction vector of ray
	dirfrac.x = 1.0f / _rayDirection.x;
	dirfrac.y = 1.0f / _rayDirection.y;
	dirfrac.z = 1.0f / _rayDirection.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = ((_Object.x - Scale) - _CameraPosition.x)*dirfrac.x;
	float t2 = ((_Object.x + Scale) - _CameraPosition.x)*dirfrac.x;
	float t3 = ((_Object.y - Scale) - _CameraPosition.y)*dirfrac.y;
	float t4 = ((_Object.y + Scale) - _CameraPosition.y)*dirfrac.y;
	float t5 = ((_Object.z) - _CameraPosition.z)*dirfrac.z;
	float t6 = ((_Object.z) - _CameraPosition.z)*dirfrac.z;

	float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		//t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		//t = tmax;
		return false;
	}

	//t = tmin;
	return true;

}

bool Physics::isMouseColidingCube(glm::vec3 _rayDirection, glm::vec3 _CameraPosition, glm::vec3 _Object)
{
	float Scale = 0.1f;

	glm::vec3 dirfrac;

	// r.dir is unit direction vector of ray
	dirfrac.x = 1.0f / _rayDirection.x;
	dirfrac.y = 1.0f / _rayDirection.y;
	dirfrac.z = 1.0f / _rayDirection.z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = ((_Object.x - Scale) - _CameraPosition.x)*dirfrac.x;
	float t2 = ((_Object.x + Scale) - _CameraPosition.x)*dirfrac.x;
	float t3 = ((_Object.y - Scale) - _CameraPosition.y)*dirfrac.y;
	float t4 = ((_Object.y + Scale) - _CameraPosition.y)*dirfrac.y;
	float t5 = ((_Object.z - Scale) - _CameraPosition.z)*dirfrac.z;
	float t6 = ((_Object.z + Scale) - _CameraPosition.z)*dirfrac.z;

	float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		//t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		//t = tmax;
		return false;
	}

	//t = tmin;
	return true;
}
