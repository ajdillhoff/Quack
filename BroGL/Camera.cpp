#include "Camera.h"


Camera::Camera() {
	// Defaults
	x = 0;
	y = 0;

	width = 800;
	height = 600;

	fov_x = 90.0f;
	fov_y = 90.0f;

	viewOrigin[0] = 0.5;
	viewOrigin[1] = 0.0;
	viewOrigin[2] = 3.0;

	viewMatrix = glm::mat4();

}


Camera::~Camera() {
}
