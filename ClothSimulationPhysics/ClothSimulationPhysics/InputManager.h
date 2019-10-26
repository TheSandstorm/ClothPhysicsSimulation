#pragma once
#include "Camera.h"
#include "Clock.h"
#include <glut.h>
#include <freeglut.h>

enum KEYSTATE {
	KEY_FIRST_PRESS,
	KEY_RELEASED,
	KEY_HELD,
};
enum WHEELSTATE {
	UP,
	DOWN,
	NEUTRAL
};

class CInputManager
{
public:
	CInputManager();
	static void ProcessMouseInputs();
	static void MouseInputs();
	static void MouseMovement(int x, int y);
	static void MouseButton(int button, int state, int x, int y);
	static void MouseWheel(int button, int dir, int x, int y);
	static void ProcessKeyInput(float _DeltaTime);
	static void ProcessKeyInput();
	static glm::vec2 GetMousePos() { return MousePos; };
	static glm::vec3 GetrayDirection() { return rayDirection; };
	static float GetFanSpeed() { return fanSpeed; };

	static unsigned char KeyArray[255];
	static unsigned char KeySpecialArray[255];
	static unsigned int MouseArray[3];
	static unsigned int WheelInput;

private:
	static void NormKeyDown(unsigned char key, int x, int y);
	static void NormKeyUp(unsigned char key, int x, int y);
	static void SpecialKeyDown(int key, int x, int y);
	static void SpecialKeyUp(int key, int x, int y);

	static float yaw;
	static float pitch;

	static void updateMousePicking();
	//Keeps current mouse position
	static glm::vec2 v2MouseLastPos;
	static glm::vec2 v2MouseCurrentPos;
	static glm::vec2 MousePos;
	static glm::vec2 NormMousePos;
	static glm::vec3 rayDirection;
	static float speed;
	static float fanSpeed;
};