#include "Entity.h"



Entity::Entity(Model* model_, glm::vec3 position_, bool isGravity_) : GameObject(model_, position_)
{
	gravity = isGravity_;
	velocity = glm::vec3(0);
	acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
}


Entity::~Entity()
{
}

void Entity::SetGravity(bool isGravity_) {
	gravity = isGravity_;
}

bool Entity::GetGravity() {
	return gravity;
}

void Entity::SetSpeed(float speed_) {
	speed = speed_;
}

float Entity::GetSpeed() {
	return speed;
}

void Entity::SetVelocity(glm::vec3 velocity_) {
	velocity = velocity_;
}

glm::vec3 Entity::GetVelocity() {
	return velocity;
}

void Entity::SetAcceleration(glm::vec3 accleration_) {
	acceleration = accleration_;
}

glm::vec3 Entity::GetAcceleration() {
	return acceleration;
}