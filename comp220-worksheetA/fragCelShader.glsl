#version 330 core

out vec4 colour;
in vec4 vertexColourFinal;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalOut;
in vec3 viewDirection;


uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;

uniform float specularMaterialPower;

uniform vec3 lightDirection;

const float levels = 4.0;

void main()
{
	//The shininess of the surface
	float diffuseIntensity = dot(vertexNormalOut, -lightDirection);

	float brightness = max(diffuseIntensity, 0.0);
	float level = floor(brightness * levels);
	brightness = level / levels;

	vec3 maxReflectionVector = normalize(-lightDirection + viewDirection);
	float specularIntensity = pow(dot(vertexNormalOut, maxReflectionVector), specularMaterialPower);

	vec4 diffuseTextureColour = texture(diffuseTexture, vertexTextureCoordOut);
	vec4 specularTextureColour = texture(specularTexture, vertexTextureCoordOut);

	colour = (ambientLightColour * ambientMaterialColour * brightness) + 
			(diffuseLightColour * diffuseIntensity * diffuseMaterialColour * diffuseTextureColour * brightness) + 
			(specularLightColour * specularIntensity * specularMaterialColour * specularTextureColour);

	
	
	
}