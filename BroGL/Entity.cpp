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

	v2.xyz[0] = 2.5;
	v2.xyz[1] = 5.0;
	v2.xyz[2] = 2.5;
	v2.color[0] = 1.0;
	v2.color[1] = 0;
	v2.color[2] = 1.0;
	v2.color[3] = 1.0;

	v3.xyz[0] = 5.0;
	v3.xyz[1] = 0.0;
	v3.xyz[2] = 0.0;
	v3.color[0] = 1.0;
	v3.color[1] = 0;
	v3.color[2] = 0;
	v3.color[3] = 1.0;

	v4.xyz[0] = 5.0;
	v4.xyz[1] = 0.0;
	v4.xyz[2] = 5.0;
	v4.color[0] = 0;
	v4.color[1] = 0;
	v4.color[2] = 1.0;
	v4.color[3] = 1.0;

	v5.xyz[0] = 0.0;
	v5.xyz[1] = 0.0;
	v5.xyz[2] = 5.0;
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

	model->numIndices = 18;
	model->indices = new int[model->numIndices];
	model->indices[0] = 0;
	model->indices[1] = 2;
	model->indices[2] = 1;
	model->indices[3] = 2;
	model->indices[4] = 3;
	model->indices[5] = 1;
	model->indices[6] = 3;
	model->indices[7] = 4;
	model->indices[8] = 1;
	model->indices[9] = 4;
	model->indices[10] = 0;
	model->indices[11] = 1;
	model->indices[12] = 0;
	model->indices[13] = 2;
	model->indices[14] = 3;
	model->indices[15] = 3;
	model->indices[16] = 4;
	model->indices[17] = 0;

	// Set world info
	origin[0] = 0.0f;
	origin[1] = 0.0f;
	origin[2] = 0.0f;

	direction = glm::mat4();
	//direction = glm::rotate(direction, float(15.0), glm::vec3(0, 1, 0));
	//direction = glm::rotate(direction, float(45.0), glm::vec3(1, 0, 0));
}

void Entity::GenerateSquareEntity() {
	vert v1, v2, v3, v4, v5, v6, v7, v8;

	v1.xyz[0] = 0.0;
	v1.xyz[1] = 0.0;
	v1.xyz[2] = 0.0;
	v1.color[0] = 1.0;
	v1.color[1] = 1.0;
	v1.color[2] = 1.0;
	v1.color[3] = 1.0;

	v2.xyz[0] = 1.0;
	v2.xyz[1] = 0.0;
	v2.xyz[2] = 0.0;
	v2.color[0] = 1.0;
	v2.color[1] = 0;
	v2.color[2] = 1.0;
	v2.color[3] = 1.0;

	v3.xyz[0] = 0.0;
	v3.xyz[1] = 1.0;
	v3.xyz[2] = 0.0;
	v3.color[0] = 1.0;
	v3.color[1] = 0;
	v3.color[2] = 0;
	v3.color[3] = 1.0;

	v4.xyz[0] = 1.0;
	v4.xyz[1] = 1.0;
	v4.xyz[2] = 0.0;
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

	v6.xyz[0] = 1.0;
	v6.xyz[1] = 0.0;
	v6.xyz[2] = 1.0;
	v6.color[0] = 1.0;
	v6.color[1] = 0.0;
	v6.color[2] = 1.0;
	v6.color[3] = 1.0;

	v7.xyz[0] = 0.0;
	v7.xyz[1] = 1.0;
	v7.xyz[2] = 1.0;
	v7.color[0] = 0.0;
	v7.color[1] = 0.0;
	v7.color[2] = 1.0;
	v7.color[3] = 1.0;

	v8.xyz[0] = 1.0;
	v8.xyz[1] = 1.0;
	v8.xyz[2] = 1.0;
	v8.color[0] = 0.0;
	v8.color[1] = 0.0;
	v8.color[2] = 1.0;
	v8.color[3] = 1.0;

	model->numVerts = 8;
	model->verts = new vert[model->numVerts];
	model->verts[0] = v1;
	model->verts[1] = v2;
	model->verts[2] = v3;
	model->verts[3] = v4;
	model->verts[4] = v5;
	model->verts[5] = v6;
	model->verts[6] = v7;
	model->verts[7] = v8;

	model->numIndices = 36;
	model->indices = new int[model->numIndices];
	model->indices[0] = 0;
	model->indices[1] = 1;
	model->indices[2] = 3;
	model->indices[3] = 0;
	model->indices[4] = 3;
	model->indices[5] = 2;
	model->indices[6] = 1;
	model->indices[7] = 5;
	model->indices[8] = 7;
	model->indices[9] = 1;
	model->indices[10] = 7;
	model->indices[11] = 3;
	model->indices[12] = 5;
	model->indices[13] = 4;
	model->indices[14] = 6;
	model->indices[15] = 5;
	model->indices[16] = 6;
	model->indices[17] = 7;
	model->indices[18] = 4;
	model->indices[19] = 0;
	model->indices[20] = 2;
	model->indices[21] = 4;
	model->indices[22] = 2;
	model->indices[23] = 6;
	model->indices[24] = 4;
	model->indices[25] = 5;
	model->indices[26] = 1;
	model->indices[27] = 4;
	model->indices[28] = 1;
	model->indices[29] = 0;
	model->indices[30] = 2;
	model->indices[31] = 3;
	model->indices[32] = 7;
	model->indices[33] = 2;
	model->indices[34] = 7;
	model->indices[35] = 6;

	// Set world info
	origin[0] = 0.0f;
	origin[1] = 0.0f;
	origin[2] = 0.0f;

	direction = glm::mat4();
}
