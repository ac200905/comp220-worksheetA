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

using namespace glm;

class Game
{
public:
	Game();
	~Game();

	void particleGen();

	void updateParticles(GLfloat deltaTime);

	GLuint firstUnusedParticle();

	void initParticles();

	void respawnParticle(GameObject * particle);

	void gameInit();

	void gameLoop();

	void gameRender();

	void gameUpdate();

	void gameInputEvents();

	void gameClean();

	bool running = true;

	bool lightFlicker = true;

	int flickerThreshold;

	int frameDelay;

	int amount = 10;

	GLuint newParticles = 10;

	float speed = 100.0f;

	// Index of the last particle
	GLuint lastUsedParticle = 0;

private:

	float deltaTime;
	float lastFrame;

	float lightIntensity;

	float turnspeed;
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
	GameObject* rock1;
	GameObject* barrel;
	GameObject* lamp;
	GameObject* tent;
	GameObject* fire;

	std::vector<GameObject*> TreeList;
	std::vector<GameObject*> ParticleObjectList;

	GLuint diffuseTextureID_Grass;
	GLuint diffuseTextureID_Barrel;
	GLuint diffuseTextureID_Lamp;
	GLuint diffuseTextureID_Tent;
	GLuint diffuseTextureID_Rock;
	GLuint diffuseTextureID_Tree;
	GLuint diffuseTextureID_Campfire;
	GLuint diffuseTextureID;
	GLuint specularTextureID;



	GLuint programID;

	GLuint MVPLocation;

	mat4 modelMatrix;

	mat4 MVPMatrix;

	vec4 ambientMaterialColour;

	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;

	GLint baseTextureLocation;

	vec3 cameraPosition;

};