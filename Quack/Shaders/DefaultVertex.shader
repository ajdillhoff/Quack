#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

mat4 temp;

void main(void) {
	temp = projectionMatrix * modelViewMatrix;
	gl_Position = temp * in_Position;
	ex_Color = in_Color;
}
