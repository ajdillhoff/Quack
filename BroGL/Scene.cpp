#include "Scene.h"


Scene::Scene() {
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
void Renderer::AddPolygonToScene(int numVerts, float *verts, int numPolygons) {
	// For each poly, add the verts to the global vert list
}

//************************************
// Method:    AddPolygonSurfaces
// FullName:  Scene::AddPolygonSurfaces
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Renderer::AddPolygonSurfaces() {
	// For each poly, add the drawing surface to the renderer surface list
}

//************************************
// Method:    RenderScene
// FullName:  Scene::RenderScene
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Renderer::RenderScene() {
	// Copy scene surfaces to renderer global list

	// Set up view parameters

	// Render the view
}
