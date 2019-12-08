#pragma once

namespace Input
{
	class InputManager final
	{
	public:
		InputManager() = delete;
		InputManager(const InputManager& p_other) = delete;
		InputManager(InputManager&& p_other) = delete;
		~InputManager() = default;

		/**
		 * @brief Returns true if the key in parameter is currently pressed
		 * @param p_key  The key to check
		 * @return true of false
		 */
		static bool IsKeyPressed(const char p_key);

		InputManager operator=(const InputManager& p_other) = delete;
		InputManager operator=(InputManager&& p_other) = delete;
	};
}