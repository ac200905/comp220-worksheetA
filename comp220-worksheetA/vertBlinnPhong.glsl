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



out vec4 vertexColourFinal;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalOut;

void main()
{
	mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vertexColourFinal = vertexColour;

	vertexTextureCoordOut = vertexTextureCoord;

	vertexNormalOut = vertexNormal;

	gl_Position = MVPMatrix * vec4(vertexPos, 1.0f);
}