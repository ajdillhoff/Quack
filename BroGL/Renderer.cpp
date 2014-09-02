#include "Renderer.h"

static GLfloat	s_flipMatrix[16] = {
	// convert from our coordinate system (looking down X)
	// to OpenGL's coordinate system (looking down -Z)
	0, 0, -1, 0,
	-1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 1
};

static float s_identityMatrix[16] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

Renderer::Renderer() {
	refdef = new RefDef();

	// Set up some default view parameters
}

Renderer::Renderer(BroGLBackend* be) {
	refdef = new RefDef();

	backend = be;
}

Renderer::~Renderer() {
	//delete refdef;
}

//************************************
// Method:    AddDrawSurface
// FullName:  Renderer::AddDrawSurface
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: surfaceType_t * s
//************************************
void Renderer::AddDrawSurface(surfaceType_t *s) {
	refdef->AddDrawSurf(s);
}

//************************************
// Method:    AddEntitySurfaces
// FullName:  Renderer::AddEntitySurfaces
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void Renderer::AddEntitySurfaces(void) {
	Entity *ent;

	for (	currentEntityNum = 0; 
				currentEntityNum < refdef->numEntities; 
				currentEntityNum++ ) {
		ent = currentEntity = &refdef->entities[currentEntityNum];

		refdef->AddDrawSurf(reinterpret_cast<surfaceType_t *>(ent->model));
	}
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
	// call back to the scene in order to get all of the polys
	// TODO: Let's just put something in the mean time...
	int i;
	poly_t *poly;

	for (i = 0, poly = refdef->polys; i < refdef->numPolys; i++, poly++) {
		// Add the poly 
		refdef->AddDrawSurf(reinterpret_cast<surfaceType_t*>(poly));
	}

	// Setup the projection matrix
	SetupProjectionMatrix();

	AddEntitySurfaces();
}

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
void Renderer::MyGlMultMatrix(const float *a, const float *b, float *out) {
	int		i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out[i * 4 + j] =
				a[i * 4 + 0] * b[0 * 4 + j]
				+ a[i * 4 + 1] * b[1 * 4 + j]
				+ a[i * 4 + 2] * b[2 * 4 + j]
				+ a[i * 4 + 3] * b[3 * 4 + j];
		}
	}
}

//************************************
// Method:    RenderView
// FullName:  Renderer::RenderView
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Renders all of the objects loaded into the current view.
//************************************
void Renderer::RenderView(viewParms_t *parms)
{
	viewParms = *parms;

	// Rotate for viewer
	RotateForViewer();

	// Generate all of the surfaces/polys to be drawn
	GenerateDrawSurfaces();

	// Draw the view
	/*DrawSurfaces();*/
	backend->DrawSurfaces(refdef->drawSurfs, refdef->numDrawSurfs, refdef, viewParms);
}

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
void Renderer::RotateForEntity(Entity *ent, viewParms_t *parms, orientation_t *or) {
	float glMatrix[16];

	VectorCopy(ent->origin, or->origin);

	VectorCopy(ent->direction[0], or->axis[0]);
	VectorCopy(ent->direction[1], or->axis[1]);
	VectorCopy(ent->direction[2], or->axis[2]);

	glMatrix[0] = or->axis[0][0];
	glMatrix[4] = or->axis[1][0];
	glMatrix[8] = or->axis[2][0];
	glMatrix[12] = or->origin[0];

	glMatrix[1] = or->axis[0][1];
	glMatrix[5] = or->axis[1][1];
	glMatrix[9] = or->axis[2][1];
	glMatrix[13] = or->origin[1];

	glMatrix[2] = or->axis[0][2];
	glMatrix[6] = or->axis[1][2];
	glMatrix[10] = or->axis[2][2];
	glMatrix[14] = or->origin[2];

	glMatrix[3] = 0;
	glMatrix[7] = 0;
	glMatrix[11] = 0;
	glMatrix[15] = 1;

	MyGlMultMatrix(glMatrix, parms->world.modelMatrix, or->modelMatrix);
}

//************************************
// Method:    RotateForViewer
// FullName:  Renderer::RotateForViewer
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Builds the "world-to-camera" matrix by taking the origin and
//              rotation information given.
//************************************
void Renderer::RotateForViewer() {
	float	viewerMatrix[16];
	vec3	origin;

	memset(&orientation, 0, sizeof(orientation));
	orientation.axis[0][0] = 1;
	orientation.axis[1][1] = 1;
	orientation.axis[2][2] = 1;
	VectorCopy(viewParms.or.origin, orientation.viewOrigin);

	// transform by the camera placement
	VectorCopy(viewParms.or.origin, origin);

	viewerMatrix[0] = viewParms.or.axis[0][0];
	viewerMatrix[4] = viewParms.or.axis[0][1];
	viewerMatrix[8] = viewParms.or.axis[0][2];
	viewerMatrix[12] = -origin[0] * viewerMatrix[0] + -origin[1] * viewerMatrix[4] + -origin[2] * viewerMatrix[8];

	viewerMatrix[1] = viewParms.or.axis[1][0];
	viewerMatrix[5] = viewParms.or.axis[1][1];
	viewerMatrix[9] = viewParms.or.axis[1][2];
	viewerMatrix[13] = -origin[0] * viewerMatrix[1] + -origin[1] * viewerMatrix[5] + -origin[2] * viewerMatrix[9];

	viewerMatrix[2] = viewParms.or.axis[2][0];
	viewerMatrix[6] = viewParms.or.axis[2][1];
	viewerMatrix[10] = viewParms.or.axis[2][2];
	viewerMatrix[14] = -origin[0] * viewerMatrix[2] + -origin[1] * viewerMatrix[6] + -origin[2] * viewerMatrix[10];

	viewerMatrix[3] = 0;
	viewerMatrix[7] = 0;
	viewerMatrix[11] = 0;
	viewerMatrix[15] = 1;

	// TODO: Just copy if we end up sticking with the identity matrix
	MyGlMultMatrix(viewerMatrix, s_identityMatrix, orientation.modelMatrix);

	viewParms.world = orientation;
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

	//float ViewDistance = 1 / tan(refdef->camera->fov_x * M_PI / 360.0f);

	float	xmin, xmax, ymin, ymax;
	float	width, height, depth;
	float	zNear, zFar;

	//
	// set up projection matrix
	//
	zNear = 1;
	zFar = 2048;

	ymax = zNear * tan(refdef->camera->fov_y * M_PI / 360.0f);
	ymin = -ymax;

	xmax = zNear * tan(refdef->camera->fov_x * M_PI / 360.0f);
	xmin = -xmax;

	width = xmax - xmin;
	height = ymax - ymin;
	depth = zFar - zNear;

	viewParms.projectionMatrix[0] = 2 * zNear / width;
	viewParms.projectionMatrix[4] = 0;
	viewParms.projectionMatrix[8] = (xmax + xmin) / width;	// normally 0
	viewParms.projectionMatrix[12] = 0;

	viewParms.projectionMatrix[1] = 0;
	viewParms.projectionMatrix[5] = 2 * zNear / height;
	viewParms.projectionMatrix[9] = (ymax + ymin) / height;	// normally 0
	viewParms.projectionMatrix[13] = 0;

	viewParms.projectionMatrix[2] = 0;
	viewParms.projectionMatrix[6] = 0;
	viewParms.projectionMatrix[10] = -(zFar + zNear) / depth;
	viewParms.projectionMatrix[14] = -2 * zFar * zNear / depth;

	viewParms.projectionMatrix[3] = 0;
	viewParms.projectionMatrix[7] = 0;
	viewParms.projectionMatrix[11] = -1;
	viewParms.projectionMatrix[15] = 0;

}
