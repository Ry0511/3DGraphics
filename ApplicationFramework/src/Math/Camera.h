#pragma once

#include "../Core/Application.h"
#include "Matrix.h"
#include "Vec3.h"
#include "Vec4.h"

#include <string>
#include <format>

namespace GMath {

	enum class CameraMode {
		FREE_CAM, FIRST_PERSON
	};

	class Camera {

	private:

		// Also known as: Pos, Front, Up
		Vec3d m_Eye;
		Vec3d m_At;
		Vec3d m_Up;

		double m_Yaw = 0;
		double m_Pitch = 0;

	public:
		Camera(Vec3d eye, Vec3d at, Vec3d up);
		Camera();

	public:
		const Vec3d& getEye() const;
		const Vec3d& getAt() const;
		const Vec3d& getUp() const;

	public:
		void setEye(const Vec3d& v);
		void setAt(const Vec3d& v);
		void setUp(const Vec3d& v);

		void addEye(const Vec3d& v);
		void addAt(const Vec3d& v);
		void addUp(const Vec3d& v);

		// Moving around
		void moveForward(const double speed);
		void moveBackward(const double speed);
		void moveLeft(const double speed);
		void moveRight(const double speed);

		// Looking around
		void setYaw(const double yaw);
		void setPitch(const double pitch);
		void applyAngle();

	public:
		Mat4x4d getViewMatrix(const CameraMode& mode) const;
	};
}

