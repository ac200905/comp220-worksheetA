#include "Window.h"


Window::Window()
{
	window = nullptr;
}

Window::Window(const char* title)
{
	window = nullptr;
	//Initialise the SDL Library
	initSDL();

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global::SCREEN_WIDTH, global::SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//Checks to see if the window has been created
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);

		//Close the SDL Library
		SDL_Quit();
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Window::initSDL()
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) !=0)
	{
		//Display an error message box
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	/* Just check for one specific subsystem */

	if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
		printf("Video is initialized.\n");
	}
	else {
		printf("Video is not initialized.\n");
	}
	return 0;
}

// A function to check if the window is fullscreen
bool Window::getIsFullscreen()
{
	return isFullscreen;
}

// A function to reverse the fullscreen boolean
void Window::setIsFullscreen()
{
	isFullscreen = !isFullscreen;
}
