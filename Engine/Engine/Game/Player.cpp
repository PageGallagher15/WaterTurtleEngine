#include "Player.h"

void Player::Movement(float deltaTime_)
{
	Camera::GetInstance()->SetPosition(glm::vec3(this->GetPosition().x, this->GetPosition().y, Camera::GetInstance()->GetPosition().z));

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A)) 
	{
		if (!GetGravity()) {
			SetSpeed(-1.0f);
		}
		else
		{
			SetSpeed(-1.0f);
		}
	}

	else if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D)) 
	{
		if (!GetGravity()) 
		{
			SetSpeed(1.0f);
		}
		else 
		{
			SetSpeed(1.0f);
		}
	}
	SetPostition(GetPosition() * deltaTime_);
	if (GetGravity()) 
	{
		SetVelocity(glm::vec3(0.0f, GetVelocity().y, 0.0f));
	}
	else 
	{
		SetVelocity(glm::vec3(0.0f));
	}
}

Player::Player(Model* model_, glm::vec3 position_) : Entity (model_,position_, true)
{
	particle = new Model("Apple.obj", "Apple.mtl", ShaderHandler::GetInstance()->GetShader("alphaShader"));
	particle->GetMesh(0)->transparency = 0.3f;
	SetVelocity(glm::vec3(0.0f));
	//window = Engine::GetInstance()->Engine::GetWindow();
}


Player::~Player()
{
}

void Player::Update(float deltaTime_)
{
	if (GetGravity())
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + (GetVelocity().y * deltaTime_) + (0.5f * (GetAcceleration().y * 4) * (deltaTime_ * deltaTime_)), GetVelocity().z));
	Movement(deltaTime_);
}

void Player::Render(Camera* camera_)
{
	this->GetModel()->Render(camera_);

}