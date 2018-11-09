#version 330 core

// Look at GL Attribute Pointer in main.cpp
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoord;

out vec3 vertColor;

//uniform vec3 myVariable;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//uniform mat4 MVPMatrix;

out vec4 vertexColourFinal;
out vec2 vertexTextureCoordOut;

void main()
{
	mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vertexColourFinal = vertexColour;

	vertexTextureCoordOut = vertexTextureCoord;

	gl_Position = MVPMatrix * vec4(vertexPos, 1.0f);
}