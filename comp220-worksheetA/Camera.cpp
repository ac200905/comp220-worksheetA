#include "Camera.h"



Camera::Camera(float initFoV, float initNearClip, float initFarClip)
{
	//Initialise the variables
	position = vec3(-10, 3, 0);
	target = vec3(0, 0, 0);
	upVector = vec3(0, 1, 0);
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	//Generate the matricies
	setViewMatrix();
	setProjectionMatrix();
	setFullscreenProjectionMatrix();

	zAxis = normalize(position - target); // camera forward
	xAxis = normalize(cross(upVector, zAxis)); // Camera right
	yAxis = cross(zAxis, xAxis); // camera up

	pitch = 25;
	yaw = 0;
}

Camera::Camera(vec3 &Position, vec3 &Target, vec3 &UpVector, float initFoV, float initNearClip, float initFarClip)
{
	//Initialise the variables
	position = Position;
	target = Target;
	upVector = UpVector;
	FoV = initFoV;
	nearClip = initNearClip;
	farClip = initFarClip;

	//Generate the matricies
	setViewMatrix();
	setProjectionMatrix();
	setFullscreenProjectionMatrix();

	zAxis = normalize(position - target);
	xAxis = normalize(cross(upVector, zAxis));
	yAxis = cross(zAxis, xAxis);

	pitch = 0;
	yaw = 0;
}

Camera::~Camera()
{
}

void Camera::setViewMatrix()
{
	viewMatrix = lookAt
	(
		position, // the position of your camera, in world space
		position + target, // where you want to look at, in world space
		upVector // probably glm::vec3(0,1,0)
	);
}

void Camera::setProjectionMatrix()
{
	projectionMatrix = perspective
	(
		radians(FoV), // The horizontal Field of View.
		(float)global::SCREEN_WIDTH / (float)global::SCREEN_HEIGHT,   // Aspect Ratio. Depends on the window size.
		nearClip, // Near clipping plane.
		farClip // Far clipping plane. For objects in the distance.
	);
}

void Camera::setFullscreenProjectionMatrix()
{
	projectionMatrix = perspective
	(
		radians(FoV), // The horizontal Field of View.
		(float)global::FULLSCREEN_WIDTH / (float)global::FULLSCREEN_HEIGHT,   // Aspect Ratio. Depends on the window size.
		nearClip, // Near clipping plane.
		farClip // Far clipping plane. For objects in the distance.
	);
}

void Camera::checkPitchConstraints()
{
	//Constrain upwards view
	if (pitch > 89.0f)
		pitch = 89.0f;

	//Constrain downwards view
	if (pitch < -89.0f)
		pitch = -89.0f;
}

void Camera::calculateCameraRotation()
{
	vec3 front;
	vec3 direction;
	// x and z axis deal with yaw (side to side)
	// y deals with pitch (up and down)
	//front.x = cos(radians(yaw)) * sin(radians(pitch));
	//front.y = cos(radians(pitch)) * -1; // -1 to invert pitch in game
	//front.z = sin(radians(yaw)) * sin(radians(pitch));

	direction.x = cos(radians(pitch)) * cos(radians(yaw));
	direction.y = sin(radians(pitch)) * -1; // -1 to invert pitch in game
	direction.z = cos(radians(pitch)) * sin(radians(yaw));

	target = normalize(direction);
	setViewMatrix();
}