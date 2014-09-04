#include "Entity.h"


Entity::Entity() {
	model = new triangles_t;
}


Entity::~Entity() {
	delete model;
}

void Entity::GenerateTestEntity() {
	vert v1, v2, v3, v4, v5;

	v1.xyz[0] = 0.0;
	v1.xyz[1] = 0.0;
	v1.xyz[2] = 0.0;
	v1.color[0] = 1.0;
	v1.color[1] = 1.0;
	v1.color[2] = 1.0;
	v1.color[3] = 1.0;

	v2.xyz[0] = 0.5;
	v2.xyz[1] = 3.0;
	v2.xyz[2] = 0.5;
	v2.color[0] = 1.0;
	v2.color[1] = 0;
	v2.color[2] = 1.0;
	v2.color[3] = 1.0;

	v3.xyz[0] = 1.0;
	v3.xyz[1] = 0.0;
	v3.xyz[2] = 0.0;
	v3.color[0] = 1.0;
	v3.color[1] = 0;
	v3.color[2] = 0;
	v3.color[3] = 1.0;

	v4.xyz[0] = 1.0;
	v4.xyz[1] = 0.0;
	v4.xyz[2] = 1.0;
	v4.color[0] = 0;
	v4.color[1] = 0;
	v4.color[2] = 1.0;
	v4.color[3] = 1.0;

	v5.xyz[0] = 0.0;
	v5.xyz[1] = 0.0;
	v5.xyz[2] = 1.0;
	v5.color[0] = 1.0;
	v5.color[1] = 1.0;
	v5.color[2] = 1.0;
	v5.color[3] = 1.0;

	model->numVerts = 5;
	model->verts = new vert[model->numVerts];
	model->verts[0] = v1;
	model->verts[1] = v2;
	model->verts[2] = v3;
	model->verts[3] = v4;
	model->verts[4] = v5;

	model->numIndices = 12;
	model->indices = new int[model->numIndices];
	model->indices[0] = 0;
	model->indices[1] = 1;
	model->indices[2] = 2;
	model->indices[3] = 2;
	model->indices[4] = 1;
	model->indices[5] = 3;
	model->indices[6] = 3;
	model->indices[7] = 1;
	model->indices[8] = 4;
	model->indices[9] = 4;
	model->indices[10] = 1;
	model->indices[11] = 0;

	// Set world info
	origin[0] = 2.0f;
	origin[1] = 0.0f;
	origin[2] = 0.0f;

	direction = glm::mat4();
	direction = glm::rotate(direction, float(45.0), glm::vec3(0, 1, 0));
}
