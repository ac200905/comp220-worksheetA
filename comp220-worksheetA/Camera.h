#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
//#include "main.h"

#include "Window.h"

using namespace glm;

class Camera
{
public:
	Camera(float initFoV = 60, float initNearClip = 0.1, float initFarClip = 100);
	Camera(vec3 &Position, vec3 &Target, vec3 &UpVector, float initFoV = 60, float initNearClip = 0.1, float initFarClip = 100);
	//check this
	~Camera();

	void setViewMatrix();
	void setProjectionMatrix();
	void setFullscreenProjectionMatrix();

	mat4 getViewMatrix(){
		return viewMatrix;
	}

	mat4 getProjectionMatrix(){
		return projectionMatrix;
	}

	mat4 getFullscreenProjectionMatrix(){
		return projectionMatrix;
	}

	//Keep camera inside pitch constraints
	void checkPitchConstraints();

	//Calculate the camera's rotation, based on mouse position
	void calculateCameraRotation();


	//Specialised setters to increase pitch and yaw instead of just replacing with new values
	void increasePitch(float Pitch){
		pitch += Pitch;
	}

	void increaseYaw(float Yaw){
		yaw += Yaw;
	}

	void moveXAxis(float Position){
		setPosition(position - (normalize(cross(target,getUpVector()))* Position));
		setViewMatrix();
	}

	void moveZAxis(float Position){
		setPosition(position + (Position * target));
		setViewMatrix();
	}

	void moveYAxis(float Position){
		setPosition(position + (vec3(0, 1, 0) * Position));
		setViewMatrix();
	}

	vec3 getPosition(){
		return position;
	}

	vec3 getTarget(){
		return target;
	}

	vec3 getUpVector(){
		return upVector;
	}

	void setPosition(vec3 Position){
		Position.y = 3; // to simulate walking
		position = Position;
	}

	void setTarget(vec3 Target){
		target = Target;
	}

	void setPitch(float Pitch){
		pitch = Pitch;
	}

	void setYaw(float Yaw){
		yaw = Yaw;
	}

	void setFoV(float fov){
		FoV = fov;
	}

	


private:
	//Vertical field of view in degrees.
	float FoV;

	// Near clipping plane. Keep as big as possible, or you'll get precision issues.
	float nearClip;

	// Far clipping plane. Keep as little as possible.
	float farClip;

	// the position of your camera, in world space
	vec3 position;

	// where you want to look at, in world space
	vec3 target;

	//Orientation of camera, (0, 1, 0) is normal.
	vec3 upVector;

	mat4 viewMatrix;
	mat4 projectionMatrix;

	//Actually opposite direction to camera facing
	vec3 zAxis;

	vec3 xAxis;
	vec3 yAxis;


	//Yaw and pitch
	float pitch;
	float yaw;
};