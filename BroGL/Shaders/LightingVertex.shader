#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;
out vec4 ex_Color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

mat4 temp;

void main(void) {

  // temp light direction
  vec3 cameraPos = vec3(0.5, 0.0, 5.0);
  vec3 lightPos = vec3(0.0, 0.0, 10.0);
  vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
  vec3 n, lightDir;
  vec4 diffuse;
  float cosTheta;
	
	// Set position
	temp = projectionMatrix * viewMatrix * modelMatrix;
	gl_Position = temp * in_Position;

  // Lighting and camera position, direction
  vec3 vertexPosCamera = vec3(viewMatrix * modelMatrix * in_Position);
  vec3 eyeDirCamera = vec3(0,0,0) - vertexPosCamera;
  vec3 lightPosCamera = vec3(viewMatrix * vec4(lightPos, 1.0));
  lightDir = lightPosCamera + eyeDirCamera;

  // Calculate lighting
  n = vec3(viewMatrix * modelMatrix * vec4(in_Normal, 0.0));
  cosTheta = clamp(dot(n, lightDir), 0, 1);

  diffuse = in_Color * lightColor;

  // Set coloring
	ex_Color = cosTheta * diffuse;
}
