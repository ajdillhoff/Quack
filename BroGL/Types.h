#pragma once

#define SHADER_MAX_VERTICES 1000
#define SHADER_MAX_INDICES (6*SHADER_MAX_VERTICES)
#define MAX_ENTITIES 100

// Copied from q_shared.h in Q3 engine
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))

typedef float vec3[3];
typedef float vec4[4];
typedef unsigned char byte;
typedef unsigned int glIndex_t;

typedef struct {
	vec3 xyz;
	vec3 normal;
	byte color[4];
} vert;

typedef struct {
	int numVerts;
	vert *verts;
} poly;

typedef struct {
	vec3 origin; // world coordinates
	vec3 axis[3]; // world orientation
	vec3 viewOrigin; // origin in local coordinates
	float modelMatrix[16];
} orientation_t;

typedef struct {
	orientation_t or;
	orientation_t world;
	int viewPortX, viewPortY, viewPortWidth, viewPortHeight;
	float fovX, fovY;
	float projectionMatrix[16];
} viewParms_t;

// TODO: Using this temporarily to try and make sense of the Q3 renderer
typedef struct {
	glIndex_t indexes[SHADER_MAX_INDICES];
	vec4 xyz[SHADER_MAX_VERTICES];
	
	int numIndices;
	int numVertices;
} shaderCommands_t;