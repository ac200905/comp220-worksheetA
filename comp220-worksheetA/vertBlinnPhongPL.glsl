#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColour;
layout(location = 2) in vec2 vertexTextureCoord;
layout(location = 3) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 cameraPosition;

out vec4 vertexColourOut;        
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalOut;
out vec3 viewDirection;
out vec3 worldVertexPosition;

void main(){
	
	mat4 mvpMatrix=projectionMatrix*viewMatrix*modelMatrix;

	vec4 worldPosition=modelMatrix*vec4(vertexPosition,1.0f);
	vec4 mvpPosition=mvpMatrix*vec4(vertexPosition,1.0f);
	
	vertexColourOut=vertexColour;
	vertexTextureCoordOut=vertexTextureCoord;
	vertexNormalOut=normalize(modelMatrix*vec4(vertexNormal,0.0f)).xyz;
	viewDirection=normalize(cameraPosition-worldPosition.xyz);
	worldVertexPosition=worldPosition.xyz;

	gl_Position=mvpPosition;
}