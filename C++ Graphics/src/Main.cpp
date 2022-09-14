
#include "Core/Application.h"
#include "Math/FirstPersonCamera.h"
#include "Util/Random.h"
#include "Util/Object3D.h"
#include "Vec4.h"
#include "Util/ObjFile.h"

#include <iostream>
#include <format>

class App : public Core::Application {

	GMath::FirstPersonCamera m_Camera{{0,0,-3}};

	Util::Object3D m_Cube{GMath::SampleMesh::CUBE};
	Util::Object3D* m_Sphere = nullptr;

	double theta = 0.0;

public:

	App() : Core::Application(800, 600, "App") {};

	virtual void onCreate() override {
		std::cout << "[CREATE]" << std::endl;

		m_Cube.setTranslate({0,0,5});
		m_Cube.setScale({0.5,0.5,0.5});
		m_Cube.setRotate({0,0,0});

		auto vectorPredicate = [this](auto& tri, auto& normal) {
			return normal.dotProduct(m_Camera.getFront().sub(tri[0])) < 0.0;
		};

		m_Cube.setVecPredicate(vectorPredicate);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(2);

		Util::ObjFile file("resource/Sphere.obj");
		m_Sphere = new Util::Object3D(GMath::Mesh(file.getTriangleMesh()));
		m_Sphere->setVecPredicate(vectorPredicate);

		m_Sphere->setTranslate({0,0,10});
		m_Sphere->setScale({0.05,0.05,0.05});
		m_Sphere->setRotate({0,0,0});
	}

	virtual bool onUpdate(const double ts) override {
		// Rotate Model
		theta += ts;
		m_Sphere->setRotate({theta * 0.8, theta * 0.5, theta});

		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Camera.update(ts, this);

		// Display Model
		GMath::Recti bounds = getWindowBounds();
		glViewport(0, 0, bounds.w, bounds.h);

		// Transforms
		auto proj = GMath::newProjectionMatrix(bounds.w, bounds.h, 90);
		auto cam = m_Camera.getViewMatrix();

		// Cube
		GMath::Mat4x4d mvp = proj * cam * m_Cube.getViewMatrix();
		m_Cube.render(mvp);

		// Sphere
		mvp = proj * cam * m_Sphere->getViewMatrix();
		m_Sphere->render(mvp);

		return true;
	}
};

int main() {
	App app;
	app.start();
	return 0;
}
