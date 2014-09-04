#include "Types.h"

#pragma once
class Entity {
public:
	Entity();
	virtual ~Entity();

	// Used for testing and debugging
	void GenerateTestEntity();

	glm::mat4 direction;
	glm::vec3 origin;

	triangles_t *model;   // our entity's model will be defined as basic geometry
};

