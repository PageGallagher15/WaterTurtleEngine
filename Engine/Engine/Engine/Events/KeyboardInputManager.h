#ifndef KEYBOARDINPUTMANAGER_H
#define KEYBOARDINPUTMANAGER_H

#include <SDL.h>
#include <memory>

class KeyboardInputManager
{
public:

	KeyboardInputManager(const KeyboardInputManager&) = delete;
	KeyboardInputManager(KeyboardInputManager&&) = delete;
	KeyboardInputManager& operator = (const KeyboardInputManager&) = delete;
	KeyboardInputManager& operator = (KeyboardInputManager&&) = delete;

	static KeyboardInputManager* GetInstance();
	bool KeyDown(SDL_Scancode scanCode_);
	bool KeyPressed(SDL_Scancode scanCode_);
	bool KeyReleased(SDL_Scancode scanCode_);
	void Update();
	void UpdatePrevious();

private:
	KeyboardInputManager();
	~KeyboardInputManager();

	static std::unique_ptr<KeyboardInputManager> kimInstance;
	friend std::default_delete<KeyboardInputManager>;
	Uint8* previousKeyboardState;
	const Uint8* keyboardState;
	int keyLength;
};

#endif