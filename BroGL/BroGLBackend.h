#pragma once

#include "BroGLWin.h"
#include "Types.h"
#include "Entity.h"
#include "RefDef.h"
#include "BShared.h"
#include "BroShader.h"

class BroGLBackend {
public:
	drawSurf_t drawSurfs[MAX_DRAWSURFS];
	Entity entities[MAX_ENTITIES];
	Entity *currentEntity;
	poly_t *polys;
	vert *polyVerts;

	viewParms_t viewParms;
	orientation_t orientation;

	shaderCommands_t input;

	RefDef *refdef;

	BroGLWin *win; // reference to window

	// Shader debug
	BroShader *shader;

	BroGLBackend();
	BroGLBackend(BroGLWin*);
	~BroGLBackend();

	//************************************
	// Method:    BeginDrawingView
	// FullName:  BeginDrawingView
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void BeginDrawingView();

	//************************************
	// Method:    CreateShaders
	// FullName:  BroGLBackend::CreateShaders
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Used to load and compile shaders
	// TODO: If shader operations become too big, consider moving all shader funcs
	// to their own class.
	//************************************
	void CreateShaders();

	//************************************
	// Method:    DrawSurfaces
	// FullName:  DrawSurfaces
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: Iterates through all surfaces and draws them.
	//************************************
	void DrawSurfaces(drawSurf_t *, int, RefDef *, viewParms_t);

	//************************************
	// Method:    DrawTris
	// FullName:  DrawTris
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void DrawTris();

	//************************************
	// Method:    RenderDrawSurfaceList
	// FullName:  RenderDrawSurfaceList
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Description: The entry point for the rendering of polys or surfaces
	//************************************
	void RenderDrawSurfaceList(drawSurf_t *, int);

	//************************************
	// Method:    RotateForEntity
	// FullName:  RotateForEntity
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: Entity * ent
	// Parameter: viewParms_t * parms
	// Parameter: orientation_t * or
	//************************************
	void RotateForEntity(Entity *ent, viewParms_t *parms, orientation_t *or);

	//************************************
	// Method:    SurfacePolychain
	// FullName:  SurfacePolychain
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: poly * p
	//************************************
	void SurfacePolychain(poly_t *p);

	//************************************
	// Method:    SurfaceTriangles
	// FullName:  SurfaceTriangles
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: triangles_t * srf
	//************************************
	void SurfaceTriangles(triangles_t *srf);

private:
	// For Drawing
	GLuint VertexShaderId,
		FragmentShaderId,
		ProgramId,
		VaoId,
		VboId,
		ColorBufferId,
		IndexBufferId;
};

