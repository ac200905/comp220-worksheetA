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