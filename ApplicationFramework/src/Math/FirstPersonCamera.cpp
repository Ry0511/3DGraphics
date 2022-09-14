#include "FirstPersonCamera.h"

#include <iostream>

namespace GMath {

	//////////////////////////////////////////////////
	// Constructors
	//////////////////////////////////////////////////

	FirstPersonCamera::FirstPersonCamera(V pos, D yaw, D pitch)
		: m_Pos(pos), m_Yaw(yaw), m_Pitch(pitch) {
		initVectors();
	}

	//////////////////////////////////////////////////
	// Getters & Setters
	//////////////////////////////////////////////////

	GMath::FirstPersonCamera::V& FirstPersonCamera::getPos() {
		return m_Pos;
	}

	GMath::FirstPersonCamera::V& FirstPersonCamera::getFront() {
		return m_Front;
	}

	GMath::FirstPersonCamera::V& FirstPersonCamera::getUp() {
		return m_Up;
	}

	GMath::FirstPersonCamera::V& FirstPersonCamera::getRight() {
		return m_Right;
	}

	GMath::FirstPersonCamera::V& FirstPersonCamera::getWorldUp() {
		return m_WorldUp;
	}

	GMath::FirstPersonCamera::D& FirstPersonCamera::getYaw() {
		return m_Yaw;
	}

	GMath::FirstPersonCamera::D& FirstPersonCamera::getPitch() {
		return m_Pitch;
	}

	GMath::Vec2d& FirstPersonCamera::getMouseSensitivity() {
		return m_Sensitivity;
	}

	GMath::FirstPersonCamera::D& FirstPersonCamera::getMoveSpeed() {
		return m_MoveSpeed;
	}

	GMath::FirstPersonCamera::D& FirstPersonCamera::getShiftScalar() {
		return m_ShiftScalar;
	}

	//////////////////////////////////////////////////
	// Moving & Looking Around.
	//////////////////////////////////////////////////

	void FirstPersonCamera::moveForward(const D vel) {
		m_Pos = m_Pos.add(m_Front.mul(vel));
	}

	void FirstPersonCamera::moveBackward(const D vel) {
		m_Pos = m_Pos.sub(m_Front.mul(vel));
	}

	void FirstPersonCamera::moveLeft(const D vel) {
		m_Pos = m_Pos.sub(m_Right.mul(vel));
	}

	void FirstPersonCamera::moveRight(const D vel) {
		m_Pos = m_Pos.add(m_Right.mul(vel));
	}

	void FirstPersonCamera::addYawAndPitch(const Vec2d& delta) {
		m_Yaw += delta.x;
		m_Pitch += delta.y;

		// This prevents m_Up becoming inverted
		m_Pitch = std::clamp(m_Pitch, PITCH_MIN, PITCH_MAX);

		initVectors();
	}

	//////////////////////////////////////////////////
	// View Matrix.
	//////////////////////////////////////////////////

	GMath::Mat4x4d FirstPersonCamera::getViewMatrix() const {
		return newLookAtMatrix(m_Pos, m_Pos + m_Front, m_Up);
	}

	void FirstPersonCamera::update(const D ts, const Core::Application* app) {

		// Look Around (Explicitly done before moving)
		if (app->getMouseState(GLFW_MOUSE_BUTTON_1)) {
			app->getWindowInput().setIsMouseLocked(true);
			addYawAndPitch(app->getMouseVelocity(m_Sensitivity));
		} else {
			app->getWindowInput().setIsMouseLocked(false);
		}

		// Move Around
		const bool isShift = app->isModifierSet(Modifier::SHIFT);
		const double delta = (isShift ? m_MoveSpeed * m_ShiftScalar : m_MoveSpeed) * ts;
		if (app->getKeyState(GLFW_KEY_W)) moveForward(delta);
		if (app->getKeyState(GLFW_KEY_S)) moveBackward(delta);
		if (app->getKeyState(GLFW_KEY_A)) moveLeft(delta);
		if (app->getKeyState(GLFW_KEY_D)) moveRight(delta);
	}

	//////////////////////////////////////////////////
	// Initialise or Re-initialise the Front, Right,
	// and Up vectors.
	//////////////////////////////////////////////////

	void FirstPersonCamera::initVectors() {
		D yaw = DEG_TO_RAD(m_Yaw);
		D pitch = DEG_TO_RAD(m_Pitch);

		m_Front = V(cos(yaw) * cos(pitch),
					sin(pitch),
					sin(yaw) * cos(pitch)).normalise();

		m_Right = (m_Front.crossProduct(m_WorldUp)).normalise();
		m_Up = (m_Right.crossProduct(m_Front)).normalise();
	}

}