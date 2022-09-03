
#include "Core/Application.h"
#include "Input/ActionEvent.h"
#include "Util/Random.h"
#include "Util/Object3D.h"
#include "Vec4.h"

#include <iostream>
#include <format>

class App : public Core::Application {

	Util::Object3D m_Cube{GMath::SampleMesh::CUBE};
	GMath::Vec3d m_Camera{0,0,0};
	GMath::Vec3d m_LightPos{0,0,-1};

	double theta = 0.0;

public:

	App() : Core::Application(800, 600, "App") {};

	virtual void onCreate() override {
		std::cout << "[CREATE]" << std::endl;

		m_Cube.setTranslate({0,0,3});
		m_Cube.setScale({0.1,0.1,0.1});

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	virtual bool onUpdate(const double ts) override {
		// Rotate Model
		theta += ts;
		m_Cube.setRotate({theta, theta * 0.7, ts * 1.5});

		setWindowTitle(std::format("{0:.4f}", ts).c_str());

		// Poll Events
		while (hasInputEvent()) {
			const Input::ActionEvent& e = getInputEvent();
			if (e.isKeyEvent() && e.isPress()) {
				switch (e.getButton()) {
					case GLFW_KEY_W: m_Camera = m_Camera.add({0, 0.05, 0});
						break;
					case GLFW_KEY_S: m_Camera = m_Camera.sub({0, 0.05, 0});
						break;
					case GLFW_KEY_A: m_Camera = m_Camera.sub({0.05, 0, 0});
						break;
					case GLFW_KEY_D: m_Camera = m_Camera.add({0.05, 0, 0});
						break;

					case GLFW_KEY_UP: m_Camera = m_Camera.add({0, 0, 0.1});
						break;
					case GLFW_KEY_DOWN: m_Camera = m_Camera.sub({0, 0, 0.1});
						break;
				}
			}

			if (e.isMouseEvent() && e.isPress()) {
				if (e.isMouseLeft()) {

				} else if (e.isMouseRight()) {

				}
			}
		}

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Display Model
		GMath::Recti bounds = getWindowBounds();

		glLoadIdentity();
		glViewport(0, 0, bounds.w, bounds.h);

		GMath::Mat4x4d view = GMath::newTranslationMatrix(m_Camera);
		GMath::Mat4x4d mvp = GMath::newProjectionMatrix(bounds.w, bounds.h, 120) * view * m_Cube.getViewMatrix();

		glBegin(GL_TRIANGLES);
		for (const GMath::Triangle& tri : m_Cube.getModel().xs) {

			GMath::Triangle projected = tri.project(mvp);
			GMath::Vec3d normal = projected.getNormal();

			if (normal.dotProduct(m_Camera.sub(projected[0])) < 0.0) {

				GMath::Vec3d lightDir = m_LightPos.normalise();
				double dp = normal.dotProduct(lightDir);

				for (const GMath::Vec3d& v : tri.project(mvp).vertices) {
					glColor3d(0.1 * dp, 0.75 * dp, 0.75 * dp);
					glVertex2d(v.x, v.y);
				}
			}
		}
		glEnd();

		return true;
	}
};

int main() {
	App app;
	app.start();
	return 0;
}
