#include "Types.h"

#pragma once
class Entity {
public:
	Entity();
	virtual ~Entity();

	// Used for testing and debugging
	void TestEntity();

	float[3] direction[3];
	float origin[3];
	poly *polys;
};

