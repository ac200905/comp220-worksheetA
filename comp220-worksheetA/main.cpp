//main.cpp - defines the entry point of the application

#include "main.h"


int main(int argc, char* args[])
{
	
	// Transfer this to gameLoop in Game.cpp

	// Create SDL window
	Window window = Window("Main Window");
	SDL_Window* mainWindow = window.getWindow();


	// Initalise Open_GL and GLEW
	GLSetup glSetup = GLSetup(mainWindow);
	// Get Open_GL context.
	SDL_GLContext gl_Context = glSetup.getGLContext();



	//Mouse setup, can probably be moved to sdl init?
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Init deltaTime
	float deltaTime = 0.0f;	// Time between this frame and last frame
	float lastFrame = 0.0f; // Time of last frame



	//Load Mesh
	MeshCollection * tankMesh = new MeshCollection();
	loadMeshFromFile("Tank1.FBX", tankMesh);


	GLuint textureID = loadTextureFromFile("Tank1DF.png");


	GLuint programID = LoadShaders("vertTextured.glsl", "fragTextured.glsl");

	GLint baseTextureLocation = glGetUniformLocation(programID, "baseTexture");
	//GLuint colourLocation = glGetUniformLocation(programID, "triangleColour");
	
	//Translation and scale
	vec3 modelTranslation = vec3(0.0f, 0.0f, 0.0f);
	vec3 modelScale = vec3(1.0f, 1.0f, 1.0f);

	//Rotation
	vec3 modelRotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);

	//Transformation Matricies
	mat4 translationMatrix = translate(modelTranslation);
	mat4 rotationMatrix = rotate(modelRotation.x, xAxis) * rotate(modelRotation.y, yAxis) * rotate(modelRotation.z, zAxis);
	mat4 scaleMatrix = scale(modelScale);
	
	//Caluclate modelMatrix
	mat4 modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;

	// Create Camera
	Camera* camera = new Camera();
	camera->setFoV(90);
	camera->setProjectionMatrix();
	camera->setFullscreenProjectionMatrix();
	camera->setViewMatrix();


	GLuint MVPLocation = glGetUniformLocation(programID, "MVPMatrix");

	
	// Set up new input and PlayerController
	InputSetup* input = new InputSetup();
	PlayerController playerController = PlayerController(input, camera);

	// Set up new game objects
	GameObject* tank1 = new GameObject();
	tank1->giveMesh(tankMesh);

	GameObject* tank2 = new GameObject();
	tank2->giveMesh(tankMesh);

	GameObject* tank3 = new GameObject();
	tank3->giveMesh(tankMesh);

	float tankMoveSpeed = 0;

	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event event;
	while (running)
	{
		//Update deltatime
		float thisFrame = SDL_GetTicks();
		deltaTime = thisFrame - lastFrame;
		lastFrame = thisFrame;

		//Poll for the events which have happened in this frame
		while (SDL_PollEvent(&event))
		{

			//Switch case for every message we are intereted in
			switch (event.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;

				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:

				input->keyboardEvents(event);

				//Check the key code of the key that has been pressed
				switch (event.key.keysym.sym)
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
						camera->setProjectionMatrix();
						SDL_SetWindowFullscreen(mainWindow, 0);
					}
					else
					{
						window.setIsFullscreen();
						glViewport(0, 0, global::FULLSCREEN_WIDTH, global::FULLSCREEN_HEIGHT);
						camera->setFullscreenProjectionMatrix();
						SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
					}
					break;
				}
			case SDL_KEYUP:
				input->keyboardEvents(event);
				break;

			case SDL_MOUSEMOTION:
				input->mouseInput(event.motion.xrel, event.motion.yrel);
				playerController.mouseControls();
				break;

			case SDL_WINDOWEVENT:
				//Check for window being resized
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					//Update size of screen variables <- needed for mouse calculations
				}
				break;
			}
		}

		if (window.getIsFullscreen())
		{
			mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
		}
		if (!window.getIsFullscreen())
		{
			//Calculate MVP matrix
			mat4 MVPMatrix = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
		}

		//Handle keyboard input
		playerController.keyboardControls(deltaTime);




		//Calculate MVP matrix
		mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;


		
		//Do rendering here!
		// Culls the clockwise facing side of the triangle
		glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0f);


		

		// Linking shaders
		glUseProgram(programID);



		//If we want another texture do the following
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, anotherTextureID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		//-------------------------------------
		//-------------------------------------

		

		

		GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
		GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
		GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
		

		//Send Uniform Values

		GLint baseTextureLocation = glGetUniformLocation(programID, "baseTexture");

		glUniform1i(baseTextureLocation, 0);

		//MVP matrix
		glUniformMatrix4fv(MVPLocation, 1, false, &MVPMatrix[0][0]);

		//send the uniforms across
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));
		glUniform1i(baseTextureLocation, 0);

		
		tankMoveSpeed -= 0.01f;
		
		if (tank1)
		{

			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(tank1->modelMatrix));

			tank1->scale = vec3(1.0f);
			tank1->position = vec3(tankMoveSpeed, 0, 0);
			tank1->update();
			tank1->render();
		}

		if (tank2)
		{
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(tank2->modelMatrix));

			tank2->rotation.y -= 0.01;
			tank2->scale = vec3(1.0f);
			tank2->position = vec3(0, 0, -10);
			tank2->update();
			tank2->render();
		}

		if (tank3)
		{

			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(tank3->modelMatrix));

			tank3->rotation.y += 0.01;
			tank3->scale = vec3(1.0f);
			tank3->position = vec3(0, 0, 10);
			tank3->update();
			tank3->render();
		}
		

		// Screen refresh
		SDL_GL_SwapWindow(mainWindow);
	}

	if (tankMesh)
	{
		delete tankMesh;
		tankMesh = nullptr;
	}


	glDeleteProgram(programID);

	glDeleteTextures(1, &textureID);

	//Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
	
	return 0;
}