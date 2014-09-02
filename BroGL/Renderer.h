#include <math.h>
#include "BroGLBackend.h"

#pragma once
class Renderer {
public:
	// Renderer State
	viewParms_t viewParms;
	orientation_t orientation;

	shaderCommands_t input;

	// Temp for debugging
	BroGLBackend *backend;

	// Object information
	Entity *currentEntity;
	RefDef *refdef;

	//drawSurf_t drawSurfs[MAX_DRAWSURFS];
	int currentEntityNum;
	Entity entities[MAX_ENTITIES];

	drawSurf_t drawSurfs[MAX_DRAWSURFS];

	int numPolys;
	int numPolyVerts;

	Renderer();
	Renderer(BroGLBackend *);
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
	// Method:    AddEntitySurfaces
	// FullName:  Renderer::AddEntitySurfaces
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: void
	//************************************
	void AddEntitySurfaces(void);

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
};

