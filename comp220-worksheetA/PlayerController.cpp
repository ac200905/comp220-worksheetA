#include "main.h"

using namespace glm;


PlayerController::PlayerController()
{
}

PlayerController::PlayerController(InputSetup* Input, Camera* Camera)
{
	input = Input;
	playerCamera = Camera;

	cameraPosition = playerCamera->getPosition();
	cameraTarget = playerCamera->getTarget();

}


PlayerController::~PlayerController()
{
}

// Manage the keyboard inputs
void PlayerController::keyboardControls(float deltaTime)
{
	cameraPosition = playerCamera->getPosition();
	cameraTarget = playerCamera->getTarget();
	moveSpeed = 0.01f * deltaTime;

	// Check player inputs.
	// Move towards camera target
	if (input->isPressed(SDLK_w))
	{
		playerCamera->setPosition(cameraPosition + (moveSpeed * cameraTarget));
		playerCamera->setViewMatrix();
	}

	// Move directly backwards
	if (input->isPressed(SDLK_s))
	{
		playerCamera->setPosition(cameraPosition - (moveSpeed * cameraTarget));
		playerCamera->setViewMatrix();
	}

	// Move sideways left 
	if (input->isPressed(SDLK_a))
	{
		playerCamera->setPosition(cameraPosition - (normalize(cross(cameraTarget, playerCamera->getUpVector())) * moveSpeed));
		playerCamera->setViewMatrix();
	}

	// Move sideways right 
	if (input->isPressed(SDLK_d))
	{
		playerCamera->setPosition(cameraPosition + (normalize(cross(cameraTarget, playerCamera->getUpVector())) * moveSpeed));
		playerCamera->setViewMatrix();
	}

	// Move up
	if (input->isPressed(SDLK_SPACE))
	{
		playerCamera->setPosition(cameraPosition + (vec3(0,1,0) * moveSpeed));
		playerCamera->setViewMatrix();
	}

	// Move down
	if (input->isPressed(SDLK_LCTRL))
	{
		playerCamera->setPosition(cameraPosition + (vec3(0, -1, 0) * moveSpeed));
		playerCamera->setViewMatrix();
	}

}

// Manage the mouse inputs
void PlayerController::mouseControls()
{
	// Update camera yaw and pitch
	playerCamera->increaseYaw(input->getXOffset());
	playerCamera->increasePitch(input->getYOffset());

	// Constrain camera pitch
	playerCamera->checkPitchConstraints();

	// Calculate new camera rotation
	playerCamera->calculateCameraRotation();
}