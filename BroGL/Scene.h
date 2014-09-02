#include "Entity.h"
#include "Renderer.h"
#include "RefDef.h"

#pragma once
class Scene {
public:
	Renderer *re;

	int firstSceneDrawSurf;

	int numEntities;
	int firstSceneEntity;

	int numPolys;
	int firstScenePoly;

	int numPolyVerts;

	Scene();
	Scene(Renderer *);
	virtual ~Scene();

	//************************************
	// Method:    AddEntityToScene
	// FullName:  Scene::AddEntityToScene
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: Entity * entity
	//************************************
	void AddEntityToScene(Entity *entity);

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
	void AddPolygonToScene(int numVerts, vert *verts, int numPolygons);

	//************************************
	// Method:    AddPolygonSurfaces
	// FullName:  Scene::AddPolygonSurfaces
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void AddPolygonSurfaces();

	//************************************
	// Method:    ClearScene
	// FullName:  Scene::ClearScene
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void ClearScene();

	//************************************
	// Method:    RenderScene
	// FullName:  Scene::RenderScene
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void RenderScene(RefDef *rd);

	//************************************
	// Method:    ToggleNewFrame
	// FullName:  Scene::ToggleNewFrame
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void ToggleNewFrame();
};
