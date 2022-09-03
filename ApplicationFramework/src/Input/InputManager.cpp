#include "InputManager.h"

#include <iostream>
#include <format>

namespace Input {

	//////////////////////////////////////////////////
	// GLFW EVENT CALLBACKS
	//////////////////////////////////////////////////

	void InputManager::keyCallbackImpl(GLFWwindow* p, int key, int scan, int act, int mods) {
		s_Instance->m_EventQueue.emplace(key, act, mods, scan);
	}
	void InputManager::MouseCallbackImpl(GLFWwindow* p, int btn, int act, int mods) {
		s_Instance->m_EventQueue.emplace(btn, act, mods, -1);
	}

	//////////////////////////////////////////////////
	// INPUT MANAGER SINGLETON ACCESS
	//////////////////////////////////////////////////

	InputManager* InputManager::s_Instance = new InputManager();

	InputManager* const InputManager::getInstance() {
		return s_Instance;
	}

	//////////////////////////////////////////////////
	// INPUT MANAGER OPERATIONS
	//////////////////////////////////////////////////

	void InputManager::addWindow(GLFWwindow* window) {
		glfwSetKeyCallback(window, keyCallbackImpl);
		glfwSetMouseButtonCallback(window, MouseCallbackImpl);
	}

	const bool InputManager::hasEvent() const {
		return !m_EventQueue.empty();
	}

	const Input::ActionEvent& InputManager::head() {
		const auto& e = m_EventQueue.front();
		m_EventQueue.pop();
		return e;
	}

}