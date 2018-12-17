#include "ParticleEmitter.h"
/*
ParticleEmitter::ParticleEmitter(GLuint amountOfParticles, ObjectManager* manager, Shader* shader)
{
	amount = amountOfParticles;
	objectManager = manager;
	lightShader = shader;
	init();
}

ParticleEmitter::~ParticleEmitter()
{
}

// Gets unused particles and respawns new ones, then decreases particle life by delta time and updates position
void ParticleEmitter::Update(GLfloat deltaTime, GameObject & object, GLuint newParticles)
{
	// Add new particles
	for (GLuint i = 0; i < newParticles; ++i)
	{
		int unusedParticle = firstUnusedParticle();
		respawnParticle(objectManager->GetParticleObjectList()[unusedParticle], object);
	}
	// Update all particles
	for (GLuint i = 0; i < this->amount; ++i)
	{
		GameObject * p = objectManager->GetParticleObjectList()[i];
		p->DecreaseLife(deltaTime); // reduce life
		if (p->GetLife() > 0.0f)
		{	// particle is alive, thus update
			vec3 currentPos = p->GetPosition();
			vec3 objectsDirection = p->GetRandomNormal();
			currentPos = currentPos + (objectsDirection / speed); // increase the division to slow down the movement
			p->SetPositionVec3(currentPos);
		}
		p->Update(deltaTime);
	}
}

void ParticleEmitter::init()
{
	// Create the default amount of particle instances
	for (GLuint i = 0; i < amount; ++i)
	{
		objectManager->createParticleObject("Model/star.obj", "Model/light3.png", 15.0f, 15.0f, -20.0f, vec3(0.0085f, 0.0085f, 0.0085f), vec3(1.0f, 1.0f, 0.0f), 0.5f, 0.0f, lightShader);
		MeshCollection * Meshes = new MeshCollection();
		loadMeshesFromFile(fileLocation, Meshes);

		textureID = loadTextureFromFile(textureLocation);

		GameObject * GO = new GameObject();
		GO->SetPosition(posX, posY, posZ);
		GO->SetMesh(Meshes);
		GO->SetScale(scale);
		GO->setRotationAxis(rotationAxis);
		GO->setRotationSpeed(speed);
		GO->SetScaleFactor(scaleFactor);
		GO->setIsParticle(true);
		GO->setWithPlayer(true);
		GO->SetShader(shader);
		GO->SetDiffuseTexture(textureID);
		ParticleObjectList.push_back(GO);

		lampMesh = new MeshCollection();
		loadMeshFromFile("lamp.fbx", lampMesh);
	}
}

// Stores the index of the last particle
GLuint lastUsedParticle = 0;
GLuint ParticleEmitter::firstUnusedParticle()
{
	// Search from last used particle
	for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
		if (objectManager->GetParticleObjectList()[i]->GetLife() <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise serach from the begining
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (objectManager->GetParticleObjectList()[i]->GetLife() <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// If there are no dead particles use the first one in the list
	lastUsedParticle = 0;
	return 0;
}

// Respawn the particle and give it a new random direction
void ParticleEmitter::respawnParticle(GameObject * particle, GameObject & object)
{
	particle->SetPositionVec3(object.GetPosition());
	particle->ResetLife();
	particle->RandomNormal();
}
*/