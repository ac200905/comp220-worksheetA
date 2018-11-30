//main.cpp - defines the entry point of the application

#include "main.h"


int main(int argc, char* args[])
{
	
	Game game;


	game.gameLoop();

	
	// Transfer this to gameLoop in Game.cpp
	/*
	// Create SDL window
	Window window = Window("Night Fire Game");
	SDL_Window* mainWindow = window.getWindow();

	// Initalise Open_GL and GLEW
	GLSetup glSetup = GLSetup(mainWindow);
	// Get Open_GL context.
	SDL_GLContext gl_Context = glSetup.getGLContext();

	// Mouse setup
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// Init deltaTime
	float deltaTime = 0.0f;	// Time between this frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	// Load Mesh
	MeshCollection * tankMesh = new MeshCollection();
	loadMeshFromFile("Tank1.FBX", tankMesh);

	// Load Mesh
	MeshCollection * penguinMesh = new MeshCollection();
	loadMeshFromFile("Penguin.fbx", penguinMesh);

	// Load Mesh
	MeshCollection * jetMesh = new MeshCollection();
	loadMeshFromFile("jet.fbx", jetMesh);

	// Textures
	GLuint textureID_01 = loadTextureFromFile("Tank1DF.png");
	GLuint textureID_02 = loadTextureFromFile("Penguin.png");
	GLuint textureID_03 = loadTextureFromFile("jet.jpg");

	// Load shaders
	GLuint programID = LoadShaders("vertTextured.glsl", "fragTextured.glsl");

	// Translation and scale
	vec3 modelTranslation = vec3(0.0f, 0.0f, 0.0f);
	vec3 modelScale = vec3(1.0f, 1.0f, 1.0f);

	// Rotation
	vec3 modelRotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 xAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 yAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 zAxis = vec3(0.0f, 0.0f, 1.0f);

	// Transformation Matricies
	mat4 translationMatrix = translate(modelTranslation);
	mat4 rotationMatrix = rotate(modelRotation.x, xAxis) * rotate(modelRotation.y, yAxis) * rotate(modelRotation.z, zAxis);
	mat4 scaleMatrix = scale(modelScale);
	
	// Caluclate modelMatrix
	mat4 modelMatrix = rotationMatrix * scaleMatrix * translationMatrix;

	GLuint MVPLocation = glGetUniformLocation(programID, "MVPMatrix");

	// Create Camera
	Camera* camera = new Camera();
	camera->setFoV(90);
	camera->setProjectionMatrix();
	camera->setFullscreenProjectionMatrix();
	camera->setViewMatrix();

	

	// Set up new input and PlayerController
	InputSetup* input = new InputSetup();
	PlayerController playerController = PlayerController(input, camera);

	input->joystickInit();

	// Set up new game objects
	GameObject* tank1 = new GameObject();
	tank1->giveMesh(tankMesh);

	GameObject* tank2 = new GameObject();
	tank2->giveMesh(tankMesh);

	GameObject* tank3 = new GameObject();
	tank3->giveMesh(tankMesh);

	GameObject* penguin = new GameObject();
	penguin->giveMesh(penguinMesh);

	GameObject* jet = new GameObject();
	jet->giveMesh(jetMesh);

	float tankMoveSpeed = 0;
	float jetMoveSpeed = 0;

	bool rotateCameraLeft = false;
	bool rotateCameraRight = false;
	bool rotateCameraUp = false;
	bool rotateCameraDown = false;

	bool moveCameraLeft = false;
	bool moveCameraRight = false;
	bool moveCameraForward = false;
	bool moveCameraBack = false;

	bool moveCameraUp = false;
	bool moveCameraDown = false;

	// Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	// SDL Event structure, this will be checked in the while loop
	SDL_Event event;
	while (running)
	{	
		// Update deltatime
		float thisFrame = SDL_GetTicks();
		deltaTime = thisFrame - lastFrame;
		lastFrame = thisFrame;

		// Poll for the events which have happened in this frame
		while (SDL_PollEvent(&event))
		{
			// Testing controller - should be refactored to player controller
			std::cout << event.caxis.value << std::endl;
			if (SDL_CONTROLLERAXISMOTION)
			{
				if (event.caxis.which == 0)
				{
					// Left analog stick
					if (event.caxis.axis == 0)
					{
						if (event.caxis.value < -32000)
						{
							moveCameraLeft = true;
							moveCameraRight = false;
						}
						else if (event.caxis.value > 32000)
						{
							moveCameraLeft = false;
							moveCameraRight = true;
						}
						else
						{
							moveCameraLeft = false;
							moveCameraRight = false;
						}
					}
					if (event.caxis.axis == 1)
					{
						if (event.caxis.value < -32000)
						{
							moveCameraForward = true;
							moveCameraBack = false;
						}
						else if (event.caxis.value > 32000)
						{
							moveCameraBack = true;
							moveCameraForward = false;
						}
						else
						{
							moveCameraBack = false;
							moveCameraForward = false;
						}
					}

					// Right analog stick
					if (event.caxis.axis == 3)
					{
						if (event.caxis.value < -32000)
						{
							rotateCameraLeft = true;
							rotateCameraRight = false;
						}
						else if (event.caxis.value > 32000)
						{
							rotateCameraLeft = false;
							rotateCameraRight = true;
						}
						else
						{
							rotateCameraLeft = false;
							rotateCameraRight = false;
						}
					}
					if (event.caxis.axis == 4)
					{
						if (event.caxis.value < -32000)
						{
							rotateCameraUp = true;
							rotateCameraDown = false;
						}
						else if (event.caxis.value > 32000)
						{
							rotateCameraDown = true;
							rotateCameraUp = false;
						}
						else
						{
							rotateCameraUp = false;
							rotateCameraDown = false;
						}
					}

					// Left trigger
					if (event.caxis.axis == 5)
					{
						if (event.caxis.value > 32000)
						{
							moveCameraUp = true;
							moveCameraDown = false;
						}
						else
						{
							moveCameraUp = false;
							moveCameraDown = false;
						}
					}
					// Right trigger
					if (event.caxis.axis == 2)
					{
						if (event.caxis.value > 32000)
						{
							moveCameraUp = false;
							moveCameraDown = true;
						}
						else
						{
							moveCameraUp = false;
							moveCameraDown = false;
						}
					}
				}
			}

			// Switch case for every message we are intereted in
			switch (event.type)
			{
				// QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;

			// Called when a key has been pressed down
			case SDL_KEYDOWN:

				input->keyboardEvents(event);

				// Check the key code of the key that has been pressed
				switch (event.key.keysym.sym)
				{
					// Escape key
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
			// Called when a key has been released
			case SDL_KEYUP:
				input->keyboardEvents(event);
				break;

			case SDL_MOUSEMOTION:
				input->mouseInput(event.motion.xrel, event.motion.yrel);
				playerController.mouseControls();
				break;

			

			}	
		}

		if (window.getIsFullscreen())
		{
			mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
		}
		if (!window.getIsFullscreen())
		{
			// Calculate MVP matrix
			mat4 MVPMatrix = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
		}

		// Changing camera pitch and yaw
		if (rotateCameraLeft == true)
		{
			camera->increaseYaw(-2);
		}
		if (rotateCameraRight == true)
		{
			camera->increaseYaw(2);
		}
		if (rotateCameraUp == true)
		{
			camera->increasePitch(-2);
		}
		if (rotateCameraDown == true)
		{
			camera->increasePitch(2);
		}

		// Strafing and moving towards or away from target
		if (moveCameraLeft == true)
		{
			camera->moveXAxis(1);
		}
		if (moveCameraRight == true)
		{
			camera->moveXAxis(-1);
		}
		if (moveCameraForward == true)
		{
			camera->moveZAxis(1);
		}
		if (moveCameraBack == true)
		{
			camera->moveZAxis(-1);
		}

		// Moving camera up/down
		if (moveCameraUp == true)
		{
			camera->moveYAxis(1);
		}
		if (moveCameraDown == true)
		{
			camera->moveYAxis(-1);
		}

		// Handle keyboard input
		playerController.keyboardControls(deltaTime);
		//playerController.keyboardControls(timer.GetDeltaTime);

		// Handle joystick input
		playerController.joystickControls();

		// Calculate MVP matrix
		mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

		//Do rendering here!
		// Culls the clockwise facing side of the triangle
		glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0f);

		// Linking shaders
		glUseProgram(programID);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID_01);

		// Second texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureID_02);

		// Third texture
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureID_03);


		GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
		GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
		GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");

		GLint baseTextureLocation = glGetUniformLocation(programID, "baseTexture");

		
		// Send the uniforms across
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(camera->getProjectionMatrix()));
		glUniform1i(baseTextureLocation, 0);

		//MVP matrix
		glUniformMatrix4fv(MVPLocation, 1, false, &MVPMatrix[0][0]);


		// Manipulating game objects
		tankMoveSpeed -= 0.01f * deltaTime;
		jetMoveSpeed -= 0.02f * deltaTime;

		if (tank1)
		{

			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tank1->modelMatrix));

			tank1->scale = vec3(1.0f);
			tank1->position = vec3(100+tankMoveSpeed, 0, 0);
			tank1->update();
			tank1->render();
			if (tank1->position.x < -100)
			{
				tankMoveSpeed = 0;
			}
		}

		if (tank2)
		{
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tank2->modelMatrix));

			tank2->rotation.y -= 0.0002 * deltaTime;
			tank2->scale = vec3(1.0f);
			tank2->position = vec3(0, 0, -10);
			tank2->update();
			tank2->render();
		}

		if (tank3)
		{
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tank3->modelMatrix));

			tank3->rotation.y += 0.0002 * deltaTime;
			tank3->scale = vec3(1.0f);
			tank3->position = vec3(0, 0, 10);
			tank3->update();
			tank3->render();
		}

		if (penguin)
		{
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(penguin->modelMatrix));
			// Send penguin texture
			glUniform1i(baseTextureLocation, 1);

			penguin->rotation.x = -1.55;
			penguin->rotation.z = -1.5;
			penguin->rotation.y -= 0.004 * deltaTime;
			penguin->scale = vec3(2.0f);
			penguin->position = vec3(5, 5, 50);
			penguin->update();
			penguin->render();
		}

		if (jet)
		{
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(jet->modelMatrix));
			// Send jet texture
			glUniform1i(baseTextureLocation, 2);
			if (jet->position.z >= 100)
			{
				jetMoveSpeed = 0;
			}
			jet->rotation.x = -1.6;
			jet->rotation.z = 0;
			jet->rotation.y += 0.0008 * deltaTime;
			jet->scale = vec3(0.3f);
			jet->position = vec3(20, 10, -100 - jetMoveSpeed);
			jet->update();
			jet->render();
			
		}

		// Screen refresh
		SDL_GL_SwapWindow(mainWindow);
	}

	if (tankMesh)
	{
		delete tankMesh;
		tankMesh = nullptr;
	}

	if (penguinMesh)
	{
		delete penguinMesh;
		penguinMesh = nullptr;
	}

	if (jetMesh)
	{
		delete jetMesh;
		jetMesh = nullptr;
	}

	glDeleteProgram(programID);

	glDeleteTextures(1, &textureID_01);
	glDeleteTextures(1, &textureID_02);
	glDeleteTextures(1, &textureID_03);

	//Delete Context
	SDL_GL_DeleteContext(gl_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
	*/
	return 0;
}