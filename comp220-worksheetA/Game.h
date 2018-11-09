#pragma once
#include "SDL.h"
#include "main.h"

class Game
{
public:
	Game();
	~Game();

	void gameInit();

	void gameLoop();

	void gameClean();

	bool running = true;




private:



};