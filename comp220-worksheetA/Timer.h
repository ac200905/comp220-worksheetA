#pragma once

#include <SDL.h>

//Basic Timer Class
class Timer
{
public:
	Timer();
	~Timer();

	//Start Timer, this will get the initial time, get the update frequency and setup last time
	void Start();
	//Update the current timer, this will calculate the delta time since last update
	void Update();

	//Get the Delta time
	float GetDeltaTime()
	{
		return deltaTime;
	};

	//Get the Current time
	Uint64 GetCurrentTime()
	{
		return currentTime;
	};

	float GetUpdatedTime()
	{
		return updatedTime;
	};

private:
	Uint64 lastTime;
	Uint64 currentTime;
	Uint64 frequency;
	float deltaTime;
	float updatedTime;
};