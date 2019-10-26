#pragma once
#ifndef _OBJECT_H__
#define __OBJECT_H__
#include <glew.h>
#include <glm.hpp>
#include <glut.h>
#include <SOIL.h>
#include <vector>
#include "MeshManager.h"
#include "Resource.h"
#include "Camera.h"
class CObject
{
public:
	CObject();
	CObject(Object_Attributes _ObjectType, Shader_Attributes _ShaderType, const char* _TextureFile, glm::vec3 _Pos, glm::vec3 _Scale = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~CObject();
	virtual void Update(float _deltaTime);
	virtual glm::vec3& GetPos() { return Pos; };
	virtual glm::vec3& GetScale() { return Scale; };
	virtual glm::vec3& GetRotation() { return Rotation; };
	virtual glm::vec3& GetVelocity() { return Velocity; };
	virtual GLuint& GetTexture() { return Texture; };
	virtual void SetShader(GLuint _NewShader) { Shader = _NewShader; };
	virtual void Render();
	Shader_Attributes init_Shader_Type;

	virtual bool& GetScissor() { return isScissor; };
	virtual bool& GetStencil() { return isStencil; };

	Object_Attributes Object_Type;

	void SetPos(glm::vec3 newPos);
private:

protected:


	unsigned IndicesCount;

	GLuint VAO;
	GLuint Shader;
	GLuint Texture;

	glm::vec3 Pos;
	glm::vec3 Scale;
	glm::vec3 Rotation;
	glm::vec3 Velocity;

	glm::mat4 ModelMatrix;
	glm::mat4 VPMatrix;

	bool isScissor = false;
	bool isStencil = false;
};

//class CModelObject : public CObject
//{
//public:
//	CModelObject();
//	CModelObject(Object_Attributes ObjectType, glm::vec3 Pos);
//	virtual void Update(float deltaTime);
//	float GetSpeed() { return maxSpeed; };
//	float GetForce() { return maxForce; };
//	float HitRadius;
//protected:
//	virtual void Render();
//	std::shared_ptr<CObject> TargetObject;
//	std::shared_ptr<Model> model;
//	float maxSpeed;
//	float maxForce;
//};
#endif 