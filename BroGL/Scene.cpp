#include "Scene.h"


Scene::Scene() {
	ToggleNewFrame();
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
	re->backend->entities[numEntities] = *entity;

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
void Scene::AddPolygonToScene(int numVerts, vert *verts, int numPolygons) {
	// For each poly, add the verts to the global vert list
	//poly_t *poly;
	//int j;

	//for (j = 0; j < numPolygons; j++) {
	//	if (re->numPolyVerts + numVerts > MAX_POLYVERTS || re->numPolys >= MAX_POLYS) {
	//		// Cannot add these
	//		return;
	//	}
	//	poly = &re->polys[re->numPolys];
	//	poly->surfaceType = SF_POLY;
	//	poly->numVerts = numVerts;
	//	poly->verts = &re->polyVerts[re->numPolyVerts];

	//	memcpy(poly->verts, &verts[numVerts*j], numVerts * sizeof(*verts));

	//	re->numPolys++;
	//	re->numPolyVerts += numVerts;
	//}
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
// Method:    ClearScene
// FullName:  Scene::ClearScene
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Scene::ClearScene() {
	firstSceneEntity = numEntities;
	firstScenePoly = numPolys;
}

//************************************
// Method:    RenderScene
// FullName:  Scene::RenderScene
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Scene::RenderScene(RefDef *rd) {
	viewParms_t parms;

	re->refdef->camera = rd->camera;

	// info about assets to be drawn
	// TODO: Conform to OOP styles
	re->refdef->numDrawSurfs = firstSceneDrawSurf;
	re->refdef->drawSurfs = re->backend->drawSurfs;

	re->refdef->numPolys = numPolys - firstScenePoly;
	re->refdef->polys = &re->backend->polys[firstScenePoly];

	re->refdef->numEntities = numEntities - firstSceneEntity;
	re->refdef->entities = &re->backend->entities[firstSceneEntity];

	// Set up view parameters for initial view
	memset(&parms, 0, sizeof(parms));
	parms.viewPortX = re->refdef->camera->x;
	parms.viewPortY = re->refdef->camera->y;
	parms.viewPortWidth = re->refdef->camera->width;
	parms.viewPortHeight = re->refdef->camera->height;

	parms.fovX = re->refdef->camera->fov_x;
	parms.fovY = re->refdef->camera->fov_y;

	VectorCopy(re->refdef->camera->viewOrigin, parms.or.origin);
	VectorCopy(re->refdef->camera->viewMatrix[0], parms.or.axis[0]);
	VectorCopy(re->refdef->camera->viewMatrix[1], parms.or.axis[1]);
	VectorCopy(re->refdef->camera->viewMatrix[2], parms.or.axis[2]);

	// Render the view
	re->RenderView(&parms);

	firstSceneDrawSurf = re->refdef->numDrawSurfs;
	firstSceneEntity = numEntities;
	firstScenePoly = numPolys;
}

//************************************
// Method:    ToggleNewFrame
// FullName:  Scene::ToggleNewFrame
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Scene::ToggleNewFrame() {
	firstSceneDrawSurf = 0;

	numEntities = 0;
	firstSceneEntity = 0;

	numPolys = 0;
	firstScenePoly = 0;

	numPolyVerts = 0;
}
