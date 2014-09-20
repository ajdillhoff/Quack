#include "BShared.h"
#include "QuackBackend.h"

#pragma once
class Renderer {
public:
	// Renderer State
	viewParms_t viewParms;
	orientation_t orientation;

	shaderCommands_t input;

	// Temp for debugging
	QuackBackend *backend;

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
	Renderer(QuackBackend *);
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
	// Method:    RenderView
	// FullName:  Renderer::RenderView
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Renders all of the objects loaded into the current view.
	//************************************
	void RenderView(viewParms_t *parms);

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

