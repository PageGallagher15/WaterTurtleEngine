#include "Engine.h"

std::unique_ptr<Engine> Engine::engineInstance = nullptr;

Engine::Engine() 
	:window(nullptr), isRunning(false), fps(120)
{

}


Engine::~Engine()
{
	Shutdown();
}

Engine* Engine::GetInstance() {
	if (engineInstance.get() ==nullptr) {
		engineInstance.reset(new Engine);
	}
	return engineInstance.get();
}

bool Engine::Initialize(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();


	if (!window->Initialize (name_,  width_,  height_)) {
		Debug::FatalError("Window failed to Initialize", __FILE__, __LINE__);
		//std::cout << "Window failed to initialize" << std::endl;
		Shutdown();
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);

	Debug::Info("Everything Initialized properly", __FILE__, __LINE__);

	timer.Start();
	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("baseShader", "Engine/Shaders/vertexShader.glsl", "Engine/Shaders/fragmentShader.glsl");


	if (gameInterface) {
		if (!gameInterface->Initialize()) {
			Debug::FatalError("Failed to Initialize Game Interface", __FILE__, __LINE__);
			return isRunning = false;
		}
	}
	return isRunning = true;

}
void Engine::Run() {
	while (isRunning) {

		KeyboardInputManager::GetInstance()->Update();
		KeyboardInputManager::GetInstance()->UpdatePrevious();
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning) {
		Shutdown();
	}
}

bool Engine::GetIsRunning() {
	return isRunning;
}

void Engine::Update(const float deltaTime_) {

	//std::cout << "DeltaTime: " << deltaTime_ << std::endl;
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void Engine::Render() {
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render(); 
	}

	SDL_GL_SwapWindow(window->GetWindow());

}

void Engine::Shutdown() {
	delete window;
	window = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	SDL_Quit();
	exit(0);
}

void Engine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

glm::vec2 Engine::GetScreenSize() const {
	return glm::vec2(window->GetWidth(), window->GetHeight());

}

void Engine::NotifyOfMousePressed(int x_, int y_){

}

void Engine::NotifyOfMouseReleased(int x_, int y_, int buttonType_){
	CollisionHandler::GetInstance()->Update(glm::vec2(x_, y_), buttonType_);
}

void Engine::NotifyOfMouseMove(int x_, int y_){
	//Camera::GetInstance()->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);
}

void Engine::NotifyOfMouseScroll(int y_){
	//Camera::GetInstance()->ProcessMouseZoom(y_);
}

void Engine::ExitGame(){
	isRunning = false;
}
