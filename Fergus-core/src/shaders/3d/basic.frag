#version 330 core

in vec2 uvCoords;
in vec3 surfaceNormal;
in vec3 vectorToLight;
in vec3 vectorToCamera;

out vec4 out_Color;

uniform sampler2D sampler;

uniform vec3 lightColor;

uniform float shineDamper;
uniform float reflectivity;

void main(void)
{
	
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitToLight = normalize(vectorToLight);
	vec3 unitToCamera = normalize(vectorToCamera);

	vec3 lightDirection = -unitToLight;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float dotProductNormalLight = dot(unitNormal, unitToLight);
	float specularFactor = dot(reflectedLightDirection, unitToCamera);

	specularFactor = max(specularFactor, 0.0);
	float brightness = max(dotProductNormalLight, 0.15);
	float dampedFactor = pow(specularFactor, shineDamper);

	vec3 specularColor = dampedFactor * reflectivity * lightColor;
	vec3 diffuseColor = brightness * lightColor;

	out_Color = vec4(diffuseColor, 1.0) * texture(sampler, uvCoords) + vec4(specularColor, 1.0);
}