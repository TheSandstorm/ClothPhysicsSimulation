#include "InputManager.h"

unsigned char CInputManager::KeyArray[255];
unsigned char CInputManager::KeySpecialArray[255];
unsigned int CInputManager::MouseArray[];
unsigned int CInputManager::WheelInput;
glm::vec2 CInputManager::v2MouseLastPos = { 0.0f, 0.0f };
glm::vec2 CInputManager::v2MouseCurrentPos = { 0.0f, 0.0f };
float CInputManager::speed = 30.0f;
glm::vec2 CInputManager::MousePos = glm::vec2();
glm::vec2 CInputManager::NormMousePos;
glm::vec3 CInputManager::rayDirection;

float CInputManager::yaw = -90.0f;
float CInputManager::pitch = 0.0f;
float CInputManager::fanSpeed = 0.5f;


CInputManager::CInputManager() {
	for (int i = 0; i < 255; ++i) {
		KeyArray[i] = KEY_RELEASED;
		KeySpecialArray[i] = KEY_RELEASED;
	}
	for (int i = 0; i < 3; ++i) MouseArray[i] = KEY_RELEASED;
	WheelInput = NEUTRAL;
}

void CInputManager::ProcessMouseInputs()
{
	if (CInputManager::MouseArray[0] == KEY_HELD) {
		glm::vec2 dis = CInputManager::v2MouseLastPos - CInputManager::v2MouseCurrentPos;
		float xDif = (dis.x) * 0.1f ;
		float yDif = (-dis.y) * 0.1f ;

		yaw += xDif;
		pitch += yDif;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		CCamera::GetLookDir() = glm::normalize(front);
		CInputManager::v2MouseLastPos = CInputManager::v2MouseCurrentPos;
	}
}

void CInputManager::MouseInputs()
{
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMovement);
	glutPassiveMotionFunc(MouseMovement);
	//glutMouseWheelFunc(MouseWheel);
	//processing the mouse buttons
	for (int i = 0; i < 3; ++i) {
		if (MouseArray[i] == KEY_FIRST_PRESS) {
			MouseArray[i] = KEY_HELD;
		}
	}
}

void CInputManager::MouseMovement(int x, int y)
{
	MousePos = glm::vec2(x, y);
	v2MouseCurrentPos = glm::vec2(x, y);
	NormMousePos = glm::vec2((2.0f * x) / (float)Utility::SCR_WIDTH - 1.0f, 1.0f - (2.0f*y) / (float)Utility::SCR_HEIGHT);
	updateMousePicking();
}

void CInputManager::MouseButton(int button, int state, int x, int y)
{
	if (button < 3) {
		if (state == GLUT_DOWN)
		{
			std::cout << x << "\n" << y << std::endl;
			MouseArray[button] = KEY_FIRST_PRESS;
			v2MouseLastPos = { x, y };
			v2MouseCurrentPos = { x, y };
			MousePos = glm::vec2(x, y);
			NormMousePos = glm::vec2((2.0f * x) / (float)Utility::SCR_WIDTH - 1.0f, 1.0f - (2.0f*y) / (float)Utility::SCR_HEIGHT);
			updateMousePicking();
		}
		else if (state == GLUT_UP) MouseArray[button] = KEY_RELEASED;
	}
}

void CInputManager::MouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		MouseArray[button] = KEY_FIRST_PRESS;
	}
	else if (dir < 0)
	{
		MouseArray[button] = KEY_HELD;
	}
	else
	{
		MouseArray[button] = KEY_RELEASED;
	}
}

//Camera Movement
void CInputManager::ProcessKeyInput(float _DeltaTime) {

	auto CameraPos = &CCamera::GetPos();

	auto CameraFront = glm::normalize(CCamera::GetFront());
	auto CameraRight = glm::normalize(CCamera::GetRight());
	auto CameraUp = glm::normalize(CCamera::GetUpDir());

	//Movement speed Increase
	if(CInputManager::KeyArray['p'] == KEY_FIRST_PRESS)
	{
		speed += 5.0f;
		if (speed >= 60.1f)
		{
			speed = 60.0f;
		}
	}
	//Movement speed Decrease
	if (CInputManager::KeyArray['o'] == KEY_FIRST_PRESS)
	{
		speed -= 5.0f;
		if (speed <= 0.0f)
		{
			speed = 5.0f;
		}
	}

	//Forward
	if (CInputManager::KeyArray['w'] == KEY_HELD) {
		CCamera::GetPos() -= (CameraFront * speed * _DeltaTime);
	}
	if (CInputManager::KeyArray['s'] == KEY_HELD) {
		CCamera::GetPos() += (CameraFront * speed * _DeltaTime);
	}
	if (CInputManager::KeyArray['a'] == KEY_HELD) {
		CCamera::GetPos() -= (CameraRight * speed * _DeltaTime);
	}
	if (CInputManager::KeyArray['d'] == KEY_HELD) {
		CCamera::GetPos() += (CameraRight * speed * _DeltaTime);
	}
	//Up (Don't NEED to use this really)
	if (CInputManager::KeyArray[32] == KEY_HELD) {
		CameraPos->y += speed * _DeltaTime;
	}
	//Down (Don't NEED to use this really)
	if (CInputManager::KeySpecialArray[GLUT_KEY_SHIFT_L] == KEY_HELD) {
		CameraPos->y -= speed * _DeltaTime;
	}
	if (KeyArray[27] == KEY_HELD) {
		//glutLeaveMainLoop();
		return;
	}

	if (CInputManager::KeyArray['n'] == KEY_FIRST_PRESS) {
		fanSpeed < 0 ? fanSpeed -= 0.5f : fanSpeed = 0.0f;
	}
	if (CInputManager::KeyArray['m'] == KEY_FIRST_PRESS) {
		fanSpeed += 0.5f;
	}

	if (KeyArray['r'] == KEY_FIRST_PRESS)
	{
		KeyArray['r'] = KEY_HELD;
	}


	for (int i = 0; i < 255; ++i) {
		if (KeyArray[i] == KEY_FIRST_PRESS) {
			KeyArray[i] = KEY_HELD;
		}
		if (KeySpecialArray[i] == KEY_FIRST_PRESS) {
			KeySpecialArray[i] = KEY_HELD;
		}
	}
	glutSpecialFunc(CInputManager::SpecialKeyDown);
	glutSpecialUpFunc(CInputManager::SpecialKeyUp);
	glutKeyboardFunc(CInputManager::NormKeyDown);
	glutKeyboardUpFunc(CInputManager::NormKeyUp);
}

//Menu input
void CInputManager::ProcessKeyInput() {
	glutSpecialFunc(CInputManager::SpecialKeyDown);
	glutSpecialUpFunc(CInputManager::SpecialKeyUp);
	glutKeyboardFunc(CInputManager::NormKeyDown);
	glutKeyboardUpFunc(CInputManager::NormKeyUp);

	//UP KEY INPUT
	if (KeySpecialArray[GLUT_KEY_UP] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_UP] == KEY_FIRST_PRESS) {
		KeySpecialArray[GLUT_KEY_UP] = KEY_HELD;
	}

	//DOWN KEY INPUT
	else if (KeySpecialArray[GLUT_KEY_DOWN] == KEY_HELD) {
		//Held Stuff
	}
	else if (KeySpecialArray[GLUT_KEY_DOWN] == KEY_FIRST_PRESS) {
		KeySpecialArray[GLUT_KEY_DOWN] = KEY_HELD;
	}

	//ENTER KEY INPUT
	if (KeyArray['\r'] == KEY_HELD) {

	}
	else if (KeyArray['\r'] == KEY_FIRST_PRESS) {
		KeyArray['\r'] = KEY_HELD;
	}



}

void CInputManager::NormKeyDown(unsigned char key, int x, int y) {
	KeyArray[key] = KEY_FIRST_PRESS;
}

void CInputManager::NormKeyUp(unsigned char key, int x, int y) {
	KeyArray[key] = KEY_RELEASED;
}

void CInputManager::SpecialKeyDown(int key, int x, int y) {
	KeySpecialArray[key] = KEY_FIRST_PRESS;
}

void CInputManager::SpecialKeyUp(int key, int x, int y) {
	KeySpecialArray[key] = KEY_RELEASED;
}

void CInputManager::updateMousePicking()
{
	glm::vec2 normalizedScreenPos = NormMousePos;

	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	glm::mat4 invProjMat = glm::inverse(CCamera::GetInstance()->GetProjectionMatrix());

	glm::vec4 eyeCoords = invProjMat * clipCoords;

	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	glm::mat4 invViewMat = glm::inverse(CCamera::GetInstance()->GetViewMatrix());

	glm::vec4 rayWorld = invViewMat * eyeCoords;

	rayDirection = glm::normalize(glm::vec3(rayWorld));
}
