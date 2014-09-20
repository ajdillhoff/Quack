#include <iostream>
#include "BroInput.h"

Input::Input() {
}

Input::Input(Camera* nc) {
	camera = nc;
}

//************************************
// Method:    HandleKeyPress
// FullName:  Input::handleKeyPress
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char key
//************************************
void Input::HandleKeyPress(char key) {
	glm::mat4 translateMatrix;
	glm::mat4 transformMatrix;
	glm::vec4 forwardDirection = glm::vec4(0.0, 0.0, 0.2, 1.0);
	glm::vec4 translatedDirection = glm::vec4();

	switch (key) {
	case 'W':
		// translate forward
		translateMatrix = glm::mat4();
		translateMatrix[0][3] = -camera->viewOrigin[0];
		translateMatrix[1][3] = -camera->viewOrigin[1];
		translateMatrix[2][3] = -camera->viewOrigin[2];
		transformMatrix = camera->viewMatrix * translateMatrix;
		translatedDirection = transformMatrix * forwardDirection;
		camera->viewOrigin[0] += translatedDirection[0];
		camera->viewOrigin[2] -= translatedDirection[2];
		break;
	case 'A':
		// rotate counter clockwise about the Y axis
		camera->viewMatrix = glm::rotate(camera->viewMatrix, float(-1.0), glm::vec3(0, 1, 0));
		break;
	case 'S':
		// translate backwards
		translateMatrix = glm::mat4();
		translateMatrix[0][3] = -camera->viewOrigin[0];
		translateMatrix[1][3] = -camera->viewOrigin[1];
		translateMatrix[2][3] = -camera->viewOrigin[2];
		transformMatrix = camera->viewMatrix * translateMatrix;
		translatedDirection = transformMatrix * forwardDirection;
		camera->viewOrigin[0] -= translatedDirection[0];
		camera->viewOrigin[2] += translatedDirection[2];
		break;
	case 'D':
		// rotate clockwise about the Y axis
		camera->viewMatrix = glm::rotate(camera->viewMatrix, float(1.0), glm::vec3(0, 1, 0));
		break;
	default:
		break;
	}
}
