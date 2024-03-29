#include "Game.h"



Game::Game() {

}


Game::~Game() {
	
}

bool Game::Initialize() {
	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->Initialize(100.0);
	
	//Player-----------------------------------------
	Model* playerModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", BASE_SHADER);
	//SceneGraph::GetInstance()->AddModel(playerModel);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(playerModel), "apple1");
	player = new Player(playerModel, glm::vec3(0.0f, -1.0f, 0.0f));
	//SceneGraph::GetInstance()->GetGameObject("apple1")->SetScale(glm::vec3(0.5f));

	//Dice--------------------------------------------
	/*Model* dice = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(dice);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(dice, glm::vec3(3.0f, 0.0f, 0.0f)));*/
	


	std::cout << "Object's bounding box: "<< std::endl;
	std::cout << "Min vert: " << glm::to_string(SceneGraph::GetInstance()->GetGameObject("apple1")->GetBoundingBox().minVert) << std::endl;
	std::cout << "Max vert: " << glm::to_string(SceneGraph::GetInstance()->GetGameObject("apple1")->GetBoundingBox().maxVert) << std::endl;

	return true;
}

void Game::Update(const float deltaTime_) {
	//SceneGraph::GetInstance()->Update(deltaTime_);
}

void Game::Render() {
	//SceneGraph::GetInstance()->Render(Camera::GetInstance());
	player->Render(Camera::GetInstance());
}