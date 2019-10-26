#include "SceneManager.h"
#include "Resource.h"
#include <iostream>
#include <glew.h>
#include <freeglut.h>

using namespace std;


void Update()
{
	CSceneManager::GetInstance()->Update();
	glutPostRedisplay();
}

void Render()
{
	CSceneManager::GetInstance()->Render();
	glutSwapBuffers();
}

void Exit()
{
	CSceneManager::DestroyInstance();
	exit(1);
}

int main(int argc, char **argv)
{
	srand(static_cast<int>(time(NULL)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(Utility::SCR_WIDTH, Utility::SCR_HEIGHT);
	glutCreateWindow("ClothSim - Physics");

	glutSetOption(GLUT_MULTISAMPLE, 8);

	//Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		//If glew setup failed thenapplication will not run graphics correctly
		cout << "Glew Initialization Failed. Aborting Application." << endl;
		system("pause");
	}
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	CSceneManager::GetInstance();


	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutCloseFunc(Exit);
	glutMainLoop();
	return (0);
}