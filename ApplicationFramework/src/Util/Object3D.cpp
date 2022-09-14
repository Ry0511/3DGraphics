#include "Object3D.h"

#include <iostream>

namespace Util {

	//////////////////////////////////////////////////
	// Default Rendering Actions
	//////////////////////////////////////////////////

	bool Object3D::defaultVecPredicateImpl(Triangle& tri, Vec3d& normal) {
		// Camera assumed to be (0,0,0)
		return normal.dotProduct(Vec3d(0,0,0).sub(tri[0])) < 0.0;
	}

	void Object3D::defaultTriRendererImpl(Triangle& tri, Vec3d& normal) {
		// Light Position Assumed to be (0,0,-1)
		const double dp = normal.dotProduct(Vec3d(0, 0, -1).normalise());
		double v = std::max(0.1, dp);
		glColor3d(v,v,v);
		for (const auto& vec : tri.vertices) {
			glVertex2d(vec.x, vec.y);
			// glVertex3d(vec.x, vec.y, vec.z);
		}
	}

	//////////////////////////////////////////////////
	// GETTERS
	//////////////////////////////////////////////////

	const GMath::Mesh& Object3D::getModel() const {
		return m_Model;
	}

	const GMath::Vec3d& Object3D::getTranslate() const {
		return m_Translate;
	}

	const GMath::Vec3d& Object3D::getScale() const {
		return m_Scale;
	}

	const GMath::Vec3d& Object3D::getRotate() const {
		return m_Rotate;
	}

	//////////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////////

	void Object3D::setTranslate(const Vec3d translate) {
		m_Translate = translate;
	}

	void Object3D::setScale(const Vec3d scale) {
		m_Scale = scale;
	}

	void Object3D::setRotate(const Vec3d rotate) {
		m_Rotate = rotate;
	}

	void Object3D::setVecPredicate(std::function<bool(Triangle&, Vec3d&)> fn) {
		m_VecPredicate = fn;
	}

	void Object3D::setTriRenderer(std::function<bool(Triangle&, Vec3d&)> fn) {
		m_TriangleRenderer = fn;
	}

	//////////////////////////////////////////////////
	// Costly operations
	//////////////////////////////////////////////////

	GMath::Mat4x4d Object3D::getViewMatrix() const {

		Mat4x4d trans = newTranslationMatrix(m_Translate);
		Mat4x4d scale = newScalingMatrix(m_Scale);
		Mat4x4d rotate = newRotateXYZ(m_Rotate);

		return trans * rotate * scale;
	}

	void Object3D::render(Mat4x4d& mvp) const {

		glBegin(GL_TRIANGLES);
		for (const GMath::Triangle& tri : m_Model.xs) {

			// Project and obtain the Normal
			GMath::Triangle projected = tri.project(mvp);
			GMath::Vec3d normal = projected.getNormal();

			// Don't render triangles that are not visible
			if (m_VecPredicate(projected, normal)) {
				m_TriangleRenderer(projected, normal);
			}
		}
		glEnd();
	}

}