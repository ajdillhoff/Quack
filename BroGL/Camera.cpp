#include "Camera.h"


Camera::Camera() {
	// Defaults
	x = 0;
	y = 0;

	width = 1680;
	height = 1050;

	fov_x = 90.0f;
	fov_y = 60.0f;

	viewOrigin[0] = 0.5;
	viewOrigin[1] = 0.0;
	viewOrigin[2] = 10.0;

	viewMatrix = glm::mat4();

}

Camera::~Camera() {
}
