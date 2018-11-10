#pragma once
#include <SDL.h>
#include <map>
#include <iostream>

#include "main.h"


class InputSetup
{
public:
	InputSetup();

	~InputSetup();

	// Populate map with keyboard events
	void keyboardEvents(SDL_Event event)
	{
		keyStates[event.key.keysym.sym] = event.key.state;
	}

	// Handle mouse input (change camera yaw/pitch)
	void mouseInput(float xPos, float yPos);

	void joystickInit();

	SDL_Joystick* joystickController;

	void joystickInput(int which, int axis, int value);

	void controllerInput(int which, int axis, float value);

	// Clear map of events
	void clearEvents()
	{
		keyStates.clear();
	}

	// Check if key is released
	bool isReleased(SDL_Keycode key)
	{
		return keyStates[key] == SDL_RELEASED;
	}

	// Check if key is pressed
	bool isPressed(SDL_Keycode key)
	{
		return keyStates[key] == SDL_PRESSED;
	}
	
	float getYOffset()
	{
		return yOffset;
	}

	float getXOffset()
	{
		return xOffset;
	}

private:
	//Map containing the key and its state
	std::map<SDL_Keycode, Uint8> keyStates;

	Camera camera;

	float mouseSpeed;

	//The mouse offsets
	float xOffset;
	float yOffset;
};
