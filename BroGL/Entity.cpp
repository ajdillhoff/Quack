#include "Entity.h"


Entity::Entity() {
}


Entity::~Entity() {
	delete[] polys;
}

void Entity::TestEntity() {
	vert v1, v2, v3, v4, v5;

	v1.xyz = { 0.0, 0.0, 0.0 };
	v2.xyz = { 0.5, 1.0, 0.5 };
	v3.xyz = { 1.0, 0.0, 0.0 };
	v4.xyz = { 1.0, 0.0, 1.0 };
	v5.xyz = { 0.0, 0.0, 1.0 };

	poly p1, p2, p3, p4;

	p1.numVerts = 3;
	p1.verts = { v1, v2, v3 };

	p2.numVerts = 3;
	p2.verts = { v3, v2, v4 };

	p3.numVerts = 3;
	p3.verts = { v4, v2, v5 };

	p3.numVerts = 3;
	p3.verts = { v5, v2, v1 };

	polys = new poly[4];
	polys[0] = p1;
	polys[1] = p2;
	polys[2] = p3;
	polys[3] = p4;

}
