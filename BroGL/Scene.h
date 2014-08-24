#pragma once
class Scene {
public:
	Scene();
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
	void AddPolygonToScene(int numVerts, float *verts, int numPolygons);

	//************************************
	// Method:    AddPolygonSurfaces
	// FullName:  Scene::AddPolygonSurfaces
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void AddPolygonSurfaces();

	//************************************
	// Method:    RenderScene
	// FullName:  Scene::RenderScene
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void RenderScene();
};

