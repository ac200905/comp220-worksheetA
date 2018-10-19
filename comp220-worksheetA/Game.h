#pragma once
#include "SDL.h"
#include "main.h"

class Game
{
public:
	Game();
	~Game();

	void handleEvents();

	void update();

	void render();

	void clean();

	bool running()
	{
		return isRunning;
	}


private:

	bool isRunning;

};