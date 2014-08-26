#include "RefDef.h"


RefDef::RefDef() {
	camera = new Camera();
	numEntities = 0;
	numPolys = 0;
	numDrawSurfs = 0;
}


RefDef::~RefDef() {
	delete camera;
}

//************************************
// Method:    AddDrawSurf
// FullName:  RefDef::AddDrawSurf
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: surfaceType_t * surface
//************************************
int RefDef::AddDrawSurf(surfaceType_t *surface) {
	int i = numDrawSurfs;

	drawSurfs[numDrawSurfs++].surface = surface;

	return i;
}

//************************************
// Method:    AddEntity
// FullName:  RefDef::AddEntity
// Access:    public 
// Returns:   int - 0 success, 1 failure
// Qualifier:
// Parameter: Entity *
//************************************
int RefDef::AddEntity(Entity *ent) {
	if (numEntities >= MAX_ENTITIES) {
		return 1;
	}

	entities[numEntities++] = *ent;
	return 0;
}