#include "Player.h"

void Player::Movement(float deltaTime_)
{
	Camera::GetInstance()->SetPosition(glm::vec3(this->GetPosition().x, this->GetPosition().y, Camera::GetInstance()->GetPosition().z));
	if (!isDead) {
		if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A) && canLeft)
		{
			if (!GetGravity()) {
				SetSpeed(-1.0f);
			}
			else
			{
				SetSpeed(-1.0f);
			}
			if (isFacingRight) {
				turningLeft = true;
				turningRight = false;
				isFacingRight = false;
			}
			if (canRight == false) {
				canRight = true;
			}
		}

		else if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D) && canRight)
		{
			if (!GetGravity())
			{
				SetSpeed(1.0f);
			}
			else
			{
				SetSpeed(1.0f);
			}
			if (!isFacingRight) {
				turningRight = true;
				turningLeft = false;
				isFacingRight = true;
			}
			if (canLeft == false) {
				canLeft = true;
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
}

Player::Player(Model* model_, glm::vec3 position_) : Entity (model_,position_, true)
{
	//SetTag("Player");
	particle = new Model("Apple.obj", "Apple.mtl", ShaderHandler::GetInstance()->GetShader("alphaShader"));
	particle->GetMesh(0)->transparency = 0.3f;
	SetVelocity(glm::vec3(0.0f));
	SetAcceleration(glm::vec3(0.0f, -9.8f * gravityS, 0.0f));
	isDead = false;
	canLeft = true;
	canRight = true;
	//window = Engine::GetInstance()->Engine::GetWindow();
}


Player::~Player()
{
}

void Player::Update(float deltaTime_)
{
	if (GetGravity())
		SetVelocity(glm::vec3(GetVelocity().x, GetVelocity().y + (GetVelocity().y * deltaTime_) + (0.5f * (GetAcceleration().y * 4) * (deltaTime_ * deltaTime_)), GetVelocity().z));

	if (turningLeft)
	{
		SetAngle(GetAngle() - (deltaTime_ * 10));
		if (GetAngle() <= -1.575)
		{
			SetAngle(-1.575);
			turningLeft = false;
		}
	}
	if (turningRight)
	{
		SetAngle(GetAngle() + (deltaTime_ * 10));
		if (GetAngle() >= 1.575)
		{
			SetAngle(glm::radians(90.0f));
			turningRight = false;
		}
	}
	Movement(deltaTime_);
}

void Player::Render(Camera* camera_)
{
	this->GetModel()->Render(camera_);

}