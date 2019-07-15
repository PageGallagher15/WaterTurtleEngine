#ifndef ENGINE_H
#define ENGINE_H

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "../Graphics/ShaderHandler.h"
#include "../Rendering/3D/Triangle.h"
#include "../Rendering/3D/Square.h"
#include "../Rendering/3D/Cube.h"
#include "../Graphics/TextureHandler.h"
#include "../Camera/Camera.h"
#include "../Rendering/3D/GameObject.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"
#include "../Events/KeyboardInputManager.h"


#include <memory>

class Engine

{
public:

	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator = (const Engine&) = delete;
	Engine& operator = (Engine&&) = delete;
	


	bool Initialize(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
	void SetGameInterface(GameInterface* gameInterface_);
	
	static Engine* GetInstance();

	glm::vec2 GetScreenSize() const;

	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);
	void ExitGame(); 

private:
	Engine();
	~Engine();
	void Shutdown();
	void Update(const float deltaTime_);
	void Render();

	static std::unique_ptr<Engine> engineInstance;
	friend std::default_delete<Engine>;

	Window* window;
	Timer timer;
	GameInterface* gameInterface;

	bool isRunning;
	unsigned int fps;



};

#endif 

