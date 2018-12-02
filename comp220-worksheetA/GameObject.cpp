#include "GameObject.h"



GameObject::GameObject()
{
	position = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	rotation = glm::vec3(0.0f);

	translationMatrix = glm::mat4(0.0f);
	rotationMatrix = glm::mat4(0.0f);
	scaleMatrix = glm::mat4(0.0f);
	modelMatrix = glm::mat4(0.0f);

	Meshes = nullptr;
	ShaderProgram = nullptr;
	DiffuseTexture = 0;
}


GameObject::~GameObject()
{
	glDeleteTextures(1, &DiffuseTexture);

	if (Meshes) {
		delete Meshes;
	}
	if (ShaderProgram)
	{
		delete ShaderProgram;
	}
}

void GameObject::update(float deltaTime)
{
	// Calculate Matricies for new object
	translationMatrix = translate(position);


	rotationMatrix = rotate(rotation.x, vec3(1.0f, 0.0f, 0.0f)) *
		rotate(rotation.y, vec3(0.0f, 1.0f, 0.0f)) *
		rotate(rotation.z, vec3(0.0f, 0.0f, 1.0f));

	scaleMatrix = glm::scale(scale);

	// Create the modelMatrix for the object
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;


}

void GameObject::render()
{
	// Render the object
	if (Meshes)
	{
		Meshes->render();
	}
}