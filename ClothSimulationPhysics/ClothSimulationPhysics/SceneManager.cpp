#include "SceneManager.h"

std::shared_ptr<CSceneManager> CSceneManager::SceneManagerPtr;
SceneState CSceneManager::CurrentState;

int MousePosx;
int MousePosy;

CSceneManager::CSceneManager()
{
	CClock::GetInstance();
	deltaTime = CClock::GetDeltaTime();
	CCamera::GetInstance();
	MeshManager::GetInstance();
	CInputManager();

	//For Culling the objects
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	//Depth Test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 0.6f, 0.0f, 1.0f); //Orange

	//Creates the program for most models
	CurrentState = START_MENU;
	Title = std::make_shared<CTextLabel>("ClothPhysics", SoundnFonts::NormalFontString.data(), glm::vec2(-120.0f, 230.0f));
#pragma region StartMenu
	std::vector<std::string> StartOpt;
	StartOpt.push_back("Start");
	StartOpt.push_back("Quit");

	StartMenu = std::make_shared<CMenu>(StartOpt, glm::vec2(-90.0f, -200.0f));
#pragma endregion

	Fan = std::make_shared<CObject>(Object_Attributes::SPHERE_OBJECT, Shader_Attributes::STANDARD_SHADER, TexturePaths::UpTexture.data(), glm::vec3(0.0f, 0.0f, -20.0f));

}

void CSceneManager::DrawMenu()
{
	CCamera::GetInstance()->Tick(deltaTime);
	CM.Render();
	Title->Render();
	StartMenu->Render();
}

void CSceneManager::DrawDemo()
{
	CCamera::GetInstance()->Tick(deltaTime);
	CM.Render();
	Fan->Render();
	cloth->Render();
	//for (unsigned int i = 0; i < vertOfObjects.size(); i++)
	//{
	//	vertOfObjects[i]->Render();
	//}
}

void CSceneManager::InitDemo()
{
	CCamera::GetInstance()->SwitchMode(CCamera::MODE::MOUSE, Fan->GetPos(), glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3(0.0f,0.0f,1.0f), 3, 3);
	cloth = std::make_shared<Cloth>();
	cloth->Init();

}


void CSceneManager::UpdateLoop()
{
	//cloth->Update(deltaTime);
	cloth->ApplyForce(Fan->GetPos(), glm::vec3(0.0f, 0.0f, 10.0f) * CInputManager::GetFanSpeed(), 20.0f);
	if (CInputManager::KeyArray[27] == KEY_FIRST_PRESS) {
		CurrentState = START_MENU;
		return;
	}
	if (CInputManager::KeyArray['v'] == KEY_FIRST_PRESS)
	{
	}
	if (CInputManager::KeyArray['g'] == KEY_FIRST_PRESS) {
	}
	if (CInputManager::KeyArray['f'] == KEY_FIRST_PRESS) {
	}
	CInputManager::ProcessMouseInputs();
	CInputManager::MouseInputs();
	CInputManager::ProcessKeyInput(deltaTime);
	
}

CSceneManager::~CSceneManager()
{
	CCamera::DestroyInstance();
	MeshManager::DestroyInstance();
	CClock::DestroyInstance();
	Title = nullptr;
	StartMenu = nullptr;
}

void CSceneManager::Update()
{
	deltaTime = CClock::GetDeltaTime();

	switch (CurrentState)
	{

	case START_MENU: {
		int TempOutput = NULL;
		StartMenu->Process(TempOutput);
		CInputManager::ProcessKeyInput();

		switch (TempOutput) {
		case 0:
			CurrentState = DEMO_START;
			InitDemo();
			break;
		case 1:
			glutLeaveMainLoop();
			break;
		default:break;
		}
		break;
	}

	case DEMO_START:
	{
		UpdateLoop();
		break;
	}
	}
}

void CSceneManager::Render()
{
	//Clears the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	switch (CurrentState)
	{
	case START_MENU:
		DrawMenu();
		break;
	case DEMO_START:
		DrawDemo();
		//Switches states
		break;

	default:break;
	}
}

void CSceneManager::DestroyInstance()
{
	SceneManagerPtr = nullptr;
}

std::shared_ptr<CSceneManager> CSceneManager::GetInstance()
{
	if (SceneManagerPtr == nullptr) SceneManagerPtr = std::shared_ptr<CSceneManager>(new CSceneManager());
	return SceneManagerPtr;
}
