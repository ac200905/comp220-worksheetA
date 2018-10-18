#include "main.h"


Camera::Camera(float initFoV, float initNearClip, float initFarClip)
{
	//Initialise the variables
	position = vec3(8, 4, 6);
	target = vec3(0, 0, 0);
	upVector = vec3(0, 1, 0);
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	//Generate the matricies
	setViewMatrix();
	setProjectionMatrix();
}

Camera::Camera(vec3 &cameraPosition, vec3 &cameraTarget, vec3 &UpVector, float initFoV, float initNearClip, float initFarClip)
{
	//Initialise the variables
	position = cameraPosition;
	target = cameraTarget;
	upVector = UpVector;
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	//Generate the matricies
	setViewMatrix();
	setProjectionMatrix();
}

Camera::~Camera()
{
}

void Camera::setViewMatrix()
{
	viewMatrix = lookAt
	(
		position, // the position of your camera, in world space
		target, // where you want to look at, in world space
		upVector // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
	);
}

void Camera::setProjectionMatrix()
{
	projectionMatrix = perspective
	(
		radians(FoV), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		(float)global::SCREEN_HEIGHT / (float)global::SCREEN_WIDTH,   // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960
		nearClip, // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		farClip // Far clipping plane. Keep as little as possible.
	);
}