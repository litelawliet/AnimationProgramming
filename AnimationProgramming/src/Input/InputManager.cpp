#include <Input/InputManager.h>
#include <Windows.h>

bool Input::InputManager::IsKeyPressed(const char p_key)
{
	if (GetKeyState(p_key) & 0x8000)
	{
		return true;
	}

	return false;
}
