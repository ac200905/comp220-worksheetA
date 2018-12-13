#include "Game.h"
#include <time.h>
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
	//loadMeshFromFile("lowpolytree1.fbx", treeMesh);
	loadMeshFromFile("tree.dae", treeMesh);

	grassMesh = new MeshCollection();
	loadMeshFromFile("grasspatch.obj", grassMesh);

	lampMesh = new MeshCollection();
	loadMeshFromFile("lamp.fbx", lampMesh);

	barrelMesh = new MeshCollection();
	loadMeshFromFile("barrel.fbx", barrelMesh);

	tentMesh = new MeshCollection();
	loadMeshFromFile("Tent.obj", tentMesh);

	rockMesh = new MeshCollection();
	loadMeshFromFile("Rockfbx.fbx", rockMesh);

	fireMesh = new MeshCollection();
	loadMeshFromFile("campfire.fbx", fireMesh);

	// Textures
	diffuseTextureID = loadTextureFromFile("tree2.png");
	diffuseTextureID_Grass = loadTextureFromFile("dirttexture.png");
	diffuseTextureID_Barrel = loadTextureFromFile("barreltexture.png");
	diffuseTextureID_Lamp = loadTextureFromFile("lampred.png");
	//diffuseTextureID_Rock = loadTextureFromFile("RockTexture.jpg");
	diffuseTextureID_Rock = loadTextureFromFile("rockgrey.png");
	diffuseTextureID_Tent = loadTextureFromFile("tentblue.png");
	diffuseTextureID_Tree = loadTextureFromFile("tree2.png");
	diffuseTextureID_Campfire = loadTextureFromFile("campfire.jpg");
	specularTextureID = loadTextureFromFile("specmap.png");

	// Load shaders
	programID = LoadShaders("vertBlinnPhongPL.glsl", "fragBlinnPhongPL.glsl");

	// Set up new game objects
	grass = new GameObject();
	grass->giveMesh(grassMesh);

	tree1 = new GameObject();
	tree1->giveMesh(treeMesh);
	TreeList.push_back(tree1);

	tree2 = new GameObject();
	tree2->giveMesh(treeMesh);
	TreeList.push_back(tree2);

	tree3 = new GameObject();
	tree3->giveMesh(treeMesh);
	TreeList.push_back(tree3);

	barrel = new GameObject();
	barrel->giveMesh(barrelMesh);

	lamp = new GameObject();
	lamp->giveMesh(lampMesh);

	tent = new GameObject();
	tent->giveMesh(tentMesh);

	rock1 = new GameObject();
	rock1->giveMesh(rockMesh);

	fire = new GameObject();
	fire->giveMesh(fireMesh);
	
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

	

	// Game loop
	while (running)
	{
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		// Update deltatime
		float thisFrame = SDL_GetTicks();
		deltaTime = thisFrame - lastFrame;
		lastFrame = thisFrame;

		if (frameDelay > deltaTime)
		{
			SDL_Delay(frameDelay - deltaTime);
		}

		gameInputEvents();

		gameUpdate();

		gameRender();

	}

	gameClean();
}

void Game::gameUpdate()
{
	cameraPosition = camera->getPosition();
	

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

	turnspeed = turnspeed + 0.001 * deltaTime;

	if (grass)
	{
		grass->scale = vec3(0.1);
		grass->position = vec3(0, 0, 0);
		grass->setRotation(radians(-90.0f), 0, 0);
		grass->update();
	}

	if (tree1)
	{
		tree1->scale = vec3(2.5);
		//tree1->position = vec3(0, -1.7, -7);
		tree1->position = vec3(0, 0.5, -7);
		//tree1->setRotation(radians(-90.0f), 0, radians(-45.0f));
		tree1->update();
	}

	if (tree2)
	{
		tree2->scale = vec3(2.5);
		//tree2->position = vec3(5, -1.7, 7);
		tree2->position = vec3(5, 0.5, 7);
		//tree2->setRotation(radians(-90.0f), 0, radians(-45.0f));
		tree2->update();
	}

	if (tree3)
	{
		tree3->scale = vec3(2.5);
		
		tree3->position = vec3(-5, 0, -7);
		
		tree3->update();
	}

	if (lamp)
	{
		lamp->scale = vec3(0.002);
		lamp->position = vec3(-3, 2.5, -4);
		lamp->setRotation(0, 0, 0);
		lamp->update();
		lamp->render();
	}

	if (barrel)
	{
		barrel->scale = vec3(0.02);
		barrel->position = vec3(-3, 1, -4);
		barrel->setRotation(0, 0, 0);
		barrel->update();
		barrel->render();
	}

	if (tent)
	{
		tent->scale = vec3(0.05);
		tent->position = vec3(6, 0.5, -4);
		tent->setRotation(radians(-90.0f), 0, radians(-45.0f));
		tent->update();
		tent->render();
	}

	if (rock1)
	{
		rock1->scale = vec3(0.5);
		rock1->position = vec3(0, 0, 5);
		//rock1->setRotation(radians(-90.0f), 0, 0);
		rock1->update();
		rock1->render();
	}

	if (fire)
	{
		fire->scale = vec3(1);
		fire->position = vec3(0, 1, 0);
		fire->setRotation(radians(-90.0f), 0, 0);
		fire->update();
		fire->render();
	}

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
	glm::vec4 specularLightColour = glm::vec4(0.0f);

	float specularMaterialPower = 10000.0f;

	//float lightIntensity = 9.0f;

	

	//Point light
	std::vector<PointLight> PointLights;

	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });

	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,7.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,7.0f,0.0f) });

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

	GLint lightIntensityLocation = glGetUniformLocation(programID, "lightIntensity");
	
	GLint ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	GLint diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	GLint specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");

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
	glUniform1i(diffuseTextureTreeLocation, 2);

	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(ambientMaterialColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(specularMaterialColour));

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));

	glUniform4fv(directionalLightDiffuseColourLocation, 1, glm::value_ptr(diffuseLightColour));
	glUniform4fv(directionalLightSpecularColourLocation, 1, glm::value_ptr(specularLightColour));

	glUniform1f(specularMaterialPowerLocation, specularMaterialPower);

	glUniform1f(lightIntensityLocation, lightIntensity);

	glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

	for (int i = 0; i < PointLights.size(); i++)
	{
		glUniform4fv(pointLightDiffuseColourLocations[i], 1, value_ptr(PointLights[i].DiffuseColour));
		glUniform4fv(pointLightSpecularColourLocations[i], 1, value_ptr(PointLights[i].SpecularColour));
		glUniform3fv(pointLightPositionLocations[i], 1, value_ptr(PointLights[i].Position));
	}

	glUniform1i(numberOfPointLightsLocation, PointLights.size());
	
	flickerThreshold += (rand() % 10 + 1);

	if (flickerThreshold > 50)
	{
		lightFlicker = true;
		flickerThreshold = 0;
	}

	if (lightFlicker == true)
	{
		lightIntensity = (rand() % 3000 + 3000); //range + start point
		glUniform1f(lightIntensityLocation, lightIntensity);

		lightFlicker = false;
	}

	

	if (tree1)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tree1->modelMatrix));
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tree);
		tree1->render();
	}

	if (tree2)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tree2->modelMatrix));
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tree);
		tree2->render();
	}

	if (barrel)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(barrel->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Barrel);
		barrel->render();
	}

	if (lamp)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(lamp->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Lamp);
		lamp->render();
	}

	if (grass)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(grass->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Grass);
		grass->render();
	}

	if (tent)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tent->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tent);
		tent->render();
	}

	if (rock1)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(rock1->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Rock);
		rock1->render();
	}
	
	if (fire)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(fire->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Campfire);
		fire->render();
	}

	for (GameObject * obj : TreeList)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(obj->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tree);
		obj->render();
	}
	SDL_GL_SwapWindow(window->getWindow());

}

void Game::gameInputEvents()
{
	
	// Poll for the events which have happened in this frame
	while (SDL_PollEvent(&event))
	{
		// Testing controller - should be refactored to player controller
		//std::cout << event.caxis.value << std::endl;
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

	if (lampMesh)
	{
		delete lampMesh;
		lampMesh = nullptr;
	}

	if (rockMesh)
	{
		delete rockMesh;
		rockMesh = nullptr;
	}

	if (tentMesh)
	{
		delete tentMesh;
		tentMesh = nullptr;
	}

	if (fireMesh)
	{
		delete fireMesh;
		fireMesh = nullptr;
	}

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	//SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

}

