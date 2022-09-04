#pragma once

#include "GL/glew.h"
#include "../Math/Mesh.h"
#include "../Math/Vec3.h"
#include "../Math/Matrix.h"

#include <functional>

namespace Util {

	using namespace GMath;

	class Object3D {

	private:
		const Mesh m_Model;
		Vec3d m_Translate{0,0,0};
		Vec3d m_Scale{0,0,0};
		Vec3d m_Rotate{0,0,0};

		// Vec3d& here is the Normal of the translated triangle
		std::function<bool(Triangle&, Vec3d&)> m_VecPredicate = defaultVecPredicateImpl;
		std::function<void(Triangle&, Vec3d&)> m_TriangleRenderer = defaultTriRendererImpl;

	public:
		static bool defaultVecPredicateImpl(Triangle& tri, Vec3d& normal);
		static void defaultTriRendererImpl(Triangle& tri, Vec3d& normal);

	public:
		Object3D(const Mesh model) : m_Model(model) {};

	public:
		const Mesh& getModel() const;
		const Vec3d& getTranslate() const;
		const Vec3d& getScale() const;
		const Vec3d& getRotate() const;

	public:
		// void setModel(const Mesh<double> model);
		void setTranslate(const Vec3d translate);
		void setScale(const Vec3d scale);
		void setRotate(const Vec3d rotate);

		void setVecPredicate(std::function<bool(Triangle&,Vec3d&)> fn);
		void setTriRenderer(std::function<bool(Triangle&,Vec3d&)> fn);

	public:
		Mat4x4d getViewMatrix() const;

		void render(Mat4x4d& mv) const;
	};
}
