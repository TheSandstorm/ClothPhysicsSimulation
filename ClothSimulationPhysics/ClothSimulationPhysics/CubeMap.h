#pragma once
#include <glew.h>
#include <glm.hpp>
#include <SOIL.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "ShaderLoader.h"

class CubeMap {
public:
	CubeMap();
	~CubeMap();
	void Render();
	GLuint GetTexture() { return Texture; };
	void SetShader(GLuint _shader) { Shader = _shader; };

private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 rotationZ;
	GLuint VAO;
	GLuint Texture;
	GLuint Shader;
};