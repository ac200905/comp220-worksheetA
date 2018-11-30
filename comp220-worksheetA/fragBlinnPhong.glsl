#version 330 core

out vec4 colour;
in vec4 vertexColourFinal;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalOut;


uniform sampler2D baseTexture;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;

uniform vec3 lightDirection;

void main()
{
	//The shininess of the surface
	float diffuseReflectance = dot(vertexNormalOut, -lightDirection);

	colour = (ambientLightColour * ambientMaterialColour) + (diffuseLightColour * diffuseReflectance * diffuseMaterialColour);
}