#include <GL/freeglut.h>
#include <GL/glew.h>
#include <GL/glut.h>

#pragma once
class Renderer {
public:
	CDC *pDC;
	float projectionMatrix[16];

	Renderer();
	Renderer(CDC*);
	virtual ~Renderer();

	//************************************
	// Method:    DrawPolygon
	// FullName:  Renderer::DrawPolygon
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: GLfloat
	// Description: Draws a polygon using OpenGL.
	//************************************
	void DrawPolygon(GLfloat);

	//************************************
	// Method:    DrawSurfaces
	// FullName:  Renderer::DrawSurfaces
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Iterates through all surfaces and draws them.
	//************************************
	void DrawSurfaces();

	//************************************
	// Method:    GenerateDrawSurfaces
	// FullName:  Renderer::GenerateDrawSurfaces
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Adds all of the view's objects to the list of draw surfaces.
	//************************************
	void GenerateDrawSurfaces();

	//************************************
	// Method:    RenderDrawSurfaceList
	// FullName:  Renderer::RenderDrawSurfaceList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: The entry point for the rendering of polys or surfaces
	//************************************
	void RenderDrawSurfaceList(int, int);

	//************************************
	// Method:    RenderView
	// FullName:  Renderer::RenderView
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Renders all of the objects loaded into the current view.
	//************************************
	void RenderView();

	//************************************
	// Method:    SetupProjectionMatrix
	// FullName:  Renderer::SetupProjectionMatrix
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Configures the proper projection matrix.
	//************************************
	void SetupProjectionMatrix();
};

