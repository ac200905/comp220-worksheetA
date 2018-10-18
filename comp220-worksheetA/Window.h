#pragma once
#include "main.h"


class Window
{

public:

	Window(const char* title);

	~Window();

	int initSDL();

	// If the window is currently fullscreen
	bool isFullscreen;

	// Get isFullscreen value
	bool getIsFullscreen();

	// Set isFullscreen value
	void setIsFullscreen();

	SDL_Window* getWindow()
	{
		return window;
	};


private:
	SDL_Window * window;

};