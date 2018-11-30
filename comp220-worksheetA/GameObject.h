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

	MeshCollection * newMesh;

	mat4 translationMatrix;
	mat4 rotationMatrix;
	mat4 scaleMatrix;

	mat4 modelMatrix;

	// Set up the models position, rotation and scale
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 scale = vec3(1.0f, 1.0f, 1.0f);

	void update();

	void render();

	// Give the GameObject a loaded mesh
	void giveMesh(MeshCollection *mesh)
	{
		newMesh = mesh;
	};

	void setPosition(float x, float y, float z)
	{
		position = vec3(x, y, z);
	};

	void setRotation(float x, float y, float z)
	{
		rotation = vec3(x, y, z);
	};

	void setScale(float x, float y, float z)
	{
		scale = vec3(x, y, z);
	};

	vec3 getPosition()
	{
		return position;
	}

	vec3 getRotation()
	{
		return rotation;
	}

	vec3 getScale()
	{
		return scale;
	}
};
