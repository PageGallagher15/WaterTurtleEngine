#ifndef ENTITY_H
#define ENTITY_H

#include "../Engine/Events/KeyboardInputManager.h"
#include "../Engine/Rendering/3D/GameObject.h"

class Entity : public GameObject
{
public:
	Entity(Model* model_, glm::vec3 position_, bool isGravity_);
	~Entity();

	void Update(const float deltaTime_);

	void SetSpeed(float speed_);
	float GetSpeed();

	void SetGravity(bool isGravity_);
	bool GetGravity();

	void SetVelocity(glm::vec3 velocity_);
	glm::vec3 GetVelocity();

	void SetAcceleration(glm::vec3 accleration_);
	glm::vec3 GetAcceleration();


private: 

	bool gravity;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float speed;
};

#endif 

