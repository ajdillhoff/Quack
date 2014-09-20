#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
//#include <GL/freeglut.h>

#include "Scene.h"
#include "Renderer.h"

#define WINDOW_TITLE_PREFIX "BroGL"

int CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0;
HGLRC m_hrc;
Camera *camera = new Camera();
vec3 angles = { 0, 0, 0 };

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void Keyboard(unsigned char, int, int);
void ResizeFunction(int, int);
void RenderFunction(void);

int main(int argc, char* argv[]) {
	Initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[]) {
	InitWindow(argc, argv);

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
		);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitContextVersion(3, 1);
	glutInitContextFlags(GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);

	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if (WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
			);
		exit(EXIT_FAILURE);
	}

	// Init glew, too!
	glewInit();
	//bool result = CreateMyGLContext(WindowHandle);

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(Keyboard);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		// Translate positive z axis
		camera->viewOrigin[2] -= 0.3;
		std::cout << "DEBUG: w pressed\n";
		break;
	case 'a':
		// Turn left
		angles[0] += 0.5;
		AngleVectors(angles, camera->viewMatrix[0], camera->viewMatrix[1], camera->viewMatrix[2]);
		break;
	case 's':
		// Translate negative z axis
		camera->viewOrigin[2] += 0.3;
		break;
	case 'd':
		// Turn right
		angles[0] -= 0.5;
		AngleVectors(angles, camera->viewMatrix[0], camera->viewMatrix[1], camera->viewMatrix[2]);
		break;
	case 'r':
		// Translate positive y axis
		camera->viewOrigin[1] -= 0.3;
		break;
	case 'f':
		// Translate negative y axis
		camera->viewOrigin[1] += 0.3;
		break;
	case 'q':
		camera->viewOrigin[0] -= 0.3;
		break;
	case 'e':
		camera->viewOrigin[0] += 0.3;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void ResizeFunction(int Width, int Height) {
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	Renderer *re = new Renderer();

	RefDef *rd = new RefDef(camera);

	Scene *sc = new Scene(re);

	Entity *ent = new Entity();
	ent->GenerateTestEntity();

	sc->AddEntityToScene(ent);

	// Render the scene
	sc->RenderScene(rd);

	glutSwapBuffers();
}