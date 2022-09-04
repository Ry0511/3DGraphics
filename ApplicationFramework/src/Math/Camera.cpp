#include "Camera.h"

namespace GMath {

#define DEG_TO_RAD(x) x * (GMath::PI / 180)

	//////////////////////////////////////////////////
	// Constructors
	//////////////////////////////////////////////////

	Camera::Camera(Vec3d eye, Vec3d at, Vec3d up) : m_Eye(eye), m_At(at), m_Up(up) {};
	Camera::Camera() : Camera({0,0,1}, {0,0,0}, {0,1,0}) {};

	//////////////////////////////////////////////////
	// Camera Getters
	//////////////////////////////////////////////////

	const GMath::Vec3d& Camera::getEye() const {
		return m_Eye;
	}

	const GMath::Vec3d& Camera::getAt() const {
		return m_At;
	}

	const GMath::Vec3d& Camera::getUp() const {
		return m_Up;
	}

	//////////////////////////////////////////////////
	// Camera Setters
	//////////////////////////////////////////////////

	void Camera::setEye(const Vec3d& v) {
		m_Eye = v;
	}

	void Camera::setAt(const Vec3d& v) {
		m_At = v;
	}

	void Camera::setUp(const Vec3d& v) {
		m_Up = v;
	}

	void Camera::addEye(const Vec3d& v) {
		m_Eye = m_Eye + v;
	}

	void Camera::addAt(const Vec3d& v) {
		m_At = m_At + v;
	}

	void Camera::addUp(const Vec3d& v) {
		m_Up = m_Up + v;
	}

	//////////////////////////////////////////////////
	// Moving around
	//////////////////////////////////////////////////

	void Camera::moveForward(const double speed) {
		addEye(m_At.mul(speed));
	}

	void Camera::moveBackward(const double speed) {
		addEye(m_At.mul(-speed));
	}

	void Camera::moveLeft(const double speed) {
		addEye(m_At.crossProduct(m_Up).normalise().mul(-speed));
	}

	void Camera::moveRight(const double speed) {
		addEye(m_At.crossProduct(m_Up).normalise().mul(speed));
	}

	//////////////////////////////////////////////////
	// Looking Around
	//////////////////////////////////////////////////

	void Camera::setYaw(const double yaw) {
		m_Yaw = yaw;
	}

	void Camera::setPitch(const double pitch) {
		m_Pitch = pitch;
	}

	void Camera::applyAngle() {

		const double yaw = DEG_TO_RAD(m_Yaw);
		const double pitch = DEG_TO_RAD(m_Pitch);

		const Vec3d v{
			cos(yaw) * cos(pitch),
			sin(pitch),
			sin(yaw) * cos(pitch),
		};

		setAt(v.normalise());
	}

	//////////////////////////////////////////////////
	// Camera Operations
	//////////////////////////////////////////////////

	GMath::Mat4x4d Camera::getViewMatrix(const CameraMode& mode) const {
		switch (mode) {
			case CameraMode::FREE_CAM: return newLookAtMatrix(m_Eye, m_At, m_Up);
			case CameraMode::FIRST_PERSON: return newLookAtMatrix(m_Eye, m_Eye + m_At, m_Up);
			default: throw "Unknown Camera Mode!";
		}
	}

}

