#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvCoords_in;

out vec3 color;
out vec2 uvCoords;

uniform mat4 ml_matrix;
uniform mat4 pr_matrix;

void main(void)
{
	gl_Position = pr_matrix * ml_matrix * vec4(position, 1.0);

	uvCoords = uvCoords_in;
}