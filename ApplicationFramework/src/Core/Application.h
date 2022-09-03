#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Input/InputManager.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Math/Rect.h"
#include <cstdint>
#include <chrono>

namespace Core {

	using namespace GMath;
	using namespace Input;

	class Application {

		GLFWwindow* m_Handle = nullptr;

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
		Vec2d getMousePos() const;
		Recti getWindowBounds() const;
		int getKeyState(const int key) const;
		int getMouseState(const int button) const;
		void setWindowTitle(const char* str) const;
		void setWindowBounds(const Recti& bounds) const;

		//////////////////////////////////////////////////
		// Event Polling Operations
		//////////////////////////////////////////////////
	public:
		const bool hasInputEvent() const;
		const ActionEvent& getInputEvent() const;

		//////////////////////////////////////////////////
		// Virtual Interface Operations
		//////////////////////////////////////////////////
	public:
		virtual void onCreate() = 0;
		virtual bool onUpdate(const double ts) = 0;
	};

}
