#pragma once
#include "ShaderLoader.h"
#include "Clock.h"
#include "Camera.h"
#include "CubeMap.h"
#include "MeshManager.h"
#include "InputManager.h"
#include "TextManager.h"
#include "Menu.h"
#include "Cloth.h"
#include "ClothParticle.h"
#include "Physics.h"
#include "Object.h"
#include <glew.h>
#include <glut.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class CSceneManager
{
public:
	~CSceneManager();
	static void DestroyInstance();
	static std::shared_ptr<CSceneManager> GetInstance();

	void Update();
	void Render();
	static SceneState& GetState() { return CurrentState; };

private:
	static std::shared_ptr<CSceneManager> SceneManagerPtr;
	CSceneManager();

	//Parts of the game that can be rendered.
	void DrawMenu();
	void DrawDemo();

	void InitDemo();

	void UpdateLoop();

	std::shared_ptr<CTextLabel> Title;
	std::shared_ptr<CTextLabel> Instructions;

	std::vector<std::string> StartOpt;
	std::vector<std::string> OptOpt;

	std::shared_ptr<CMenu> StartMenu;
	std::shared_ptr<CMenu> OptionMenu;

	std::shared_ptr<CObject> Fan;

	std::shared_ptr<Cloth> cloth;
	std::shared_ptr<ClothParticle> heldParticle;

	GLfloat deltaTime;
	static SceneState CurrentState;

	CubeMap CM;
	GLuint CubeShader;

	//std::vector<std::shared_ptr<CObject>> vertOfObjects;
};