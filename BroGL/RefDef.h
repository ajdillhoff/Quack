#pragma once

#include "Camera.h"
#include "Entity.h"

class RefDef {
public:
	Camera *camera;

	int numEntities;
	Entity entities[MAX_ENTITIES];

	int numPolys;
	poly *polys;

	RefDef();
	virtual ~RefDef();

	//************************************
	// Method:    AddEntity
	// FullName:  RefDef::AddEntity
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: Entity *
	//************************************
	int AddEntity(Entity*);
};
