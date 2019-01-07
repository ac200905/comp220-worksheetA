#pragma once
#include <SDL.h>
#include <string>
#include "Globals.h"
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "shaders.h"
#include "Window.h"
#include "Camera.h"
#include "GLSetup.h"
#include "Vertex.h"
#include "Texture.h"
#include "InputSetup.h"
#include "PlayerController.h"
#include "Model.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Timer.h"
#include "Light.h"
#include "glm/ext.hpp"

using namespace glm;

class Game
{
public:
	Game();
	~Game();


	void updateParticles(GLfloat deltaTime);

	void initParticles();

	void respawnParticle(GameObject * particle);

	void init();

	void loop();

	void render();

	void update();

	void inputEvents();

	void clean();

	bool running = true;

	
	
private:

	bool lightFlicker = true;

	int flickerThreshold = 600;

	int flickerUpdate;

	int frameDelay;

	GLuint numParticles = 40;

	// Higher value means a slower particle speed
	float particleSpeed = 300.0f;

	GLuint findDeadParticle();

	// Index of the last particle
	GLuint lastDeadParticle = 0;

	float deltaTime;
	float lastFrame;

	float pitchSpeed = 0.1f;
	float yawSpeed = 0.1f;
	float walkSpeed = 0.005f;

	float lightIntensity;

	vec3 objectDirection = vec3(0, 1, 0); //up
	vec3 scaleBack = vec3(0.0002f);

	//std::map<std::string, bool> ControlActions;
	//ControlActions["rotateCameraLeft"] = false;

	//detect buttom press
	//ControlActions["rotateCameraLeft"] = true;

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

	// Create SDL window
	Window *window;
	//SDL_Window* mainWindow;

	// Initalise Open_GL and GLEW
	GLSetup *glSetup;
	// Get Open_GL context.
	//SDL_GLContext gl_Context;

	SDL_Event event;

	MeshCollection * particleMesh;
	MeshCollection * treeMesh;
	MeshCollection * grassMesh;
	MeshCollection * barrelMesh;
	MeshCollection * lampMesh;
	MeshCollection * tentMesh;
	MeshCollection * rockMesh;
	MeshCollection * fireMesh;

	InputSetup* input;

	PlayerController playerController;

	Camera* camera;

	GameObject* particle;
	GameObject* grass;
	GameObject* tree1;
	GameObject* tree2;
	GameObject* tree3;
	GameObject* tree4;
	GameObject* tree5;
	GameObject* tree6;
	GameObject* rock;
	GameObject* barrel;
	GameObject* lamp;
	GameObject* tent;
	GameObject* fire;

	std::vector<GameObject*> TreeList;
	std::vector<GameObject*> MiscObjectList;
	std::vector<GameObject*> ParticleObjectList;
	std::vector<PointLight> PointLights;

	GLuint diffuseTextureID_Grass;
	GLuint diffuseTextureID_Barrel;
	GLuint diffuseTextureID_Lamp;
	GLuint diffuseTextureID_Tent;
	GLuint diffuseTextureID_Rock;
	GLuint diffuseTextureID_Tree;
	GLuint diffuseTextureID_Campfire;
	GLuint diffuseTextureID_Fire;
	GLuint diffuseTextureID;
	GLuint specularTextureID;



	GLuint programID;
	GLuint programID_Fire;

	GLuint MVPLocation;

	mat4 modelMatrix;

	mat4 MVPMatrix;

	// Materials
	vec4 ambientMaterialColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 diffuseMaterialColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	vec4 specularMaterialColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Light
	vec4 ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 specularLightColour = vec4(0.0f);

	float specularMaterialPower = 10000.0f;

	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;

	GLint baseTextureLocation;

	vec3 cameraPosition;

};