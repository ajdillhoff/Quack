#include "BShared.h"
#include "Types.h"

#pragma once
class Camera {
public:
	Camera();
	virtual ~Camera();

	int x, y;  // Location
	int width, height; // View parameters
	float fov_x, fov_y;
	glm::vec3 viewOrigin;
	glm::mat4 viewMatrix;
};

