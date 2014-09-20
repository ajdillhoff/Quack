#include "Renderer.h"

Renderer::Renderer() {
	refdef = new RefDef();

	// Set up some default view parameters
}

Renderer::Renderer(QuackBackend* be) {
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
// Method:    RotateForViewer
// FullName:  Renderer::RotateForViewer
// Access:    public 
// Returns:   void
// Qualifier:
// Description: Builds the "world-to-camera" matrix by taking the origin and
//              rotation information given.
//************************************
void Renderer::RotateForViewer() {
	glm::mat4	viewerMatrix;
	glm::vec3	origin;

	memset(&orientation, 0, sizeof(orientation));
	orientation.axis = glm::mat4();
	orientation.viewOrigin = viewParms.or.origin;

	// transform by the camera placement
	origin = viewParms.or.origin;

	viewerMatrix = glm::mat4(viewParms.or.axis);
	viewerMatrix = glm::translate(viewerMatrix, -origin);

	orientation.modelMatrix = viewerMatrix;

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

	float	xmin, xmax, ymin, ymax;
	float	width, height, depth;
	float	zNear, zFar;

	//
	// set up projection matrix
	//
	zNear = 1;
	zFar = 10000;

	ymax = zNear * tan(refdef->camera->fov_y * M_PI / 360.0f);
	ymin = -ymax;

	xmax = zNear * tan(refdef->camera->fov_x * M_PI / 360.0f);
	xmin = -xmax;

	width = xmax - xmin;
	height = ymax - ymin;
	depth = zFar - zNear;

	viewParms.projectionMatrix[0][0] = 2 * zNear / width;
	viewParms.projectionMatrix[0][1] = 0;
	viewParms.projectionMatrix[0][2] = (xmax + xmin) / width;	// normally 0
	viewParms.projectionMatrix[0][3] = 0;

	viewParms.projectionMatrix[1][0] = 0;
	viewParms.projectionMatrix[1][1] = 2 * zNear / height;
	viewParms.projectionMatrix[1][2] = (ymax + ymin) / height;	// normally 0
	viewParms.projectionMatrix[1][3] = 0;

	viewParms.projectionMatrix[2][0] = 0;
	viewParms.projectionMatrix[2][1] = 0;
	viewParms.projectionMatrix[2][2] = -(zFar + zNear) / depth;
	viewParms.projectionMatrix[2][3] = -2 * zFar * zNear / depth;

	viewParms.projectionMatrix[3][0] = 0;
	viewParms.projectionMatrix[3][1] = 0;
	viewParms.projectionMatrix[3][2] = -1;
	viewParms.projectionMatrix[3][3] = 0;

}
