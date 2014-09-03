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
	// Set the viewport
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(viewParms.projectionMatrix);
	//glMatrixMode(GL_MODELVIEW);

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
	const GLchar* VertexShader =
	{
		"#version 400\n"\

		"layout(location=0) in vec4 in_Position;\n"\
		"layout(location=1) in vec4 in_Color;\n"\
		"out vec4 ex_Color;\n"\

		"uniform mat4 modelViewMatrix;\n"\
		"uniform mat4 projectionMatrix;\n"\

		"void main(void)\n"\
		"{\n"\
		"  gl_Position = projectionMatrix * modelViewMatrix * in_Position;\n"\
		"  ex_Color = in_Color;\n"\
		"}\n"
	};

	const GLchar* FragmentShader =
	{
		"#version 400\n"\

		"in vec4 ex_Color;\n"\
		"out vec4 out_Color;\n"\

		"void main(void)\n"\
		"{\n"\
		"  out_Color = ex_Color;\n"\
		"}\n"
	};

	int InfoLogLength;
	GLint Result = GL_FALSE;

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
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
void BroGLBackend::DrawTris(shaderCommands_t *input) {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// So much sloppy in here, apply this transformation somewhere else :))))
	GLuint modelViewMatrixId = glGetUniformLocation(ProgramId, "modelViewMatrix");
	glUniformMatrix4fv(modelViewMatrixId, 1, GL_FALSE, viewParms.world.modelMatrix);
	GLuint projectionMatrixId = glGetUniformLocation(ProgramId, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, viewParms.projectionMatrix);

	/* OpenGL 3+ stuff */
	// Set up the buffer arrays
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	// Vertex Buffer
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * input->numVertices, input->xyz, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec4), 0);
	glEnableVertexAttribArray(0);

	// Color Buffer
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color4f_t) * input->numVertices, input->vertexColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	// Index Buffer
	glGenBuffers(1, &IndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(input->indexes) * input->numIndices, input->indexes, GL_STATIC_DRAW);

	//glDrawArrays(GL_TRIANGLES, 0, input->numVertices);
	glDrawElements(GL_TRIANGLES, input->numIndices, GL_UNSIGNED_INT, 0);
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
		//currentEntity = &refdef->entities[entityNum++];

		// Set up the model view matrix, if necessary
		//RotateForEntity(currentEntity, &viewParms, &orientation);
		//glLoadMatrixf(viewParms.world.modelMatrix);

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
	// TODO - Since we are generating buffers, this may not be necessary
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
	float		*color;

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

		color[0] = dv->color[0];
		color[1] = dv->color[1];
		color[2] = dv->color[2];
		color[3] = dv->color[3];
		//*(color4f_t *)color = *(color4f_t *)dv->color;
	}

	input.numVertices += srf->numVerts;
}
