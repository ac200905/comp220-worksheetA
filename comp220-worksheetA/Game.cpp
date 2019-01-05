#include "Game.h"
#include <time.h>
#include <iostream>



Game::Game()
{
	
}
/*
struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle()
		: Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};
*/
Game::~Game()
{
}

// Gets unused particles and respawns new ones, then decreases particle life by delta time and updates position
void Game::updateParticles(GLfloat deltaTime)
{
	// Add new particles
	for (GLuint i = 0; i < numParticles; ++i)
	{
		int unusedParticle = firstUnusedParticle();
		respawnParticle(ParticleObjectList[unusedParticle]);
	}
	// Update all particles
	for (GLuint i = 0; i < amount; ++i)
	{
		GameObject * particle = ParticleObjectList[i];
		particle->decreaseLife(deltaTime); // reduce life
		if (particle->getLife() > 0.0f)
		{	// particle still alive: update particle
			vec3 currentPos = particle->getPosition();
			vec3 objectDirection = vec3(0,1,0); //up
			currentPos = currentPos + (objectDirection / speed); // increase the division to slow down the movement
			particle->setPositionVec3(currentPos);

			vec3 scaleBack = vec3(0.003f);
			vec3 currentScale = particle->getScale();
			currentScale = currentScale - scaleBack;
			particle->setScaleVec3(currentScale);

			//std::cout << to_string(particle->getScale()) << std::endl;
			//std::cout << to_string(particle->getPosition()) << std::endl;

		}
		//std::cout << i << std::endl;
		particle->update();
		
	}
}

void Game::initParticles()
{
	// Create the default amount of particle instances
	for (GLuint i = 0; i < amount; ++i)
	{
		//objectManager->createParticleObject("Model/star.obj", "Model/light3.png", 15.0f, 15.0f, -20.0f, vec3(0.0085f, 0.0085f, 0.0085f), vec3(1.0f, 1.0f, 0.0f), 0.5f, 0.0f, lightShader);
		particleMesh = new MeshCollection();
		loadMeshFromFile("Models/cube.fbx", particleMesh);

		//diffuseTextureID_Lamp = loadTextureFromFile("lampred.png");

		GameObject * particle = new GameObject();
		particle->giveMesh(particleMesh);
		particle->scale = vec3(0.2);
		particle->position = vec3(0, 2, 0);
		particle->setRotation(radians(-90.0f), 0, 0);
		particle->update();

		ParticleObjectList.push_back(particle);

		//std::cout << i << std::endl;
	}
}


GLuint Game::firstUnusedParticle()
{
	
	// Search from last used particle
	for (GLuint i = lastCheckedParticle; i < amount; ++i) {
		if (ParticleObjectList[i]->getLife() <= 0.0f) {
			lastCheckedParticle = i;
			return i;
		}
	}
	// Otherwise serach from the begining
	for (GLuint i = 0; i < lastCheckedParticle; ++i) {
		if (ParticleObjectList[i]->getLife() <= 0.0f) {
			lastCheckedParticle = i;
			return i;
		}
	}
	// If there are no dead particles use the first one in the list
	lastCheckedParticle = 0;
	return 0;
}

// Respawn the particle and give it a new random direction
void Game::respawnParticle(GameObject * particle)
{
	particle->scale = vec3(0.2);
	particle->setRotation(radians(rand() % (90)/1.0f), radians(rand() % (90) / 1.0f), radians(rand() % (90) / 1.0f));
	particle->setPositionVec3(vec3(((rand() % 100 + -50)/100.0f),0.5, ((rand() % 100 + -50) / 100.0f)));
	particle->resetLife();
	 //range + start point (float(rand() % 90))
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
	if (grass){
		grass->scale = vec3(0.1);
		grass->position = vec3(0, 0, 0);
		grass->setRotation(radians(-90.0f), 0, 0);
	}
	if (lamp){
		lamp->scale = vec3(0.002);
		lamp->position = vec3(-3, 2.5, -4);
		lamp->setRotation(0, 0, 0);
	}
	if (barrel){
		barrel->scale = vec3(0.02);
		barrel->position = vec3(-3, 1, -4);
		barrel->setRotation(0, 0, 0);
	}
	if (tent){
		tent->scale = vec3(0.05);
		tent->position = vec3(6, 0.5, -4);
		tent->setRotation(radians(-90.0f), 0, radians(-45.0f));
	}
	if (rock){
		rock->scale = vec3(0.5);
		rock->position = vec3(0, 1, 3);
	}
	if (fire){
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
		updateParticles(deltaTime);
		gameRender();
		
	}

	gameClean();
}

void Game::gameUpdate()
{
	// Index of the last particle
	GLuint lastUsedParticle;

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



	for (GameObject * obj : TreeList){
		obj->update();
	}

	for (GameObject * obj : MiscObjectList){
		obj->update();
	}

}

void Game::gameRender()
{

	// Materials
	glm::vec4 ambientMaterialColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 diffuseMaterialColour = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Light
	glm::vec4 ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularLightColour = glm::vec4(0.0f);

	float specularMaterialPower = 10000.0f;


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

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, specularTextureID);

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
	
	// Create a light flickering effect from the campfire
	flickerThreshold += (rand() % 10 + 1);

	if (flickerThreshold > 30)
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
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(camera->getProjectionMatrix()));

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(p->modelMatrix));
		glUniform1i(diffuseTextureLocation, 0);
		
		p->render();
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

void Game::gameClean()
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
	
	if (grassMesh)
	{
		delete grassMesh;
		grassMesh = nullptr;
	}

	if (barrelMesh)
	{
		delete barrelMesh;
		barrelMesh = nullptr;
	}

	if (particleMesh)
	{
		delete particleMesh;
		particleMesh = nullptr;
	}

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	//SDL_DestroyWindow(mainWindow);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

}

