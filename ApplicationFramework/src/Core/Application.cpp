#include "Application.h"

namespace Core {

	//////////////////////////////////////////////////
	// Constructors & Destructor's
	//////////////////////////////////////////////////

	Application::Application(const uint16_t w, const uint16_t h, const char* title) {
		if (!glfwInit()) {
			throw "GLFW didn't initialise!";
		}
		m_Handle = glfwCreateWindow(w, h, title, nullptr, nullptr);
		if (!m_Handle) throw "GLFW window handle invalid!";
		m_WindowState = new WindowState(m_Handle);
	}

	Application::~Application() {
		delete m_WindowState;
		glfwDestroyWindow(m_Handle);
		glfwTerminate();
	}

	//////////////////////////////////////////////////
	// Core Operations
	//////////////////////////////////////////////////

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

	Recti Application::getWindowBounds() const {
		Recti r;
		glfwGetWindowPos(m_Handle, &r.x, &r.y);
		glfwGetWindowSize(m_Handle, &r.w, &r.h);
		return r;
	}

	void Application::setWindowTitle(const char* str) const {
		glfwSetWindowTitle(m_Handle, str);
	}

	void Application::setWindowBounds(const Recti& bounds) const {
		glfwSetWindowPos(m_Handle, bounds.x, bounds.y);
		glfwSetWindowSize(m_Handle, bounds.w, bounds.h);
	}

	//////////////////////////////////////////////////
	// Window Input Interface
	//////////////////////////////////////////////////

	Input::WindowState& Application::getWindowInput() const {
		return (*m_WindowState);
	}

	const GMath::Vec2i& Application::getWindowSize() const {
		return m_WindowState->getWindowSize();
	}

	const GMath::Vec2i& Application::getWindowPos() const {
		return m_WindowState->getWindowPos();
	}

	const GMath::Vec2d& Application::getMousePos() const {
		return m_WindowState->getMousePos();
	}

	const GMath::Vec2d Application::getMouseVelocity(const Vec2d& sens) const {
		return m_WindowState->getMouseVelocity(sens);
	}

	const void Application::setIsMouseLocked(const bool state) {
		m_WindowState->setIsMouseLocked(state);
	}

	const GMath::Vec2d Application::getScrollVelocity(const Vec2d& sens) const {
		return m_WindowState->getMouseScrollVelocity(sens);
	}

	const Input::Modifiers& Application::getKeyboardModifiers() const {
		return m_WindowState->getActionModifiers();
	}

	const bool Application::isModifierSet(const Input::Modifier mod) const {
		return getKeyboardModifiers().isModifier(mod);
	}

	//////////////////////////////////////////////////
	// Window Input
	//////////////////////////////////////////////////

	int Application::getKeyState(const int key) const {
		return glfwGetKey(m_Handle, key);
	}

	int Application::getMouseState(const int button) const {
		return glfwGetMouseButton(m_Handle, button);
	}

}
