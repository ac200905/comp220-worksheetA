#pragma once
#include "main.h"

class GLSetup
{

public:
	GLSetup(SDL_Window* window);
	~GLSetup();

	//Create a new Open_GL context
	int CreateGLContext();

	//Initialise GLEW
	int initGLEW();

	//Set the version information for Open_GL
	void setGLVersion();

	SDL_GLContext getGLContext()
	{
		return glContext;
	}

private:
	SDL_GLContext glContext;
	SDL_Window* window;
};