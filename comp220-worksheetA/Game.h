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

	void gameInit();

	void gameLoop();

	void gameRender();

	void gameUpdate();

	void gameInputEvents();

	void gameClean();

	bool running = true;




private:

	float deltaTime;
	float lastFrame;

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

	MeshCollection * treeMesh;
	MeshCollection * fireMesh;

	InputSetup* input;

	PlayerController playerController;

	Camera* camera;

	GameObject* tree1;
	GameObject* tree2;
	GameObject* fire;

	GLuint diffuseTextureID_Tree;
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