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

	/*** TEST ***/
	//poly_t *polys;
	vert v1, v2, v3, v4, v5;

	v1.xyz[0] = 0.0;
	v1.xyz[1] = 0.0;
	v1.xyz[2] = 0.0;

	v2.xyz[0] = 0.5;
	v2.xyz[1] = 1.0;
	v2.xyz[2] = 0.5;

	v3.xyz[0] = 1.0;
	v3.xyz[1] = 0.0;
	v3.xyz[2] = 0.0;

	v4.xyz[0] = 1.0;
	v4.xyz[1] = 0.0;
	v4.xyz[2] = 1.0;

	v5.xyz[0] = 0.0;
	v5.xyz[1] = 0.0;
	v5.xyz[2] = 1.0;

	poly_t p1, p2, p3, p4;

	p1.numVerts = 3;
	p1.verts = new vert[p1.numVerts];
	p1.verts[0] = v1;
	p1.verts[1] = v2;
	p1.verts[2] = v3;

	p2.numVerts = 3;
	p2.verts = new vert[p2.numVerts];
	p2.verts[0] = v3;
	p2.verts[1] = v2;
	p2.verts[2] = v4;

	p3.numVerts = 3;
	p3.verts = new vert[p3.numVerts];
	p3.verts[0] = v4;
	p3.verts[1] = v2;
	p3.verts[2] = v5;

	p4.numVerts = 3;
	p4.verts = new vert[p4.numVerts];
	p4.verts[0] = v5;
	p4.verts[1] = v2;
	p4.verts[2] = v1;

	//polys = new poly_t[4];
	//polys[0] = p1;
	//polys[1] = p2;
	//polys[2] = p3;
	//polys[3] = p4;
	/*** TEST ***/

	Scene *sc = new Scene(re);
	sc->AddPolygonToScene(p1.numVerts, p1.verts, 1);
	sc->AddPolygonToScene(p2.numVerts, p2.verts, 1);
	sc->AddPolygonToScene(p3.numVerts, p3.verts, 1);
	sc->AddPolygonToScene(p4.numVerts, p4.verts, 1);

	// Add the first entity
	sc->RenderScene(rd);

	glutSwapBuffers();
}