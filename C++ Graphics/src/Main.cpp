
#include "Core/Application.h"
#include "Input/ActionEvent.h"
#include "Math/Camera.h"
#include "Util/Random.h"
#include "Util/Object3D.h"
#include "Vec4.h"

#include <iostream>
#include <format>

class App : public Core::Application {

	Util::Object3D m_Cube{GMath::SampleMesh::CUBE};
	GMath::Camera m_Camera{{0,0,3}, {0,0,-1}, {0,1,0}};

	double theta = 0.0;

	double yaw = -90;
	double pitch = -0;

public:

	App() : Core::Application(800, 600, "App") {};

	virtual void onCreate() override {
		std::cout << "[CREATE]" << std::endl;

		m_Cube.setTranslate({0,0,5});
		m_Cube.setScale({1,1,1});
		m_Cube.setRotate({0,0,0});

		m_Cube.setVecPredicate([this](auto& tri, auto& normal) -> bool {
			return normal.dotProduct(m_Camera.getAt().sub(tri[0])) < 0.0;
		});

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	virtual bool onUpdate(const double ts) override {
		// Rotate Model
		theta += ts;
		// m_Cube.setRotate({theta, theta * 0.7, ts * 1.5});

		while (hasInputEvent()) {
			const Input::ActionEvent& e = getInputEvent();

			if (e.isKeyEvent()) {
				if (e.isPress() || e.isRepeat()) {

					double speed = 500 * ts;
					switch (e.getButton()) {

						case GLFW_KEY_LEFT: m_Camera.setYaw(yaw -= 0.5); m_Camera.applyAngle(); break;
						case GLFW_KEY_RIGHT: m_Camera.setYaw(yaw += 0.5); m_Camera.applyAngle(); break;

						case GLFW_KEY_UP: m_Camera.setPitch(pitch += 0.5); m_Camera.applyAngle(); break;
						case GLFW_KEY_DOWN: m_Camera.setPitch(pitch -= 0.5); m_Camera.applyAngle(); break;

						case GLFW_KEY_W: m_Camera.moveForward(speed); break;
						case GLFW_KEY_S: m_Camera.moveBackward(speed); break;

						case GLFW_KEY_A: m_Camera.moveLeft(speed); break;
						case GLFW_KEY_D: m_Camera.moveRight(speed); break;
					}
				}

				std::cout << yaw << std::endl;

				// Mouse Event
			} else {

			}

		}

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Display Model
		GMath::Recti bounds = getWindowBounds();
		glLoadIdentity();
		glViewport(0, 0, bounds.w, bounds.h);


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
