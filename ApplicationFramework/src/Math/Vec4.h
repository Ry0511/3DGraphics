#pragma once

#include "Vec3.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <format>

namespace GMath {

	struct Vec4 : public Mat4x1d {

		Vec4(double x, double y, double z, double w) : Mat4x1d({x, y, z, w}) {};
		Vec4(const Vec3d& v, double w = 1.0) : Mat4x1d({v.x, v.y, v.z, w}) {};
		Vec4(const Mat4x1d& matrix) : Mat4x1d(matrix) {};

		operator Vec3d() const { return {getX(), getY(), getZ()}; };

		Vec4 normalise() const {
			if (getW() != 0) {
				const double w = getW();
				return {getX() / w, getY() / w, getZ() / w, w};
			}
			return *this;
		};

		double getX() const { return xs[0][0]; };
		double getY() const { return xs[1][0]; };
		double getZ() const { return xs[2][0]; };
		double getW() const { return xs[3][0]; };

		std::string toString() const {
			return std::format(
				"Vec4({0:.4f}, {1:.4f}, {2:.4f}, {3:.4f})",
				getX(), getY(), getZ(), getW()
			);
		}
	};

}