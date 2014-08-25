#include "Entity.h"


Entity::Entity() {
}


Entity::~Entity() {
	delete[] polys;
}

void Entity::GenerateTestEntity() {
	vert v1, v2, v3, v4, v5;

	v1.xyz[0] = 0.0;
	v1.xyz[1] = 0.0;
	v1.xyz[2] = 0.0;
	
	v2.xyz[0] = 0.5;
	v2.xyz[1] = 1.0;
	v2.xyz[2] = 0.5;
	
	v3.xyz[0] = 1.0;
	v3.xyz[1] = 0.0;
	v3.xyz[2] = 0.0;
	
	v4.xyz[0] = 1.0;
	v4.xyz[1] = 0.0;
	v4.xyz[2] = 1.0;
	
	v5.xyz[0] = 0.0;
	v5.xyz[1] = 0.0;
	v5.xyz[2] = 1.0;

	poly p1, p2, p3, p4;

	p1.numVerts = 3;
	p1.verts = new vert[p1.numVerts];
	p1.verts[0] = v1;
	p1.verts[1] = v2;
	p1.verts[2] = v3;

	p2.numVerts = 3;
	p2.verts = new vert[p2.numVerts];
	p2.verts[0] = v3;
	p2.verts[1] = v2;
	p2.verts[2] = v4;

	p3.numVerts = 3;
	p3.verts = new vert[p3.numVerts];
	p3.verts[0] = v4;
	p3.verts[1] = v2;
	p3.verts[2] = v5;

	p4.numVerts = 3;
	p4.verts = new vert[p4.numVerts];
	p4.verts[0] = v5;
	p4.verts[1] = v2;
	p4.verts[2] = v1;

	polys = new poly[4];
	polys[0] = p1;
	polys[1] = p2;
	polys[2] = p3;
	polys[3] = p4;

	// Set world info
	origin[0] = 0.0;
	origin[1] = 0.0;
	origin[2] = 0.0;

	direction[0][0] = 0.0;
	direction[0][1] = 0.0;
	direction[0][2] = 0.0;

	direction[1][0] = 0.0;
	direction[1][1] = 0.0;
	direction[1][2] = 0.0;

	direction[2][0] = 0.0;
	direction[2][1] = 0.0;
	direction[2][2] = 0.0;
}
