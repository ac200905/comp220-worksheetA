#include "main.h"


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
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Warning: No joysticks connected!\n", SDL_GetError(), NULL);
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
	if (which == 0)
	{
		if (axis == 0)
		{
			if ( value < -3200)
			{
				//xOffset = -2;
			}
			else if (value > 3200)
			{
				//xOffset = 2;
			}
			else
			{
				//xOffset = 0;
			}
		}
		if (axis == 1)
		{
			if (value < -3200)
			{
				//yOffset = -2;
			}
			else if (value > 3200)
			{
				//yOffset = 2;
			}
			else
			{
				//yOffset = 0;
			}
		}
	}
		
}

void InputSetup::controllerInput(int which, int axis, float value)
{
	if (which = 0)
	{
		if (axis == 0)
		{
			if (value < -3200)
			{
				//xOffset = -1 * mouseSpeed;
			}
			else if (value > 3200)
			{
				//xOffset = 1 * mouseSpeed;
			}
		}
	}
	if (SDL_CONTROLLER_AXIS_LEFTX)
	{
		//xOffset = -1 * mouseSpeed;
	}
}