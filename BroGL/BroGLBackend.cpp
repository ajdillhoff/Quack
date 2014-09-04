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

	CreateShaders();
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
	// Set the projection matrix
	shader->SetUniform("projectionMatrix", viewParms.projectionMatrix);

	// Set window clipping 
	glViewport(viewParms.viewPortX, viewParms.viewPortY,
		viewParms.viewPortWidth, viewParms.viewPortHeight);
}

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
void BroGLBackend::CreateShaders() {
	shader = new BroShader();
	shader->Compile();
	shader->Link();
	shader->Use();
}

//************************************
// Method:    DrawSurfaces
// FullName:  BroGLBackend::DrawSurfaces
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Iterates through all objects and draws them.
//************************************
void BroGLBackend::DrawSurfaces(drawSurf_t *drawSurfs,
	int numDrawSurfs,
	RefDef *rd,
	viewParms_t vp) {
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
void BroGLBackend::DrawTris() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* OpenGL 3+ stuff */
	// Set up the buffer arrays
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	// Vertex Buffer
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* input.numVertices, &input.xyz[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
	glEnableVertexAttribArray(0);

	// Color Buffer
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color4f_t)* input.numVertices, input.vertexColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	// Index Buffer
	glGenBuffers(1, &IndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(input.indexes) * input.numIndices, input.indexes, GL_STATIC_DRAW);

	//glDrawArrays(GL_TRIANGLES, 0, input.numVertices);
	glDrawElements(GL_TRIANGLES, input.numIndices, GL_UNSIGNED_INT, 0);

	// Destroy the buffer objects
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &IndexBufferId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
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
void BroGLBackend::RenderDrawSurfaceList(drawSurf_t *drawSurfs,
	int numDrawSurfaces) {
	// local variables
	int i, entityNum = 0;
	drawSurf_t *drawSurf;

	// Perform actions required before drawing the view (set model view, etc.)
	BeginDrawingView();

	// Draw loop
	for (i = 0, drawSurf = drawSurfs; i < numDrawSurfaces; i++, drawSurf++) {
		// Perform any actions necessary before drawing the surface
		// BeginSurface();

		// If entities contain multiple surfaces, some sort of sorting needs to be
		// applied first to make sure we are still referencing the same one.
		currentEntity = &entities[entityNum++];

		// Set up the model view matrix, if necessary
		RotateForEntity(currentEntity, &viewParms, &orientation);
		shader->SetUniform("modelViewMatrix", orientation.modelMatrix);

		// Add the triangles to an index array - for now these represent our model.
		SurfaceTriangles(reinterpret_cast<triangles_t*>(drawSurf->surface));
	}

	// Draw the surface
	// EndSurface();
	DrawTris();

	// Reset the model view matrix
	//glLoadMatrixf(viewParms.world.modelMatrix);

	// TODO: Commands will be issued by some sort of render thread, so there will
	// be no use for the class member input
	input.numIndices = 0;
	input.numVertices = 0;
}

//************************************
// Method:    RotateForEntity
// FullName:  BroGLBackend::RotateForEntity
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Entity * ent
// Parameter: viewParms_t * parms
// Parameter: orientation_t * or
//************************************
void BroGLBackend::RotateForEntity(Entity *ent, viewParms_t *parms, orientation_t *or) {
	or->origin = ent->origin;
	or->axis = ent->direction;

	glm::mat4 glMatrix = glm::mat4(or->axis);
	glMatrix[0][3] = or->origin[0];
	glMatrix[1][3] = or->origin[1];
	glMatrix[2][3] = or->origin[2];

	or->modelMatrix = parms->world.modelMatrix * glMatrix;
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
		input.xyz[numVertices] = glm::vec4(p->verts[i].xyz, 1.0);
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
	float		*color;

	for (i = 0; i < srf->numIndices; i += 3) {
		input.indexes[input.numIndices + i + 0] = input.numVertices + srf->indices[i + 0];
		input.indexes[input.numIndices + i + 1] = input.numVertices + srf->indices[i + 1];
		input.indexes[input.numIndices + i + 2] = input.numVertices + srf->indices[i + 2];
	}
	input.numIndices += srf->numIndices;

	dv = srf->verts;
	color = input.vertexColors[input.numVertices];

	for (i = 0; i < srf->numVerts; i++, dv++, color += 4) {
		input.xyz[input.numVertices + i] = glm::vec4(dv->xyz, 1.0);

		color[0] = dv->color[0];
		color[1] = dv->color[1];
		color[2] = dv->color[2];
		color[3] = dv->color[3];
	}

	input.numVertices += srf->numVerts;
}
