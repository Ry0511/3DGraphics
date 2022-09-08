#include "WindowState.h"

namespace Input {

#define _THIS static_cast<WindowState*>(glfwGetWindowUserPointer(_H))

	//////////////////////////////////////////////////
	// Constructors
	//////////////////////////////////////////////////

	WindowState::WindowState(GLFWwindow* window) : m_WindowHandle(window) {
		glfwSetWindowUserPointer(window, this);

		// Mouse Position & Scroll
		glfwSetCursorPosCallback(window, [](auto* _H, double x, double y) {
			WindowState* self = _THIS;

			self->setMousePos({x, y});

			// Lock Mouse to Centre
			if (self->isCursorLocked()) {
				const Vec2d& size = self->getWindowSize();
				glfwSetCursorPos(_H, size.x / 2, size.y / 2);
			}
		});
		glfwSetScrollCallback(window, [](auto* _H, double x, double y) {
			WindowState* self = _THIS;
			self->setMouseScrollPos({x, y});
		});

		// Window Size & Position
		glfwSetWindowSizeCallback(window, [](auto* _H, int w, int h) {
			_THIS->setWindowSize({w, h});
		});
		glfwSetWindowPosCallback(window, [](auto* _H, int x, int y) {
			_THIS->setWindowPos({x,y});
		});

		// Key & Mouse Modifiers
		glfwSetKeyCallback(window, [](auto* _H, int k, int s, int a, int m) {
			_THIS->getActionModifiers().eventImpl(m);
		});
		glfwSetMouseButtonCallback(window, [](auto* _H, int b, int a, int m) {
			_THIS->getActionModifiers().eventImpl(m);
		});

		glfwGetWindowSize(window, &m_WindowSize.x, &m_WindowSize.y);
		glfwGetWindowPos(window, &m_WindowPos.x, &m_WindowPos.y);
		setMousePos(getWindowSize() / Vec2i{2, 2});
	}

	GMath::Vec2d WindowState::getMousePosImpl() const {
		Vec2d v{};
		glfwGetCursorPos(m_WindowHandle, &v.x, &v.y);
		return v;
	}

	const GMath::Vec2d WindowState::getMouseVelocity(const Vec2d& sens) const {
		return (getMousePos() - getMousePosImpl()) * sens;
	}

	const GMath::Vec2d WindowState::getMouseScrollVelocity(const Vec2d& scrollSens) {
		const Vec2d& pos = getMouseScrollPos();
		const Vec2d delta = pos * scrollSens;
		pos.x = 0;
		pos.y = 0;
		return delta;
	}

}