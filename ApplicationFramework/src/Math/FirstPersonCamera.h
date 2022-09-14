#pragma once

#include "Vec3.h"
#include "Matrix.h"
#include "../Core/Application.h"

#include <cstdint>

namespace GMath {

	using namespace Input;

	class FirstPersonCamera {

	public:
#define DEG_TO_RAD(x) x * (GMath::PI / 180)

		static constexpr double PITCH_MIN = -89.0;
		static constexpr double PITCH_MAX = 89.0;

		using V = Vec3d;
		using D = double;

	private:
		Vec2d m_Sensitivity{0.008, 0.008};
		D m_MoveSpeed = 2;
		D m_ShiftScalar = 3;
		V m_Pos, m_Front = {0, 0, -1}, m_Up{}, m_Right{}, m_WorldUp{0,1,0};
		D m_Yaw, m_Pitch;

	public:
		FirstPersonCamera(V pos, D yaw = 90, D pitch = 0.0);

	public:
		V& getPos();
		V& getFront();
		V& getUp();
		V& getRight();
		V& getWorldUp();
		D& getYaw();
		D& getPitch();
		Vec2d& getMouseSensitivity();
		D& getMoveSpeed();
		D& getShiftScalar();

	public:
		void moveForward(const D vel);
		void moveBackward(const D vel);
		void moveLeft(const D vel);
		void moveRight(const D vel);
		void addYawAndPitch(const Vec2d& delta);

	public:
		Mat4x4d getViewMatrix() const;
		void update(const D delta, const Core::Application* app);

	private:
		void initVectors();
	};
}

