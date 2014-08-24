#pragma once
class Camera {
public:
	Camera();
	virtual ~Camera();

	int x, y;  // Location
	int width, height; // View parameters
	float fov_x, fov_y;
	float[3] viewOrigin;
	float[3] viewMatrix[3];
};

