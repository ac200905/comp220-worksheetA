#version 330 core

// Look at GL Attribute Pointer in main.cpp
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoord;
layout(location = 3) in vec3 vertexNormal;

out vec3 vertColor;



uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;



out vec4 vertexColourFinal;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalOut;
out vec3 viewDirection;

void main()
{
	mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vec4 vertexWorldPos = modelMatrix * vec4(vertexPos, 1.0f);

	vertexColourFinal = vertexColour;

	vertexTextureCoordOut = vertexTextureCoord;

	vertexNormalOut = vertexNormal;

	viewDirection = normalize(cameraPosition - vertexWorldPos.xyz);

	gl_Position = MVPMatrix * vec4(vertexPos, 1.0f);
}