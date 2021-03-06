#include "Game.h"
#include <time.h>
#include <iostream>

//Demo video of the game working
//https://www.youtube.com/watch?v=MDfq-7ug-EM

Game::Game()
{	
}

Game::~Game()
{
}

/* -------------------
	Particle Emitter 
----------------------*/

//http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/particles-instancing/

// Initialise particle gameobjects
void Game::initParticles()
{
	// Create the default amount of particle instances
	for (GLuint i = 0; i < numParticles; ++i)
	{
		// Create Mesh for particle
		particleMesh = new MeshCollection();
		loadMeshFromFile("Models/cube.fbx", particleMesh);

		GameObject * particle = new GameObject();
		particle->giveMesh(particleMesh);
		particle->scale = vec3(0.2);
		particle->position = vec3(0, 2, 0);
		particle->setRotation(radians(-90.0f), 0, 0);
		particle->update();

		ParticleObjectList.push_back(particle);

	}
}


// Main particle update loop
void Game::updateParticles(GLfloat deltaTime)
{
	// Respawning dead particles
	for (GLuint i = 0; i < numParticles; ++i){
		// Finds the index in the ParticleObjectList of the last particle that died
		int deadParticle = findDeadParticle();
		// Respawns the last particle that died
		respawnParticle(ParticleObjectList[deadParticle]);
	}
	// Update all particles
	for (GLuint i = 0; i < numParticles; ++i){
		GameObject * particle = ParticleObjectList[i];
		// Reduce life of current particle
		particle->decreaseLife(deltaTime); 
		if (particle->getLife() > 0.0f){	
			// Particle still alive: update particle position and scale
			// Update particle position to imitate rising fire
			vec3 currentPos = particle->getPosition();
			currentPos = currentPos + (objectDirection / particleSpeed * deltaTime);
			particle->setPositionVec3(currentPos);
			// Update particle scale to give a shrinking effect
			vec3 currentScale = particle->getScale();
			currentScale = (currentScale - scaleBack * deltaTime) ;
			particle->setScaleVec3(currentScale);

		}
		// Update particle GameObject
		particle->update();
	}
}


// Find index of that last particle that died
GLuint Game::findDeadParticle()
{
	// Start from the idex of the last particle that died.
	for (GLuint i = lastDeadParticle; i < numParticles; ++i) {
		// If the particle is dead, becomes lastDeadParticle
		if (ParticleObjectList[i]->getLife() <= 0.0f) {
			lastDeadParticle = i;
			return i;
		}
	}
	// If there are no dead particles, use the first one in the list
	lastDeadParticle = 0;
	return 0;
}

// Respawn the particle and give it a new random direction
void Game::respawnParticle(GameObject * particle)
{
	particle->scale = vec3(0.2);
	particle->setRotation(radians(rand() % (90)/1.0f), radians(rand() % (90) / 1.0f), radians(rand() % (90) / 1.0f));
	particle->setPositionVec3(vec3(((rand() % 100 + -50)/100.0f),0.5, ((rand() % 100 + -50) / 100.0f)));
	particle->resetLife();
	
}



/* -------------------
Particle Emitter
----------------------*/

void Game::init()
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

	// Load Meshes
	treeMesh = new MeshCollection();
	loadMeshFromFile("Models/tree.dae", treeMesh);

	grassMesh = new MeshCollection();
	loadMeshFromFile("Models/grasspatch.obj", grassMesh);

	lampMesh = new MeshCollection();
	loadMeshFromFile("Models/lamp.fbx", lampMesh);

	barrelMesh = new MeshCollection();
	loadMeshFromFile("Models/barrel.fbx", barrelMesh);

	tentMesh = new MeshCollection();
	loadMeshFromFile("Models/Tent.obj", tentMesh);

	rockMesh = new MeshCollection();
	loadMeshFromFile("Models/Rockfbx.fbx", rockMesh);

	fireMesh = new MeshCollection();
	loadMeshFromFile("Models/campfire.fbx", fireMesh);

	particleMesh = new MeshCollection();
	loadMeshFromFile("Models/lamp.fbx", particleMesh);

	// Load textures
	diffuseTextureID_Grass = loadTextureFromFile("Textures/dirttexture.png");
	diffuseTextureID_Barrel = loadTextureFromFile("Textures/barrel.png");
	diffuseTextureID_Lamp = loadTextureFromFile("Textures/lampred.png");
	diffuseTextureID_Rock = loadTextureFromFile("Textures/rockgrey.png");
	diffuseTextureID_Tent = loadTextureFromFile("Textures/tentblue.png");
	diffuseTextureID_Tree = loadTextureFromFile("Textures/tree2.png");
	diffuseTextureID_Campfire = loadTextureFromFile("Textures/campfire.jpg");
	diffuseTextureID_Fire = loadTextureFromFile("Textures/fire.png");
	specularTextureID = loadTextureFromFile("Textures/specmap.png");

	// Load shaders
	programID = LoadShaders("vertBlinnPhongPL.glsl", "fragBlinnPhongPL.glsl");
	programID_Fire = LoadShaders("vertTextured.glsl", "fragTextured.glsl");


	// Set up list of point lights
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,7.0f,0.0f) });
	PointLights.push_back({ glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(0.0f,7.0f,0.0f) });

	// Set up new game objects
	tree1 = new GameObject();
	tree1->giveMesh(treeMesh);
	TreeList.push_back(tree1);

	tree2 = new GameObject();
	tree2->giveMesh(treeMesh);
	TreeList.push_back(tree2);

	tree3 = new GameObject();
	tree3->giveMesh(treeMesh);
	TreeList.push_back(tree3);

	tree4 = new GameObject();
	tree4->giveMesh(treeMesh);
	TreeList.push_back(tree4);

	tree5 = new GameObject();
	tree5->giveMesh(treeMesh);
	TreeList.push_back(tree5);

	tree6 = new GameObject();
	tree6->giveMesh(treeMesh);
	TreeList.push_back(tree6);

	grass = new GameObject();
	grass->giveMesh(grassMesh);
	MiscObjectList.push_back(grass);

	barrel = new GameObject();
	barrel->giveMesh(barrelMesh);
	MiscObjectList.push_back(barrel);

	lamp = new GameObject();
	lamp->giveMesh(lampMesh);
	MiscObjectList.push_back(lamp);

	tent = new GameObject();
	tent->giveMesh(tentMesh);
	MiscObjectList.push_back(tent);

	rock = new GameObject();
	rock->giveMesh(rockMesh);
	MiscObjectList.push_back(rock);

	fire = new GameObject();
	fire->giveMesh(fireMesh);
	MiscObjectList.push_back(fire);

	// Set object scale and positions
	if (tree1) {
		tree1->scale = vec3(2.5);
		tree1->position = vec3(0, 0.5, -7);
	}
	if (tree2) {
		tree2->scale = vec3(2.5);
		tree2->position = vec3(5, 0.5, 7);
	}
	if (tree3) {
		tree3->scale = vec3(2.5);
		tree3->position = vec3(-5, 0, -7);
	}
	if (tree4) {
		tree4->scale = vec3(2.5);
		tree4->position = vec3(7, 0, 2);
	}
	if (tree5) {
		tree5->scale = vec3(2.5);
		tree5->position = vec3(-5, 0, 6);
	}
	if (tree6) {
		tree6->scale = vec3(2.5);
		tree6->setRotation(0, 0, 0);
		tree6->position = vec3(0, 0, 8);
	}
	if (grass) {
		grass->scale = vec3(0.1);
		grass->position = vec3(0, 0, 0);
		grass->setRotation(radians(-90.0f), 0, 0);
	}
	if (lamp) {
		lamp->scale = vec3(0.002);
		lamp->position = vec3(-3, 2.5, -4);
		lamp->setRotation(0, 0, 0);
	}
	if (barrel) {
		barrel->scale = vec3(0.02);
		barrel->position = vec3(-3, 1, -4);
		barrel->setRotation(0, 0, 0);
	}
	if (tent) {
		tent->scale = vec3(0.05);
		tent->position = vec3(6, 0.5, -4);
		tent->setRotation(radians(-90.0f), 0, radians(-70.0f));
	}
	if (rock) {
		rock->scale = vec3(0.5);
		rock->position = vec3(0, 1, 3);
	}
	if (fire) {
		fire->scale = vec3(1);
		fire->position = vec3(0, 1, 0);
		fire->setRotation(radians(-90.0f), 0, 0);
	}

	// Set up camera
	camera = new Camera();
	camera->setFoV(90);
	camera->setProjectionMatrix();
	camera->setFullscreenProjectionMatrix();
	camera->setViewMatrix();

	cameraPosition = camera->getPosition();

	// Set up input and controls
	input = new InputSetup();

	playerController = PlayerController(input, camera);

	input->joystickInit();

	// SDL Event structure, this will be checked in the while loop
	SDL_Event event;

	initParticles();
}

void Game::loop()
{

	init();

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

		inputEvents();

		update();
		
		render();
		
	}

	clean();
}

void Game::update()
{
	// Update camera position
	cameraPosition = camera->getPosition();

	// Update particle generator
	updateParticles(deltaTime);

	// Handle keyboard input
	playerController.keyboardControls(deltaTime);

	// Handle joystick input
	playerController.joystickControls();

	if (window->getIsFullscreen()){
		mat4 MVPMatrix = camera->getFullscreenProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
	}
	if (!window->getIsFullscreen()){
		// Calculate MVP matrix
		mat4 MVPMatrix = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;
	}

	// Changing camera pitch and yaw
	if (rotateCameraLeft == true){
		camera->increaseYaw(-pitchSpeed * deltaTime);
	}
	if (rotateCameraRight == true){
		camera->increaseYaw(pitchSpeed * deltaTime);
	}
	if (rotateCameraUp == true){
		camera->increasePitch(-yawSpeed * deltaTime);
	}
	if (rotateCameraDown == true){
		camera->increasePitch(yawSpeed * deltaTime);
	}

	// Strafing and moving towards or away from target
	if (moveCameraLeft == true){
		camera->moveXAxis(walkSpeed * deltaTime);
	}
	if (moveCameraRight == true){
		camera->moveXAxis(-walkSpeed * deltaTime);
	}
	if (moveCameraForward == true){
		camera->moveZAxis(walkSpeed * deltaTime);
	}
	if (moveCameraBack == true){
		camera->moveZAxis(-walkSpeed * deltaTime);
	}

	// Moving camera up/down on the y axis
	if (moveCameraUp == true){
		camera->moveYAxis(walkSpeed * deltaTime);
	}
	if (moveCameraDown == true){
		camera->moveYAxis(-walkSpeed * deltaTime);
	}

	// Update objects
	for (GameObject * obj : TreeList){
		obj->update();
	}

	for (GameObject * obj : MiscObjectList){
		obj->update();
	}

}

void Game::render()
{

	// Culls the clockwise facing side of the triangles
	glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);

	// Linking shaders
	glUseProgram(programID);


	// Get uniforms from shader
	GLuint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	GLuint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLuint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");

	GLint diffuseTextureLocation = glGetUniformLocation(programID, "diffuseTexture");
	GLint specularTextureLocation = glGetUniformLocation(programID, "specularTexture"); 
	
	GLint ambientMaterialColourLocation = glGetUniformLocation(programID, "ambientMaterialColour");
	GLint diffuseMaterialColourLocation = glGetUniformLocation(programID, "diffuseMaterialColour");
	GLint specularMaterialColourLocation = glGetUniformLocation(programID, "specularMaterialColour");
	GLint specularMaterialPowerLocation = glGetUniformLocation(programID, "specularMaterialPower");
	
	GLint ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	GLint diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	GLint specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");

	GLint directionalLightDiffuseColourLocation = glGetUniformLocation(programID, "directionalLight.diffuseColour");
	GLint directionalLightSpecularColourLocation = glGetUniformLocation(programID, "directionalLight.specularColour");

	GLint lightDirectionLocation = glGetUniformLocation(programID, "directionalLight.direction");

	GLint cameraPositionLocation = glGetUniformLocation(programID, "cameraPosition");

	GLint lightIntensityLocation = glGetUniformLocation(programID, "lightIntensity");

	
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

	// Send the uniforms across to shader for the MVP variables
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(camera->getProjectionMatrix()));

	// Send uniforms for Textures and Lighting across
	glUniform1i(diffuseTextureLocation, 0);
	glUniform1i(specularTextureLocation, 1);
	//glUniform1i(diffuseTextureTreeLocation, 2);

	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(ambientMaterialColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(specularMaterialColour));

	glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));

	glUniform1f(specularMaterialPowerLocation, specularMaterialPower);

	glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

	// Send uniform values for point lights
	for (int i = 0; i < PointLights.size(); i++)
	{
		glUniform4fv(pointLightDiffuseColourLocations[i], 1, value_ptr(PointLights[i].DiffuseColour));
		glUniform4fv(pointLightSpecularColourLocations[i], 1, value_ptr(PointLights[i].SpecularColour));
		glUniform3fv(pointLightPositionLocations[i], 1, value_ptr(PointLights[i].Position));
	}

	glUniform1i(numberOfPointLightsLocation, PointLights.size());

	glUniform4fv(directionalLightDiffuseColourLocation, 1, glm::value_ptr(diffuseLightColour));
	glUniform4fv(directionalLightSpecularColourLocation, 1, glm::value_ptr(specularLightColour));

	// Send uniform values for Light Intensity to be used for the flicker effect
	glUniform1f(lightIntensityLocation, lightIntensity);
	


	/*--------------------
	Light Flicker effect
	---------------------*/

	// Create a light flickering effect from the campfire
	flickerUpdate += (rand() % 10 + 1)* deltaTime;

	if (flickerUpdate > flickerThreshold){
		lightFlicker = true;
		flickerUpdate = 0;
	}

	if (lightFlicker == true){
		lightIntensity = (rand() % 3000 + 3000); //range + start point
		glUniform1f(lightIntensityLocation, lightIntensity);
		lightFlicker = false;
	}


	/*----------------
	Model Rendering
	----------------*/

	if (barrel){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(barrel->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Barrel);
		barrel->render();
	}

	if (lamp){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(lamp->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Lamp);
		lamp->render();
	}

	if (grass){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(grass->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Grass);
		grass->render();
	}

	if (tent){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(tent->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tent);
		tent->render();
	}

	if (rock){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(rock->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Rock);
		rock->render();
	}
	
	if (fire){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(fire->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Campfire);
		fire->render();
	}

	for (GameObject * obj : TreeList){
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(obj->modelMatrix));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Tree);
		obj->render();
	}

	for (GameObject * p : ParticleObjectList){
		// Linking shaders
		glUseProgram(programID_Fire);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTextureID_Fire);

		// Get uniforms from shader
		GLuint modelMatrixLocation = glGetUniformLocation(programID_Fire, "modelMatrix");
		GLuint viewMatrixLocation = glGetUniformLocation(programID_Fire, "viewMatrix");
		GLuint projectionMatrixLocation = glGetUniformLocation(programID_Fire, "projectionMatrix");

		// Send the uniforms across
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(p->modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(camera->getProjectionMatrix()));
		glUniform1i(diffuseTextureLocation, 0);
		
		p->render();
	}

	SDL_GL_SwapWindow(window->getWindow());

}

void Game::inputEvents()
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
					else if (event.caxis.value > 32000){
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

void Game::clean()
{
	glDeleteProgram(programID);
	glDeleteProgram(programID_Fire);

	glDeleteTextures(1, &diffuseTextureID);
	glDeleteTextures(1, &specularTextureID);
	glDeleteTextures(1, &diffuseTextureID_Grass);
	glDeleteTextures(1, &diffuseTextureID_Barrel);
	glDeleteTextures(1, &diffuseTextureID_Lamp);
	glDeleteTextures(1, &diffuseTextureID_Rock);
	glDeleteTextures(1, &diffuseTextureID_Tent);
	glDeleteTextures(1, &diffuseTextureID_Tree);
	glDeleteTextures(1, &diffuseTextureID_Campfire);
	glDeleteTextures(1, &diffuseTextureID_Fire);

	
	if (glSetup){
		delete glSetup;
		glSetup = nullptr;
	}

	if (window){
		delete window;
		window = nullptr;
	}

	if (treeMesh){
		delete treeMesh;
		treeMesh = nullptr;
	}

	if (lampMesh){
		delete lampMesh;
		lampMesh = nullptr;
	}

	if (rockMesh){
		delete rockMesh;
		rockMesh = nullptr;
	}

	if (tentMesh){
		delete tentMesh;
		tentMesh = nullptr;
	}

	if (fireMesh){
		delete fireMesh;
		fireMesh = nullptr;
	}
	
	if (grassMesh){
		delete grassMesh;
		grassMesh = nullptr;
	}

	if (barrelMesh){
		delete barrelMesh;
		barrelMesh = nullptr;
	}

	if (particleMesh){
		delete particleMesh;
		particleMesh = nullptr;
	}

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	//SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

}

