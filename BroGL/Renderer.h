#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "RefDef.h"
#include "Types.h"
#include "Entity.h"
#include <GL/freeglut.h>

#pragma once
class Renderer {
public:
	// Renderer State
	viewParms_t viewParms;
	orientation_t orientation;

	shaderCommands_t input;

	// Object information
	Entity *currentEntity;
	RefDef *refdef;

	//drawSurf_t drawSurfs[MAX_DRAWSURFS];
	Entity entities[MAX_ENTITIES];

	drawSurf_t drawSurfs[MAX_DRAWSURFS];

	int numPolys;
	int numPolyVerts;
	poly_t *polys;
	vert *polyVerts;

	Renderer();
	virtual ~Renderer();

	//************************************
	// Method:    AddDrawSurface
	// FullName:  Renderer::AddDrawSurface
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: surfaceType_t * s
	//************************************
	void AddDrawSurface(surfaceType_t *s);

	//************************************
	// Method:    BeginDrawingView
	// FullName:  Renderer::BeginDrawingView
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void BeginDrawingView();

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
	// Method:    DrawTris
	// FullName:  Renderer::DrawTris
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void DrawTris();

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
	// Method:    MyGlMultMatrix
	// FullName:  Renderer::MyGlMultMatrix
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const float * a
	// Parameter: const float * b
	// Parameter: float * out
	//************************************
	void Renderer::MyGlMultMatrix(const float *a, const float *b, float *out);

	//************************************
	// Method:    RenderDrawSurfaceList
	// FullName:  Renderer::RenderDrawSurfaceList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: The entry point for the rendering of polys or surfaces
	//************************************
	void RenderDrawSurfaceList(drawSurf_t *, int);

	//************************************
	// Method:    RenderView
	// FullName:  Renderer::RenderView
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Renders all of the objects loaded into the current view.
	//************************************
	void RenderView(viewParms_t *parms);

	//************************************
	// Method:    RotateForEntity
	// FullName:  Renderer::RotateForEntity
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: Entity * ent
	// Parameter: viewParms_t * parms
	// Parameter: orientation_t * or
	//************************************
	void RotateForEntity(Entity *ent, viewParms_t *parms, orientation_t *or);

	//************************************
	// Method:    RotateForViewer
	// FullName:  Renderer::RotateForViewer
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void RotateForViewer();

	//************************************
	// Method:    SetupProjectionMatrix
	// FullName:  Renderer::SetupProjectionMatrix
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Configures the proper projection matrix.
	//************************************
	void SetupProjectionMatrix();

	//************************************
	// Method:    SurfacePolychain
	// FullName:  Renderer::SurfacePolychain
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: poly * p
	//************************************
	void SurfacePolychain(poly_t *p);
};

