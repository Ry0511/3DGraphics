#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Matrix.h"
#include <array>
#include <functional>

namespace GMath {

	struct Triangle {
		const std::array<Vec3d, 3> vertices;

		const Vec3d& operator[](const int i) const { return vertices[i]; };

		Vec3d getNormal() const {
			const Vec3d l0 = vertices[1] - vertices[0];
			const Vec3d l1 = vertices[2] - vertices[0];
			return l0.crossProduct(l1).normalise();
		};

		Triangle project(Mat4x4d& mvp) const {

			GMath::Vec3d p0 = ((GMath::Vec4)(mvp * GMath::Vec4{vertices[0]})).normalise();
			GMath::Vec3d p1 = ((GMath::Vec4)(mvp * GMath::Vec4{vertices[1]})).normalise();
			GMath::Vec3d p2 = ((GMath::Vec4)(mvp * GMath::Vec4{vertices[2]})).normalise();

			return {p0, p1, p2};
		}

		void forEach(const std::function<void(const Vec3d&)>& fn) {
			for (const Vec3d& v : vertices) fn(v);
		}
	};
}
