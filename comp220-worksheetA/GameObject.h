#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Texture.h"
#include "Model.h"
#include "Mesh.h"
#include "shaders.h"

using namespace glm;

class GameObject
{
public:
	GameObject();
	~GameObject();

	

	void update(float deltaTime);

	void render();

	void SetPosition(float x, float y, float z)
	{
		position = glm::vec3(x, y, z);
	};

	void SetScale(float x)
	{
		scale = glm::vec3(x, x, x);
	};

	glm::vec3& GetPosition()
	{
		return position;
	};

	glm::mat4& GetModelTransformation()
	{
		return modelMatrix;
	};

	// Give the GameObject a loaded mesh
	void SetMesh(MeshCollection * meshes)
	{
		Meshes = meshes;
	};

	void SetShader(Shader * shader)
	{
		ShaderProgram = shader;
	};

	Shader * GetShader()
	{
		return ShaderProgram;
	};

	void SetDiffuseTexture(GLuint texture)
	{
		DiffuseTexture = texture;
	};

	GLuint GetDiffuseTexture()
	{
		return DiffuseTexture;
	};

private:

	// Mesh
	MeshCollection * Meshes;

	// Shader
	Shader * ShaderProgram;

	// Texture
	GLuint DiffuseTexture;

	mat4 translationMatrix;
	mat4 rotationMatrix;
	mat4 scaleMatrix;

	mat4 modelMatrix;

	// Set up the models position, rotation and scale
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 scale = vec3(1.0f, 1.0f, 1.0f);
};
