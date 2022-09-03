#include "Object3D.h"

namespace Util {

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

	//void Object3D::setModel(const Mesh<double> model) {
	//	m_Model = model;
	//}

	void Object3D::setTranslate(const Vec3d translate) {
		m_Translate = translate;
	}

	void Object3D::setScale(const Vec3d scale) {
		m_Scale = scale;
	}

	void Object3D::setRotate(const Vec3d rotate) {
		m_Rotate = rotate;
	}

	GMath::Mat4x4d Object3D::getViewMatrix() const {

		Mat4x4d trans = newTranslationMatrix(m_Translate);
		Mat4x4d scale = newScalingMatrix(m_Scale);
		Mat4x4d rotate = newRotateXYZ(m_Rotate);

		return trans * rotate * scale;
	}

}