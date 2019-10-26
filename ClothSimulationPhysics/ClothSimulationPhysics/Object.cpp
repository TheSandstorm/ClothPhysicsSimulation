#include "Object.h"

void CheckNan(glm::vec3& _Vec) {
	for (int i = 0; i < 3; ++i) {
		if (isnan(_Vec.x)) _Vec.x = 0.0f;
		if (isnan(_Vec.y)) _Vec.y = 0.0f;
		if (isnan(_Vec.z)) _Vec.z = 0.0f;
	}
}

CObject::CObject()
{
}

CObject::CObject(Object_Attributes _ObjectType, Shader_Attributes _ShaderType, const char* _TextureFile, glm::vec3 _Pos , glm::vec3 _Scale)
{
	Scale = _Scale;
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Pos = _Pos;
	VAO = MeshManager::GetMesh(_ObjectType)->VAO;
	IndicesCount = MeshManager::GetMesh(_ObjectType)->IndicesCount;
	Texture = MeshManager::SetTexture(_TextureFile);
	Shader = MeshManager::GetShaderProgram(_ShaderType);
	Object_Type = _ObjectType;
}

CObject::~CObject()
{
}

void CObject::Render()
{

	if (isScissor)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(400, 0, 800, 800);
	}
	if (isStencil)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
	}
	VPMatrix = CCamera::GetVPMatrix();
	glUseProgram(Shader);

	//Binding the array
	glBindVertexArray(VAO);

	//Setting back face culling
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Setting and binding the correct texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	//Sending the texture to the GPU via uniform
	glUniform1i(glGetUniformLocation(Shader, "tex"), 0);

	//Translating the cube (x,y,z)
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), Pos);

	//Z Rotation
	glm::mat4 RotateZ =
		glm::rotate(
			glm::mat4(),
			glm::radians(Rotation.y),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);


	//Y Rotation
	glm::mat4 RotateY =
		glm::rotate(
			glm::mat4(),
			glm::radians(Rotation.y),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

	//X Rotation
	glm::mat4 RotateX =
		glm::rotate(
			glm::mat4(),
			glm::radians(Rotation.x),
			glm::vec3(1.0f, 0.0f, 0.0f)
		);

	glm::mat4 RotationMatrix = RotateX * RotateY * RotateZ;
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), Scale);

	ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

	glm::mat4 MVP = VPMatrix * ModelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(Shader, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniform3fv(glGetUniformLocation(Shader, "camPos"), 1, glm::value_ptr(CCamera::GetPos()));
	//Drawing the entity
	glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, 0);
	
	//Disabling backface culling
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	if (isScissor)
	{
		glDisable(GL_SCISSOR_TEST);
	}

	//Clearing the vertex array
	glBindVertexArray(0);
	glUseProgram(0);
}

void CObject::Update(float _deltaTime)
{

}

void CObject::SetPos(glm::vec3 newPos)
{
	Pos = newPos;
}

//CModelObject::CModelObject()
//{
//}
//
//CModelObject::CModelObject(Object_Attributes ObjectType, glm::vec3 Pos)
//{
//	Scale = glm::vec3(0.1f, 0.1f, 0.1f);
//	Rotation = glm::vec3();
//	Pos = Pos;
//	Velocity = glm::vec3();
//	model = MeshManager::GetModel(ObjectType);
//	Object_Type = ObjectType;
//}
//
//void CModelObject::Update(float deltaTime)
//{
//	Pos += Velocity * 30.0f * deltaTime;
//}
//
//void CModelObject::Render()
//{
//	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(Pos.x, Pos.y, Pos.z + 30.0f) / 375.0f);
//
//	float PI = 3.14159265359f;
//	float angle;
//	angle = atan2f(Velocity.x, Velocity.y) * (180.0f / PI);
//
//	//X Rotation
//	glm::mat4 RotateX =
//		glm::rotate(
//			glm::mat4(),
//			glm::radians(Rotation.x + 90.0f),
//			glm::vec3(1.0f, 0.0f, 0.0f)
//		);
//
//	glm::mat4 RotateY =
//		glm::rotate(
//			glm::mat4(),
//			glm::radians(Rotation.y + (angle * -1.0f)),
//			glm::vec3(0.0f, 1.0f, 0.0f)
//		);
//
//	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(Scale));
//	glm::mat4 ModelMatrix = TranslationMatrix * (RotateX * RotateY) * ScaleMatrix;
//	glUniform3fv(glGetUniformLocation(Shader, "camPos"), 1, glm::value_ptr(CCamera::GetPos()));
//	model->Render(ModelMatrix);
//}
