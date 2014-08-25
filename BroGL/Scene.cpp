#include "Scene.h"


Scene::Scene() {
}

Scene::Scene(Renderer *newRenderer) {
	re = newRenderer;
}

Scene::~Scene() {
}

//************************************
// Method:    AddEntityToScene
// FullName:  Scene::AddEntityToScene
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Entity * entity
//************************************
void Scene::AddEntityToScene(Entity *entity) {
	// Add the entity to the rendering list
	re->entities[re->numEntities++] = *entity;

	// Probably useless, but gives us a count for each scene
	numEntities++;
}

//************************************
// Method:    AddPolygonToScene
// FullName:  Scene::AddPolygonToScene
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int numVerts
// Parameter: float * verts
// Parameter: int numPolygons
//************************************
void Scene::AddPolygonToScene(int numVerts, float *verts, int numPolygons) {
	// For each poly, add the verts to the global vert list
}

//************************************
// Method:    AddPolygonSurfaces
// FullName:  Scene::AddPolygonSurfaces
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Scene::AddPolygonSurfaces() {
	// For each poly, add the drawing surface to the renderer surface list
}

//************************************
// Method:    RenderScene
// FullName:  Scene::RenderScene
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Scene::RenderScene(Camera *camera) {
	viewParms_t parms;

	re->camera = camera;
	// Copy scene surfaces to renderer global list

	// Set up view parameters
	memset(&parms, 0, sizeof(parms));
	parms.viewPortX = re->camera->x;
	parms.viewPortY = re->camera->y;
	parms.viewPortWidth = re->camera->width;
	parms.viewPortHeight = re->camera->height;

	parms.fovX = re->camera->fov_x;
	parms.fovY = re->camera->fov_y;

	VectorCopy(re->camera->viewOrigin, parms.or.origin);
	VectorCopy(re->camera->viewMatrix[0], parms.or.axis[0]);
	VectorCopy(re->camera->viewMatrix[1], parms.or.axis[1]);
	VectorCopy(re->camera->viewMatrix[2], parms.or.axis[2]);

	// Render the view
	re->RenderView(&parms);
}
