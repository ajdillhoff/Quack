#include "Camera.h"


Camera::Camera() {
	// Defaults
	x = 0;
	y = 0;

	width = 800;
	height = 600;

	fov_x = 90.0f;
	fov_y = 90.0f;

	viewOrigin[0] = 0.0;
	viewOrigin[1] = 0.0;
	viewOrigin[2] = 0.0;

	viewMatrix[0][0] = 1.0;
	viewMatrix[0][1] = 0.0;
	viewMatrix[0][2] = 0.0;

	viewMatrix[1][0] = 0.0;
	viewMatrix[1][1] = 1.0;
	viewMatrix[1][2] = 0.0;

	viewMatrix[2][0] = 0.0;
	viewMatrix[2][1] = 0.0;
	viewMatrix[2][2] = 1.0;

	//vec3 angles = { 0, 0, 0 };

	//AngleVectors(angles, viewMatrix[0], viewMatrix[1], viewMatrix[2]);
}


Camera::~Camera() {
}
