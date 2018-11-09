#version 330 core

out vec4 colour;
in vec4 vertexColourFinal;
in vec2 vertexTextureCoordOut;

uniform vec4 triangleColour; 
uniform sampler2D baseTexture;
uniform sampler2D baseTexture2;

void main()
{
  //colour = triangleColour;
  //colour = vertexColourFinal;
  colour = texture2D(baseTexture, vertexTextureCoordOut);
}