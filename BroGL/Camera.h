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
	vec3 viewOrigin;
	vec3 viewMatrix[3];
};

