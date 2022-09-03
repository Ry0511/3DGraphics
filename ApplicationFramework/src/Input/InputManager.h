#pragma once

#include "GLFW/glfw3.h"
#include "ActionEvent.h"
#include <queue>

namespace Input {
	class InputManager {
		static InputManager* s_Instance;
		std::queue<ActionEvent> m_EventQueue{};

	private:
		InputManager() = default;

		static void keyCallbackImpl(GLFWwindow* p, int btn, int act, int scan, int mods);
		static void MouseCallbackImpl(GLFWwindow* p, int btn, int act, int mods);

	public:
		static InputManager* const getInstance();

		void addWindow(GLFWwindow* window);
		const bool hasEvent() const;
		const ActionEvent& head();
	};
}

