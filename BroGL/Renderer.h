#include <GL/freeglut.h>
#include <GL/glew.h>
#include <GL/glut.h>

#pragma once
class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	/*
	* DrawPolygon
	* Draws a polygon using OpenGL
	*/
	void DrawPolygon(int, int, GLfloat);

	/*
	* RenderView
	* Renders all of the objects loaded into the current view.
	*/
	void RenderView();
};

