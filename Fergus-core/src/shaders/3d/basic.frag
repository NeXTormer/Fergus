#version 330 core

in vec3 color;
in vec2 uvCoords;

out vec4 out_Color;

uniform sampler2D sampler;

void main(void)
{
	out_Color = texture(sampler, uvCoords);
}