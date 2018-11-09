#pragma once
#include "main.h"
#include <iostream>

using namespace glm;

class PlayerController
{
public:
	PlayerController();
	PlayerController(InputSetup * Input, Camera * Camera);

	~PlayerController();

	// Manage keyboard inputs
	void keyboardControls(float deltaTime);

	// Manage mouse inputs
	void mouseControls();

private:
	InputSetup *input;

	Camera *playerCamera; 

	vec3 cameraPosition;
	vec3 cameraTarget;

	//How fast the player can move
	float moveSpeed;
};
