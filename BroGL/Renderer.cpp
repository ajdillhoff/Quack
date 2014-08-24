#include "Renderer.h"


Renderer::Renderer() {
}

Renderer::Renderer(CDC *newDC) {
	pDC = newDC;

	Renderer();
}

Renderer::~Renderer() {
}

//************************************
// Method:    DrawPolygon
// FullName:  Renderer::DrawPolygon
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: GLfloat
// Description: Draws a polygon using OpenGL.
// TODO: Determine if this method is even going to be used.
//************************************
void Renderer::DrawPolygon(GLfloat glVertexBuffer) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(glVertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);

	SwapBuffers(pDC->m_hDC); // TODO: Send the context here
}

//************************************
// Method:    DrawSurfaces
// FullName:  Renderer::DrawSurfaces
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Iterates through all objects and draws them.
//************************************
void Renderer::DrawSurfaces() {
	// All of our data should be loaded in during this call.

	// Render the drawing list
	RenderDrawSurfaceList();
}

//************************************
// Method:    GenerateDrawSurfaces
// FullName:  Renderer::GenerateDrawSurfaces
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Adds all of the view's objects to the list of draw surfaces.
//************************************
void Renderer::GenerateDrawSurfaces() {
	// Add all of the different types of surfaces necessary

	// Setup the projection matrix
	SetupProjectionMatrix();
}

//************************************
// Method:    RenderDrawSurfaceList
// FullName:  RenderDrawSurfaceList
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int surfaceType
// Parameter: int numDrawSurfaces
// Description: The entry point for the rendering of surfaces
//************************************
void Renderer::RenderDrawSurfaceList(int surfaceType, int numDrawSurfaces) {
	// local variables
	int i;

	// Perform any actions required before drawing the view (set model view, etc.)

	// Draw loop
	for (i = 0; i < numDrawSurfaces; i++) {
		// Perform any actions necessary before drawing the surface

		// Set up the model view matrix, if necessary

		// Add the triangles to an index array

		// Draw the surface
		// Note: Look into use glDrawElements instead of glDrawArrays
	}

	// Reset the model view matrix
}

//************************************
// Method:    RenderView
// FullName:  Renderer::RenderView
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Renders all of the objects loaded into the current view.
//************************************
void Renderer::RenderView() {
	// Generate all of the surfaces to be drawn
	GenerateDrawSurfaces();

	// Draw the view
	DrawSurfaces();
}

//************************************
// Method:    SetupProjectionMatrix
// FullName:  Renderer::SetupProjectionMatrix
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Configures the proper projection matrix.
//************************************
void Renderer::SetupProjectionMatrix() {
	// TODO: This is very simple for now. The data should come from outside of
	// the rendering class. For example, the view parameters are different for
	// each scene.

	float ViewDistance = 1 / tan(45.0f * M_PI / 180.0f);

	projectionMatrix[0] = 1;
	projectionMatrix[4] = 0;
	projectionMatrix[8] = 0;	// normally 0
	projectionMatrix[12] = 0;

	projectionMatrix[1] = 0;
	projectionMatrix[5] = 1;
	projectionMatrix[9] = 0;	// normally 0
	projectionMatrix[13] = 0;

	projectionMatrix[2] = 0;
	projectionMatrix[6] = 0;
	projectionMatrix[10] = 1;
	projectionMatrix[14] = 1 / ViewDistance;

	projectionMatrix[3] = 0;
	projectionMatrix[7] = 0;
	projectionMatrix[11] = 0;
	projectionMatrix[15] = 0;

}
