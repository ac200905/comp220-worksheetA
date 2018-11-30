#include "InputSetup.h"


InputSetup::InputSetup()
{
	mouseSpeed = 0.1f;
}


InputSetup::~InputSetup()
{
}

void InputSetup::mouseInput(float xPos, float yPos)
{
	//Store mouse position
	xOffset = xPos * mouseSpeed;
	yOffset = yPos * mouseSpeed;
}

void InputSetup::joystickInit()
{
	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Warning:\n", "No joysticks connected!\n", NULL);
	}
	else
	{
		//Load joystick
		joystickController = SDL_JoystickOpen(0);
		if (joystickController == NULL)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}

		
	}
}

void InputSetup::joystickInput(int which, int axis, int value)
{

		
}

void InputSetup::controllerInput(int which, int axis, float value)
{
	
	
}