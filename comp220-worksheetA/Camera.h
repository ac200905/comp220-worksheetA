#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

class Camera
{
public:
	Camera(float initFoV = 60, float initNearClip = 0.1, float initFarClip = 100);
	Camera(vec3 &cameraPosition, vec3 &cameraTarget, vec3 &UpVector, float initFoV = 60, float initNearClip = 0.1, float initFarClip = 100);

	~Camera();

	void setViewMatrix();
	void setProjectionMatrix();

	mat4 getViewMatrix()
	{
		return viewMatrix;
	}

	mat4 getProjectionMatrix()
	{
		return projectionMatrix;
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
};