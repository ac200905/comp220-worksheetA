//main.cpp - defines the entry point of the application

#include "main.h"


int main(int argc, char* args[])
{
	//Create SDL window
	Window window = Window("Main Window");
	SDL_Window* mainWindow = window.getWindow();


	//Initalise Open_GL and GLEW
	GLSetup glSetup = GLSetup(mainWindow);
	//Get Open_GL context.
	SDL_GLContext gl_Context = glSetup.getGLContext();


	//Vertex array
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	// An array of 4 vectors which represents 8 vertices
	// {x,y,z,r,g,b,a}
	static const Vertex cubeVertexArray[] =
	{
		{ -0.5f,-0.5f,0.0f,  1.0f,0.0f,1.0f,1.0f },
	{ 0.5f,-0.5f,0.0f,  0.0f,1.0f,1.0f,1.0f },
	{ 0.5f,0.5f,0.0f,  1.0f,1.0f,0.0f,1.0f },
	{ -0.5f,0.5f,0.0f,  1.0f,1.0f,1.0f,1.0f },

	{ -0.5f,-0.5f,-1.0f,  1.0f,0.0f,0.0f,1.0f },
	{ 0.5f,-0.5f,-1.0f,  1.0f,1.0f,0.0f,1.0f },
	{ 0.5f,0.5f,-1.0f,  0.0f,0.0f,1.0f,1.0f },
	{ -0.5f,0.5f,-1.0f,  0.0f,1.0f,0.0f,1.0f }

	};

	// Indicies must be set in anti-clockwise if on the outside of the cube order due to back-face culling
	static const int cubeIndiciesArray[] =
	{
		0,1,2, // Represenative of one triangle
		2,3,0,

		6,5,4,
		4,7,6,

		7,3,2,
		2,6,7,

		6,2,1,
		1,5,6,

		3,7,4,
		4,0,3,

		1,0,5,
		5,0,4

	};

	// Culls the clockwise facing side of the triangle
	glEnable(GL_CULL_FACE);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, (8 * sizeof(Vertex)), cubeVertexArray, GL_STATIC_DRAW);

	GLuint elementbuffer;
	// Generate 1 buffer, put the resulting identifier in elementbuffer
	glGenBuffers(1, &elementbuffer);
	// The following commands will talk about our 'elementbuffer' buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	// Give our elements to OpenGL.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (36 * sizeof(int)), cubeIndiciesArray, GL_STATIC_DRAW);

	GLuint programID = LoadShaders("vertShader.glsl", "fragShader.glsl");

	GLuint colourLocation = glGetUniformLocation(programID, "triangleColour");

	// ModelMatrix setup. 
	vec3 modelTranslation = vec3(0.0f, 0.0f, 0.0f);
	vec3 modelRotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 modelScale = vec3(1.0f, 1.0f, 1.0f);

	// Create Camera
	Camera camera = Camera();

	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		//Poll for the events which have happened in this frame
		while (SDL_PollEvent(&ev))
		{
			//The mouse offsets
			int x = 0, y = 0;

			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;

				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;

					// Switching between windowed and fullscreen 
				case SDLK_F11:
					if (window.getIsFullscreen())
					{
						window.setIsFullscreen();
						glViewport(0, 0, global::SCREEN_WIDTH, global::SCREEN_HEIGHT);
						SDL_SetWindowFullscreen(mainWindow, 0);
					}
					else
					{
						window.setIsFullscreen();
						glViewport(0, 0, global::FULLSCREEN_WIDTH, global::FULLSCREEN_HEIGHT);
						SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
					}
					break;

				case SDLK_RIGHT:
					modelTranslation = modelTranslation - vec3(0.1, 0, 0);
					break;

				case SDLK_LEFT:
					modelTranslation = modelTranslation + vec3(0.1, 0, 0);
					break;

				case SDLK_UP:
					modelTranslation = modelTranslation - vec3(0, 0.1, 0);
					break;

				case SDLK_DOWN:
					modelTranslation = modelTranslation + vec3(0, 0.1, 0);
					break;

				case SDLK_a:
					modelRotation = modelRotation + vec3(0.0f, 0.1f, 0.0f);
					break;

				case SDLK_d:
					modelRotation = modelRotation - vec3(0.0f, 0.1f, 0.0f);
					break;

				case SDLK_w:
					modelRotation = modelRotation + vec3(0.1f, 0.0f, 0.0f);
					break;

				case SDLK_s:
					modelRotation = modelRotation - vec3(0.1f, 0.0f, 0.0f);
					break;

				case SDLK_q:
					modelRotation = modelRotation + vec3(0.0f, 0.0f, 0.1f);
					break;

				case SDLK_e:
					modelRotation = modelRotation - vec3(0.0f, 0.0f, 0.1f);
					break;

				case SDLK_SPACE:
					modelScale = modelScale + vec3(0.1f, 0.1f, 0.1f);
					break;

				case SDLK_LSHIFT:
					modelScale = modelScale - vec3(0.1f, 0.1f, 0.1f);
					break;

				case SDL_MOUSEMOTION:
					//mouseMotion = Vec2I(event.motion.x, event.motion.y);
					break;


				}
			}
		}

		//Do rendering here!
		glClearColor(0.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// Linking shaders
		glUseProgram(programID);



		//-------------------------------------
		//-------------------------------------



		//Rotation Axes
		vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
		vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
		vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);

		//Transformation Matrices 
		mat4 translationMatrix = translate(modelTranslation);
		mat4 scaleMatrix = scale(modelScale);
		mat4 rotationMatrix = rotate(modelRotation.x, xAxis) * rotate(modelRotation.y, yAxis) * rotate(modelRotation.z, zAxis);

		//Calculating the modelMatrix
		mat4 modelMatrix = scaleMatrix * rotationMatrix *  translationMatrix;




		//Calculate MVP matrix
		mat4 MVPMatrix = camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix;

		GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
		GLuint MVPLocation = glGetUniformLocation(programID, "MVPMatrix");

		//Send Uniform Values


		//MVP matrix
		glUniformMatrix4fv(MVPLocation, 1, false, &MVPMatrix[0][0]);

		//Set triangle colour
		glUniform4f(colourLocation, 0, 0, 1, 0);


		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		// First attribute buffer : vertices
		// Describe first element in the vertex - For x,y,z
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),     // stride, how big one vertex is 
			(void*)0            // array buffer offset
		);

		// Describe second element in the vertex - For r,g,b,a
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,							// attribute 1, must match the layout in the shader.
			4,							// size
			GL_FLOAT,					// type
			GL_FALSE,					// normalized?
			sizeof(Vertex),				// stride, how big one vertex is //change to sizeof(Vertex)
			(void*)(3 * sizeof(float))  // array buffer offset
		);


		// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
		glDisableVertexAttribArray(0);


		// Screen refresh
		SDL_GL_SwapWindow(mainWindow);
	}

	glDeleteProgram(programID);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	//Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}