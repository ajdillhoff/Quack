typedef float[3] vec3;
typedef unsigned char byte;

typedef struct {
	vec3 xyz;
	vec3 normal;
	byte color[4];
} vert;

typedef struct {
	int numVerts;
	vert *verts;
} poly;