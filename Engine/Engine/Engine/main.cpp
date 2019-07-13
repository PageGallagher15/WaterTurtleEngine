#include "Core/Engine.h"
#include "../Game/Game.h"

int main(int argc, char* args[]) {
	//Engine::GetInstance()->Initialize();
	//Version 1
	//if (!engine->Initialize("GAME 301 Engine", 800, 600)) {
	//	std::cout << "Engine failed to initialize" << std::endl;
	//	//engine->Shutdown();
	//	delete engine;
	//	engine = nullptr;
	//	return 0;
	//}

	Engine::GetInstance()->SetGameInterface(new Game());
	Engine::GetInstance()->Initialize("GAME 301 Engine", 800, 600);
	Engine::GetInstance()->Run();


	return 0;


}