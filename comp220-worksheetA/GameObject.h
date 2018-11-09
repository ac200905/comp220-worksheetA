#pragma once
#include "main.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	MeshCollection * newModel;

	void update();

	void render();

	// Give the GameObject a loaded mesh
	void giveMesh(MeshCollection *mesh)
	{
		newModel = mesh;
	};

	mat4 translationMatrix;
	mat4 rotationMatrix;
	mat4 scaleMatrix;

	mat4 modelMatrix;

	// Set up the models position, rotation and scale
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
	vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 scale = vec3(1.0f, 1.0f, 1.0f);
};
