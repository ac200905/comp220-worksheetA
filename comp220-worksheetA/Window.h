#pragma once
#include <SDL.h>
#include <string>
#include <SDL_opengl.h>
#include "Globals.h"


class Window
{

public:

	Window(const char* title);
	Window();

	~Window();

	int initSDL();

	// If the window is currently fullscreen
	bool isFullscreen = false;

	// Get isFullscreen value
	bool getIsFullscreen();

	// Set isFullscreen value
	void setIsFullscreen();

	SDL_Window* getWindow()
	{
		return window;
	};

	void toggleFullscreen(uint32 windowFlags)
	{
		SDL_SetWindowFullscreen(window, windowFlags);
	}


private:
	SDL_Window * window;

};