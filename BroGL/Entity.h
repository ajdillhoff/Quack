#include "Types.h"

#pragma once
class Entity {
public:
	Entity();
	virtual ~Entity();

	// Used for testing and debugging
	void GenerateTestEntity();

	vec3 direction[3];
	vec3 origin;
	poly_t *polys;
};

