#include "RefDef.h"


RefDef::RefDef() {
	camera = new Camera();
	numEntities = 0;
	numPolys = 0;
}


RefDef::~RefDef() {
	delete camera;
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
