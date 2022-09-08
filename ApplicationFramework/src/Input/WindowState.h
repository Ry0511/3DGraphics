#pragma once

#include "GLFW/glfw3.h"
#include "../Math/Vec2.h"

namespace Input {

	//
	// Not sure if GLFW multithreading will be an issue for some of the internal data.
	//

	using namespace GMath;

	//////////////////////////////////////////////////
	// Keyboard Modifiers
	//////////////////////////////////////////////////

	enum class Modifier : int {
		SHIFT = GLFW_MOD_SHIFT, ALT = GLFW_MOD_ALT,
		CTRL = GLFW_MOD_CONTROL, SUPER = GLFW_MOD_SUPER,
		NUMLOCK = GLFW_MOD_NUM_LOCK, CAPS = GLFW_MOD_CAPS_LOCK
	};

	struct Modifiers {
		int modifiers = 0;
		void eventImpl(const int mods) { modifiers = mods; };
		const bool isModifier(const Modifier mod) const {
			return modifiers & static_cast<int>(mod);
		};
	};

	//////////////////////////////////////////////////
	// Mutable Window Input State
	//////////////////////////////////////////////////

	class WindowState {

	private:
		GLFWwindow* m_WindowHandle;
		Vec2i m_WindowSize{};
		Vec2i m_WindowPos{};

		Vec2d m_MousePos{0,0};
		Vec2d m_MouseScrollPos{0,0};

		bool m_IsCursorPosLocked = false;

		Modifiers m_Modifiers;

	public:
		WindowState(GLFWwindow* window);

	private:
		void setWindowSize(const Vec2i& size) { m_WindowSize = size; };
		void setWindowPos(const Vec2i& pos) { m_WindowPos = pos; };
		void setMousePos(const Vec2d& pos) { m_MousePos = pos; };
		void setMouseScrollPos(const Vec2d& pos) { m_MouseScrollPos = pos; };

		Vec2d getMousePosImpl() const;

	public:
		void setIsMouseLocked(const bool isLocked) { m_IsCursorPosLocked = isLocked; };

	public:
		const Vec2i& getWindowSize() const { return m_WindowSize; };
		const Vec2i& getWindowPos() const { return m_WindowPos; };

		const Vec2d& getMousePos() const { return m_MousePos; };
		const Vec2d getMouseVelocity(const Vec2d& sens) const;

		const Vec2d& getMouseScrollPos() const { return m_MouseScrollPos; };
		const Vec2d getMouseScrollVelocity(const Vec2d& scrollSens);

		const bool isCursorLocked() const { return m_IsCursorPosLocked; };
		Modifiers& getActionModifiers() { return m_Modifiers; };
	};
}

