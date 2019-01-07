#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::update()
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
	newMesh->render();
}

// Give particle a semi-random lifespan
void GameObject::resetLife()
{
	life = (rand() % (lifeMax - lifeMin)) + lifeMin;
}