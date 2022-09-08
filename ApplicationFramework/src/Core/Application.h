#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Input/WindowState.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Rect.h"
#include <cstdint>
#include <chrono>

namespace Core {

	using namespace GMath;
	using namespace Input;

	class Application {

	private:
		GLFWwindow* m_Handle = nullptr;
		WindowState* m_WindowState = nullptr;

	public:
		Application(const uint16_t w, const uint16_t h, const char* title);
		~Application();

	public:
		void start();

		//////////////////////////////////////////////////
		// Window Specific Operations
		//////////////////////////////////////////////////
	public:
		GLFWwindow* getWindow() const;
		Recti getWindowBounds() const;
		void setWindowTitle(const char* str) const;
		void setWindowBounds(const Recti& bounds) const;

		//////////////////////////////////////////////////
		// Input Operations
		//////////////////////////////////////////////////
	public:
		int getKeyState(const int key) const;
		int getMouseState(const int button) const;

		//////////////////////////////////////////////////
		// Window Input Interface
		//////////////////////////////////////////////////
	public:
		WindowState& getWindowInput() const;
		const Vec2i& getWindowSize() const;
		const Vec2i& getWindowPos() const;
		const Vec2d& getMousePos() const;
		const Vec2d getMouseVelocity(const Vec2d& sens) const;
		const void setIsMouseLocked(const bool state);
		const Vec2d getScrollVelocity(const Vec2d& sens) const;
		const Input::Modifiers& getKeyboardModifiers() const;
		const bool isModifierSet(const Input::Modifier mod) const;

		//////////////////////////////////////////////////
		// Virtual Interface Operations
		//////////////////////////////////////////////////
	public:
		virtual void onCreate() = 0;
		virtual bool onUpdate(const double ts) = 0;
	};

}
