#include "Game.h"

#include <iostream>

// Should refactor game loop out of main.cpp

Game::Game()
{
	
}


Game::~Game()
{
}

void Game::gameInit()
{
	//init SDL

	// Create SDL window
	window = new Window("Night Fire Game");

	// Initalise Open_GL and GLEW
	glSetup = new GLSetup(window->getWindow());
	
	// Mouse setup
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	// Init deltaTime
	float deltaTime = 0.0f;	// Time between this frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	bool running = true;

	treeMesh = new MeshCollection();
	loadMeshFromFile("lowpolytree.fbx", treeMesh);
	//loadMeshFromFile("utah-teapot.fbx", treeMesh);
	//loadMeshFromFile("Tank1.FBX", treeMesh);

	fireMesh = new MeshCollection();
	loadMeshFromFile("campfire.fbx", fireMesh);


	// Textures
	//diffuseTextureID = loadTextureFromFile("campfire.jpg");
	diffuseTextureID = loadTextureFromFile("tree.png");
	specularTextureID = loadTextureFromFile("specmap.png");
	//diffuseTextureID_Tree = loadTextureFromFile("tree.png");


	// Load shaders
	//programID = LoadShaders("vertTextured.glsl", "fragTextured.glsl");
	//programID = LoadShaders("vertBlinnPhong.glsl", "fragBlinnPhong.glsl");
	//programID = LoadShaders("vertCelShader.glsl", "fragCelShader.glsl");
	programID = LoadShaders("vertBlinnPhongPL.glsl", "fragBlinnPhongPL.glsl");

	// Set up new game objects
	tree1 = new GameObject();
	tree1->giveMesh(treeMesh);

	tree2 = new GameObject();
	tree2->giveMesh(treeMesh);

	fire = new GameObject();
	fire->giveMesh(fireMesh);
	
	if (tree1)
	{

		
		tree1->scale = vec3(1.5);
		tree1->position = vec3(0, -1.7, -7);
		//tree1->setRotation(radians(-90.0f), 0, 0);
		tree1->update();
		tree1->render();

	}

	if (tree2)
	{
		
		tree2->scale = vec3(1.5);
		tree2->position = vec3(5, -1.7, 7);
		//tree2->setRotation(radians(-90.0f), 0, 0);
		tree2->update();
		tree2->render();

	}

	if (fire)
	{
		
		fire->scale = vec3(1);
		fire->position = vec3(0, 0, 0);
		fire->setRotation(radians(-90.0f), 0, 0);
		fire->update();
		fire->render();

	}
	
	float turnspeed = 0;

	camera = new Camera();
	camera->setFoV(90);
	camera->setProjectionMatrix();
	camera->setFullscreenProjectionMatrix();
	camera->setViewMatrix();

	cameraPosition = camera->getPosition();

	input = new InputSetup();

	playerController = PlayerController(input, camera);

	input->joystickInit();

	// SDL Event structure, this will be checked in the while loop
	SDL_Event event;
}

void Game::gameLoop()
{

	gameInit();

	

	// Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	
	
	while (running)
	{
		// Update deltatime
		float thisFrame = SDL_GetTicks();
		deltaTime = thisFrame - lastFrame;
		lastFrame = thisFrame;

		gameInputEvents();

		gameUpdate();

		gameRender();

		
	}

	gameClean();
}

void Game::gameUpdate()
{
	cameraPosition = camera->getPosition();
	//tank1->update();

	if (window->getIsFullscreen())
	{
		mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
	}
	if (!window->getIsFullscreen())
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


	// Handle joystick input
	playerController.joystickControls();

	// Calculate MVP matrix
	//mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

}

void Game::gameRender()
{
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

	// Materials
	glm::vec4 ambientMaterialColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 diffuseMaterialColour = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	// Light
	glm::vec4 ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//glm::vec4 specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularLightColour = glm::vec4(0.0f);

	float specularMaterialPower = 10000.0f;

	//vec3 lightDirection = vec3(0.0f, 0.0f, -1.0f);// points directly down

	//Point light
	std::vector<PointLight> PointLights;
	//PointLights.push_back({ glm::vec4(1.0f,0.0f,0.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	//PointLights.push_back({ glm::vec4(0.0f,1.0f,0.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	//PointLights.push_back({ glm::vec4(0.0f,0.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });

	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	


	// Culls the clockwise facing side of the triangle
	glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);

	// Linking shaders
	glUseProgram(programID);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTextureID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTextureID);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tree);


	// Get uniforms from shader
	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
	GLint diffuseTextureLocation = glGetUniformLocation(programID, "diffuseTexture");
	GLint diffuseTextureTreeLocation = glGetUniformLocation(programID, "diffuseTextureTree");
	GLint specularTextureLocation = glGetUniformLocation(programID, "specularTexture"); 

	GLint directionalLightDiffuseColourLocation = glGetUniformLocation(programID, "directionalLight.diffuseColour");
	GLint directionalLightSpecularColourLocation = glGetUniformLocation(programID, "directionalLight.specularColour");

	
	GLint ambientMaterialColourLocation = glGetUniformLocation(programID, "ambientMaterialColour");
	GLint diffuseMaterialColourLocation = glGetUniformLocation(programID, "diffuseMaterialColour");
	GLint specularMaterialColourLocation = glGetUniformLocation(programID, "specularMaterialColour");
	GLint specularMaterialPowerLocation = glGetUniformLocation(programID, "specularMaterialPower");
	
	GLint ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	GLint diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	GLint specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");

	//GLint lightDirectionLocation = glGetUniformLocation(programID, "lightDirection");
	GLint lightDirectionLocation = glGetUniformLocation(programID, "directionalLight.direction");

	GLint cameraPositionLocation = glGetUniformLocation(programID, "cameraPosition");

	const int MAX_NO_OF_POINT_LIGHTS = 8;
	GLint pointLightDiffuseColourLocations[MAX_NO_OF_POINT_LIGHTS];
	GLint pointLightSpecularColourLocations[MAX_NO_OF_POINT_LIGHTS];
	GLint pointLightPositionLocations[MAX_NO_OF_POINT_LIGHTS];

	char characterBuffer[50];
	for (int i = 0; i < MAX_NO_OF_POINT_LIGHTS; i++)
	{
		sprintf_s(characterBuffer, "pointLights[%i].diffuseColour", i);
		pointLightDiffuseColourLocations[i] = glGetUniformLocation(programID, characterBuffer);

		sprintf_s(characterBuffer, "pointLights[%i].specularColour", i);
		pointLightSpecularColourLocations[i] = glGetUniformLocation(programID, characterBuffer);

		sprintf_s(characterBuffer, "pointLights[%i].position", i);
		pointLightPositionLocations[i] = glGetUniformLocation(programID, characterBuffer);
	}

	GLint numberOfPointLightsLocation = glGetUniformLocation(programID, "numberOfPointLights");

	// Send the uniforms across

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(camera->getProjectionMatrix()));
	glUniform1i(diffuseTextureLocation, 0);
	glUniform1i(specularTextureLocation, 1);
	//glUniform1i(diffuseTextureTreeLocation, 2);

	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(ambientMaterialColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(specularMaterialColour));

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
	//glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
	//glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));

	glUniform4fv(directionalLightDiffuseColourLocation, 1, glm::value_ptr(diffuseLightColour));
	glUniform4fv(directionalLightSpecularColourLocation, 1, glm::value_ptr(specularLightColour));

	glUniform1f(specularMaterialPowerLocation, specularMaterialPower);

	//glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));

	glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

	for (int i = 0; i < PointLights.size(); i++)
	{
		glUniform4fv(pointLightDiffuseColourLocations[i], 1, value_ptr(PointLights[i].DiffuseColour));
		glUniform4fv(pointLightSpecularColourLocations[i], 1, value_ptr(PointLights[i].SpecularColour));
		glUniform3fv(pointLightPositionLocations[i], 1, value_ptr(PointLights[i].Position));
	}

	glUniform1i(numberOfPointLightsLocation, PointLights.size());
	
	turnspeed = turnspeed + 0.001 * deltaTime;
	if (tree1)
	{

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tree1->modelMatrix));
		//glUniform1i(diffuseTextureLocation, 2);
		tree2->setRotation(0, turnspeed, 0);
		tree1->update();
		tree1->render();

	}

	if (tree2)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tree2->modelMatrix));
		//glUniform1i(diffuseTextureLocation, 2);
		
		tree2->update();
		tree2->render();

	}
	
	if (fire)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(fire->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		
		fire->update();
		fire->render();

	}
	

	SDL_GL_SwapWindow(window->getWindow());

}

void Game::gameInputEvents()
{
	
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
				if (window->getIsFullscreen())
				{
					window->setIsFullscreen();
					glViewport(0, 0, global::SCREEN_WIDTH, global::SCREEN_HEIGHT);
					camera->setProjectionMatrix();
					//SDL_SetWindowFullscreen(mainWindow, 0);
					window->toggleFullscreen(0);
				}
				else
				{
					window->setIsFullscreen();
					glViewport(0, 0, global::FULLSCREEN_WIDTH, global::FULLSCREEN_HEIGHT);
					camera->setFullscreenProjectionMatrix();
					window->toggleFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP);
					//SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
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

}

void Game::gameClean()
{
	glDeleteProgram(programID);

	glDeleteTextures(1, &diffuseTextureID);
	glDeleteTextures(1, &specularTextureID);
	

	//Delete Context
	//SDL_GL_DeleteContext(gl_Context);
	if (glSetup)
	{
		delete glSetup;
		glSetup = nullptr;
	}

	if (window)
	{
		delete window;
		window = nullptr;
	}

	if (treeMesh)
	{
		delete treeMesh;
		treeMesh = nullptr;
	}

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	//SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

}

