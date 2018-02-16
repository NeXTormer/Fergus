#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvCoords_in;
layout (location = 2) in vec3 normal_in;

out vec2 uvCoords;
out vec3 surfaceNormal;
out vec3 vectorToLight;
out vec3 vectorToCamera;

uniform mat4 ml_matrix = mat4(1.0);
uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);

uniform vec3 lightPosition;

void main(void)
{
	vec4 worldPosition = ml_matrix * vec4(position, 1.0);
	gl_Position = pr_matrix * vw_matrix * worldPosition;;

	uvCoords = uvCoords_in;
	surfaceNormal = (ml_matrix * vec4(normal_in, 1.0)).xyz;
	vectorToLight = lightPosition - worldPosition.xyz;

	vectorToCamera = (inverse(vw_matrix) * vec4(0.0, 0.0, 0.0, 0.0)).xyz - worldPosition.xyz;
}