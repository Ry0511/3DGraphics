
#include "Core/Application.h"
#include "Math/Camera.h"
#include "Util/Random.h"
#include "Util/Object3D.h"
#include "Vec4.h"

#include <iostream>
#include <format>

class App : public Core::Application {

	Util::Object3D m_Cube{GMath::SampleMesh::CUBE};
	GMath::Camera m_Camera{{0,0,0}, {0,0,-1}, {0,1,0}};

	double theta = 0.0;

	double yaw = -90;
	double pitch = -0;

public:

	App() : Core::Application(800, 600, "App") {};

	virtual void onCreate() override {
		std::cout << "[CREATE]" << std::endl;

		m_Cube.setTranslate({0,0,5});
		m_Cube.setScale({0.5,0.5,0.5});
		m_Cube.setRotate({0,0,0});

		m_Cube.setVecPredicate([this](auto& tri, auto& normal) {
			return normal.dotProduct(m_Camera.getAt().sub(tri[0])) < 0.0;
		});

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(3);
	}

	virtual bool onUpdate(const double ts) override {
		// Rotate Model
		theta += ts;
		//m_Cube.setRotate({theta, theta * 0.7, ts * 1.5});

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Mouse Input
		if (getMouseState(GLFW_MOUSE_BUTTON_1)) {
			App::setIsMouseLocked(true);

			const GMath::Vec2d vel = getMouseVelocity({0.008, 0.008});

			yaw += vel.x;
			pitch += vel.y;

			if (pitch > 89) pitch = 89;
			if (pitch < -89) pitch = -89;

			m_Camera.setPitch(pitch);
			m_Camera.setYaw(yaw);
			m_Camera.applyAngle();
		} else {
			App::setIsMouseLocked(false);
		}

		// Zooming in & out
		if (getMouseState(GLFW_MOUSE_BUTTON_2)) {
			GMath::Vec2d scroll = getWindowInput().getMouseScrollVelocity({0.2, 0.2});
			m_Cube.setTranslate(m_Cube.getTranslate() + GMath::Vec3d{0, 0, scroll.y});
		}

		// Moving around
		double speed = isModifierSet(Input::Modifier::SHIFT) ? 4 * ts : 2 * ts;
		if (getKeyState(GLFW_KEY_W)) m_Camera.moveForward(speed);
		if (getKeyState(GLFW_KEY_S)) m_Camera.moveBackward(speed);
		if (getKeyState(GLFW_KEY_A)) m_Camera.moveLeft(speed);
		if (getKeyState(GLFW_KEY_D)) m_Camera.moveRight(speed);

		// Display Model
		GMath::Recti bounds = getWindowBounds();
		glLoadIdentity();
		glViewport(0, 0, bounds.w, bounds.h);

		// Transforms
		auto proj = GMath::newProjectionMatrix(bounds.w, bounds.h, 90);
		auto cam = m_Camera.getViewMatrix(GMath::CameraMode::FIRST_PERSON);
		auto cube = m_Cube.getViewMatrix();

		GMath::Mat4x4d mvp = proj * cube * cam;
		m_Cube.render(mvp);

		return true;
	}
};

int main() {
	App app;
	app.start();
	return 0;
}
