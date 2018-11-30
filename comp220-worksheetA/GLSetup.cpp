#include "GLSetup.h"


GLSetup::GLSetup()
{
	
}

GLSetup::GLSetup(SDL_Window* Window)
{
	//Get application window
	window = Window;

	//Setup Open_GL and GLEW
	setGLVersion();
	CreateGLContext();
	initGLEW();
}

GLSetup::~GLSetup()
{
	SDL_GL_DeleteContext(glContext);
}

void GLSetup::setGLVersion()
{
	// Request 3.2 Core OpenGL version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
}

int GLSetup::CreateGLContext()
{
	//Create OPEN_GL context
	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "CreateContext failed", SDL_GetError(), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	return 0;
}

int GLSetup::initGLEW()
{
	//Init GLEW
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW initilisation failed", (char*)glewGetErrorString(error), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	return 0;
}

