#include "Timer.h"

Timer::Timer()
{
	deltaTime = 0.0f;
	currentTime = 0;
	frequency = 0;
	lastTime = 0;
	updatedTime = 0;
}

Timer::~Timer()
{

}

void Timer::Start()
{
	//Get the current value from high pref counter
	currentTime = SDL_GetPerformanceCounter();
	//Set the last time equal to the current time
	lastTime = currentTime;
	//Get the frequency of the high pref counter
	frequency = SDL_GetPerformanceFrequency();
}

void Timer::Update()
{
	//Get current value from high pref counter
	currentTime = SDL_GetPerformanceCounter();
	//Calculate Delta time
	deltaTime = (float)(currentTime - lastTime) / (float)frequency;
	//Set the last time equal to the current time
	lastTime = currentTime;
	updatedTime += deltaTime;

}