#ifndef PLAYER_H
#define PLAYER_H


#include "../Engine/Events/KeyboardInputManager.h"
#include "../Engine/Core/Timer.h"
#include "Entity.h"


class Player : public Entity
{
public:
	Player(Model* model_, glm::vec3 position_);
	~Player();

	void Update(float deltaTime_);
	void Render(Camera* camera_);

	void Movement(float deltaTime_);

private: 
	float speed = 2.0f;
	float gravityS = 2.5f;
	Model* particle;
};

#endif
