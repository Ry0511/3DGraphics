#include "Application.h"

namespace Core {

	//////////////////////////////////////////////////
	// Core Operations
	//////////////////////////////////////////////////

	Application::Application(const uint16_t w, const uint16_t h, const char* title) {
		if (!glfwInit()) {
			throw "GLFW didn't initialise!";
		} else {
			m_Handle = glfwCreateWindow(w, h, title, nullptr, nullptr);
			if (!m_Handle) throw "GLFW window handle invalid!";
			Input::InputManager::getInstance()->addWindow(m_Handle);
		}
	}

	Application::~Application() {
		glfwDestroyWindow(m_Handle);
		glfwTerminate();
	}

	void Application::start() {

		// Simplify
		using Time = std::chrono::system_clock;
		using Instant = std::chrono::system_clock::time_point;
		using Duration = std::chrono::duration<double>;

		// Create OpenGL context
		glfwMakeContextCurrent(m_Handle);
		if (glewInit() != GLEW_OK) {
			throw "GLEW Didn't initialise!";
		}

		// Allow user to init
		onCreate();

		// Enter update loop
		Instant before = Time::now();
		while (!glfwWindowShouldClose(m_Handle)) {

			const Instant now = Time::now();
			glfwSwapBuffers(m_Handle);
			glfwPollEvents();
			const bool isClose = !onUpdate(Duration(now - before).count());
			before = now;

			// Close the window if the application signals it
			if (isClose) {
				glfwSetWindowShouldClose(m_Handle, GLFW_TRUE);
			}
		}
	}

	//////////////////////////////////////////////////
	// Window Operations
	//////////////////////////////////////////////////

	GLFWwindow* Application::getWindow() const {
		return m_Handle;
	}

	Vec2d Application::getMousePos() const {
		Vec2d v{};
		glfwGetCursorPos(m_Handle, &v.x, &v.y);
		return v;
	}

	Recti Application::getWindowBounds() const {
		Recti r;
		glfwGetWindowPos(m_Handle, &r.x, &r.y);
		glfwGetWindowSize(m_Handle, &r.w, &r.h);
		return r;
	}

	int Application::getKeyState(const int key) const {
		return glfwGetKey(m_Handle, key);
	}

	int Application::getMouseState(const int button) const {
		return glfwGetMouseButton(m_Handle, button);
	}

	void Application::setWindowTitle(const char* str) const {
		glfwSetWindowTitle(m_Handle, str);
	}

	void Application::setWindowBounds(const Recti& bounds) const {
		glfwSetWindowPos(m_Handle, bounds.x, bounds.y);
		glfwSetWindowSize(m_Handle, bounds.w, bounds.h);
	}

	//////////////////////////////////////////////////
	// Event Polling Operations
	//////////////////////////////////////////////////

	const bool Application::hasInputEvent() const {
		return InputManager::getInstance()->hasEvent();
	}

	const Input::ActionEvent& Application::getInputEvent() const {
		return InputManager::getInstance()->head();
	}

}
