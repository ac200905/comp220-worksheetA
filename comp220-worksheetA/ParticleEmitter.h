#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shaders.h"
#include "Texture.h"
#include "GameObject.h"
#include "Game.h"
/*
class ParticleEmitter
{
public:
	// Constructor
	ParticleEmitter(GLuint amountOfParticles, ObjectManager* manager, Shader* shader);

	~ParticleEmitter();
	// Update particles
	void Update(GLfloat dt, GameObject &object, GLuint newParticles);

private:
	// Will be the default amount of particles
	GLuint amount;
	// Speed at which the particle will move, higher is slower
	float speed = 100.0f;
	// For pointing to the active objectManager and lightShader
	ObjectManager * objectManager;
	Shader* lightShader;
	// List of all particle objects
	std::vector<GameObject*> ParticleObjectList;
	// Returns the first Particle index that's currently unused
	GLuint firstUnusedParticle();
	// Respawns particle
	void respawnParticle(GameObject * particle, GameObject & object);
	void init();
};
*/