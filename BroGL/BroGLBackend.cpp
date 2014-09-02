#include "BroGLBackend.h"


BroGLBackend::BroGLBackend() {
	//refdef = new RefDef();

	polys = new poly_t[MAX_POLYS];
	polyVerts = new vert[MAX_POLYVERTS];
}

BroGLBackend::BroGLBackend(BroGLWin* newWindow) {
	win = newWindow;

	polys = new poly_t[MAX_POLYS];
	polyVerts = new vert[MAX_POLYVERTS];
}

BroGLBackend::~BroGLBackend() {
	//delete refdef;
}

//************************************
// Method:    BeginDrawingView
// FullName:  BeginDrawingView
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void BroGLBackend::BeginDrawingView() {
	// Set the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(viewParms.projectionMatrix);
	glMatrixMode(GL_MODELVIEW);

	// Set window clipping 
	glViewport(viewParms.viewPortX, viewParms.viewPortY,
		viewParms.viewPortWidth, viewParms.viewPortHeight);
}

//************************************
// Method:    DrawSurfaces
// FullName:  BroGLBackend::DrawSurfaces
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Iterates through all objects and draws them.
//************************************
void BroGLBackend::DrawSurfaces(drawSurf_t *drawSurfs, int numDrawSurfs, RefDef *rd, viewParms_t vp) {
	// All of our data should be loaded in during this call.
	refdef = rd;
	viewParms = vp;

	// Render the drawing list
	RenderDrawSurfaceList(drawSurfs, numDrawSurfs);

	// End the frame
	if (win) {
		win->EndFrame();
	}
}

//************************************
// Method:    DrawTris
// FullName:  BroGLBackend::DrawTris
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Currently this is the catch all for rendering
//************************************
void BroGLBackend::DrawTris(shaderCommands_t *input) {

	// Add colors
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, input->vertexColors);

	// add vertices of polygon
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(vec4), input->xyz);

	// finally, draw
	glDrawElements(GL_TRIANGLES, input->numIndices, GL_UNSIGNED_INT, input->indexes);
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
void BroGLBackend::RenderDrawSurfaceList(drawSurf_t *drawSurfs, int numDrawSurfaces) {
	// local variables
	int i, entityNum = 0;
	drawSurf_t *drawSurf;

	// Perform any actions required before drawing the view (set model view, etc.)
	BeginDrawingView();

	// Draw loop
	for (i = 0, drawSurf = drawSurfs; i < numDrawSurfaces; i++, drawSurf++) {
		// Perform any actions necessary before drawing the surface
		// BeginSurface();

		// If entities contain multiple surfaces, some sort of sorting needs to be
		// applied first to make sure we are still referencing the same one.
		//currentEntity = &refdef->entities[entityNum++];

		// Set up the model view matrix, if necessary
		//RotateForEntity(currentEntity, &viewParms, &orientation);
		glLoadMatrixf(viewParms.world.modelMatrix);

		// Add the triangles to an index array - for now these represent our model.
		SurfaceTriangles(reinterpret_cast<triangles_t*>(drawSurf->surface));
	}

	// Draw the surface
	// EndSurface();
	DrawTris(&input);

	// Reset the model view matrix
	//glLoadMatrixf(viewParms.world.modelMatrix);

	// TODO: Commands will be issued by some sort of render thread, so there will
	// be no use for the class member input
	input.numIndices = 0;
	input.numVertices = 0;
}

//************************************
// Method:    SurfacePolychain
// FullName:  BroGLBackend::SurfacePolychain
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: poly * p
//************************************
void BroGLBackend::SurfacePolychain(poly_t *p) {
	int i, numVertices;

	numVertices = input.numVertices;
	for (i = 0; i < p->numVerts; i++) {
		// Copy poly vertices locations to input
		VectorCopy(p->verts[i].xyz, input.xyz[numVertices]);
		*(int *)&input.vertexColors[numVertices] = *(int *)p->verts[i].color;
		numVertices++;
	}

	// Generate indexes into the input array
	for (i = 0; i < p->numVerts - 2; i++) {
		input.indexes[input.numIndices + 0] = input.numVertices;
		input.indexes[input.numIndices + 1] = input.numVertices + i + 1;
		input.indexes[input.numIndices + 2] = input.numVertices + i + 2;
		input.numIndices += 3;
	}

	input.numVertices = numVertices;
}

//************************************
// Method:    SurfaceTriangles
// FullName:  BroGLBackend::SurfaceTriangles
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: triangles_t * srf
//************************************
void BroGLBackend::SurfaceTriangles(triangles_t *srf) {
	int			i;
	vert  	*dv;
	float		*xyz;
	byte		*color;

	for (i = 0; i < srf->numIndices; i += 3) {
		input.indexes[input.numIndices + i + 0] = input.numVertices + srf->indices[i + 0];
		input.indexes[input.numIndices + i + 1] = input.numVertices + srf->indices[i + 1];
		input.indexes[input.numIndices + i + 2] = input.numVertices + srf->indices[i + 2];
	}
	input.numIndices += srf->numIndices;

	dv = srf->verts;
	xyz = input.xyz[input.numVertices];
	color = input.vertexColors[input.numVertices];

	for (i = 0; i < srf->numVerts; i++, dv++, xyz += 4, color += 4) {
		xyz[0] = dv->xyz[0];
		xyz[1] = dv->xyz[1];
		xyz[2] = dv->xyz[2];

		*(int *)color = *(int *)dv->color;
	}

	input.numVertices += srf->numVerts;
}
