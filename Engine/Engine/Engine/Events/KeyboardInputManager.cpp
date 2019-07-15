#include "KeyboardInputManager.h"

std::unique_ptr<KeyboardInputManager> KeyboardInputManager::kimInstance = nullptr;

KeyboardInputManager::KeyboardInputManager()
{
	keyboardState = SDL_GetKeyboardState(&keyLength);
	previousKeyboardState = new Uint8[keyLength];
	memcpy(previousKeyboardState, keyboardState, keyLength);
}


KeyboardInputManager::~KeyboardInputManager()
{
	delete[] previousKeyboardState;
	previousKeyboardState = nullptr;
}

KeyboardInputManager* KeyboardInputManager::GetInstance() 
{
	if (kimInstance.get() == nullptr) 
	{
		kimInstance.reset(new KeyboardInputManager);
	}

	return kimInstance.get();
}

bool KeyboardInputManager::KeyDown(SDL_Scancode scancode_)
{
	return keyboardState[scancode_];
}

bool KeyboardInputManager::KeyPressed(SDL_Scancode scancode_)
{
	return !previousKeyboardState[scancode_] && keyboardState[scancode_];
}

bool KeyboardInputManager::KeyReleased(SDL_Scancode scancode_)
{
	return previousKeyboardState[scancode_] && !keyboardState[scancode_];
}

void KeyboardInputManager::Update()
{
	keyboardState = SDL_GetKeyboardState(NULL);
}

void KeyboardInputManager::UpdatePrevious()
{
	memcpy(previousKeyboardState, keyboardState, keyLength);
}