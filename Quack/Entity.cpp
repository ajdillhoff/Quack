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
}

void Entity::GenerateSquareEntity() {
	vert v1, v2, v3, v4, v5, v6, v7, v8;

	glm::vec3 x =		 glm::vec3(1, 0, 0);
	glm::vec3 xNeg = glm::vec3(-1, 0, 0);
	glm::vec3 y =		 glm::vec3(0, 1, 0);
	glm::vec3 yNeg = glm::vec3(0, -1, 0);
	glm::vec3 z =		 glm::vec3(0, 0, 1);
	glm::vec3 zNeg = glm::vec3(0, 0, -1);

	v1.xyz[0] = 0.0;
	v1.xyz[1] = 0.0;
	v1.xyz[2] = 0.0;
	v1.color[0] = 1.0;
	v1.color[1] = 1.0;
	v1.color[2] = 1.0;
	v1.color[3] = 1.0;
	v1.normal = glm::normalize(zNeg + xNeg + yNeg);

	v2.xyz[0] = 1.0;
	v2.xyz[1] = 0.0;
	v2.xyz[2] = 0.0;
	v2.color[0] = 1.0;
	v2.color[1] = 0;
	v2.color[2] = 1.0;
	v2.color[3] = 1.0;
	v2.normal = glm::normalize(zNeg + x + yNeg);

	v3.xyz[0] = 0.0;
	v3.xyz[1] = 1.0;
	v3.xyz[2] = 0.0;
	v3.color[0] = 1.0;
	v3.color[1] = 0;
	v3.color[2] = 0;
	v3.color[3] = 1.0;
	v3.normal = glm::normalize(zNeg + xNeg + y);

	v4.xyz[0] = 1.0;
	v4.xyz[1] = 1.0;
	v4.xyz[2] = 0.0;
	v4.color[0] = 0;
	v4.color[1] = 0;
	v4.color[2] = 1.0;
	v4.color[3] = 1.0;
	v4.normal = glm::normalize(zNeg + x + y);

	v5.xyz[0] = 0.0;
	v5.xyz[1] = 0.0;
	v5.xyz[2] = 1.0;
	v5.color[0] = 1.0;
	v5.color[1] = 1.0;
	v5.color[2] = 1.0;
	v5.color[3] = 1.0;
	v5.normal = glm::normalize(z + xNeg + yNeg);

	v6.xyz[0] = 1.0;
	v6.xyz[1] = 0.0;
	v6.xyz[2] = 1.0;
	v6.color[0] = 1.0;
	v6.color[1] = 0.0;
	v6.color[2] = 1.0;
	v6.color[3] = 1.0;
	v6.normal = glm::normalize(z + x + yNeg);

	v7.xyz[0] = 0.0;
	v7.xyz[1] = 1.0;
	v7.xyz[2] = 1.0;
	v7.color[0] = 0.0;
	v7.color[1] = 0.0;
	v7.color[2] = 1.0;
	v7.color[3] = 1.0;
	v7.normal = glm::normalize(z + xNeg + y);

	v8.xyz[0] = 1.0;
	v8.xyz[1] = 1.0;
	v8.xyz[2] = 1.0;
	v8.color[0] = 0.0;
	v8.color[1] = 0.0;
	v8.color[2] = 1.0;
	v8.color[3] = 1.0;
	v8.normal = glm::normalize(z + x + y);

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

	// Front
	model->indices[0] = 0;
	model->indices[1] = 3;
	model->indices[2] = 1;
	model->indices[3] = 0;
	model->indices[4] = 2;
	model->indices[5] = 3;

	// Right
	model->indices[6] = 1;
	model->indices[7] = 5;
	model->indices[8] = 7;
	model->indices[9] = 1;
	model->indices[10] = 7;
	model->indices[11] = 3;

	// Rear
	model->indices[12] = 5;
	model->indices[13] = 4;
	model->indices[14] = 6;
	model->indices[15] = 5;
	model->indices[16] = 6;
	model->indices[17] = 7;

	// Left
	model->indices[18] = 4;
	model->indices[19] = 0;
	model->indices[20] = 2;
	model->indices[21] = 4;
	model->indices[22] = 2;
	model->indices[23] = 6;

	// Top
	model->indices[24] = 4;
	model->indices[25] = 5;
	model->indices[26] = 1;
	model->indices[27] = 4;
	model->indices[28] = 1;
	model->indices[29] = 0;

	// Bottom
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
	center = glm::vec3(0.5, 0.5, 0.5);
	//Rotate(-90, glm::vec3(0.0, 1.0, 0.0));
}

//************************************
// Method:    LoadTexture
// FullName:  Entity::LoadTexture
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: char * imagePath
//************************************
int Entity::LoadTexture(char * imagePath) {
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	ifstream file;

	file.open(imagePath, ios::in);
	if (!file) {
		return 0; // can't open
	}

	if (fread(header, 1, 54, file) != 54) {
		return 0; // not a correct bmp file
	}

	if (header[0] != 'B' || header[1] != 'M') {
		return 0; // not a correct bmp file
	}

	// read ints from byte array
	dataPos   = *(int *)&(header[0x0A]);
	imageSize = *(int *)&(header[0x22]);
	width     = *(int *)&(header[0x12]);
	height    = *(int *)&(header[0x16]);

	if (imageSize == 0) {
		imageSize = width * height * 3;
	}

	if (dataPos == 0) {
		dataPos = 54;
	}

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	// create the texture
	GLuint textureID;
	glGenTextures(1, &textureID);

}

//************************************
// Method:    Rotate
// FullName:  Entity::Rotate
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: float degrees
// Parameter: glm::vec3 rotationAxis
//************************************
void Entity::Rotate(float degrees, glm::vec3 rotationAxis) {
	glm::vec3 offset = origin - center;
	direction = glm::translate(direction, -offset);
	direction = glm::rotate(direction, float(degrees), rotationAxis);
	direction = glm::translate(direction, offset);
}
