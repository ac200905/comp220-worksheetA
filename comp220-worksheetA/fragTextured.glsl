#version 330 core

out vec4 colour;
in vec4 vertexColourFinal;
in vec2 vertexTextureCoordOut;


uniform sampler2D baseTexture;


void main()
{

  colour = texture2D(baseTexture, vertexTextureCoordOut);
}