#version 330 core

out vec4 colour;
in vec4 vertexColourFinal;

uniform vec4 triangleColour; 


void main()
{
  //colour = triangleColour;
  colour = vertexColourFinal;
}