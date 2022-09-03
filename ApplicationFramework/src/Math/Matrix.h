#pragma once

#include "Vec3.h"
#include <array>

namespace GMath {

#define TSize template<size_t o_Rows, size_t o_Cols>
#define TSizeMatrix Matrix<T, o_Rows, o_Cols>
#define SelfMatrix Matrix<T, m_Rows, m_Cols>

	constexpr double PI = 3.141592653589793;

	template<typename T, size_t m_Rows, size_t m_Cols> struct Matrix {

		using TMatrix = std::array<std::array<T, m_Cols>, m_Rows>;

		TMatrix xs;

		std::array<T, m_Cols>& operator[](const size_t i) { return xs[i]; };

		TSize TSizeMatrix multiply(const TSizeMatrix& other) {

			if (m_Cols != o_Rows) {
				throw "Can't multiply as sizes differ";
			}

			TSizeMatrix m{};

			for (size_t i = 0; i < m_Rows; ++i) {
				for (size_t j = 0; j < o_Cols; ++j) {
					for (size_t k = 0; k < m_Cols; k++) {
						m.xs[i][j] += xs[i][k] * other.xs[k][j];
					}
				}
			}

			return m;
		};

		TSize TSizeMatrix operator*(const TSizeMatrix& other) { return multiply(other); };
	};

	using Mat4x4d = Matrix<double, 4, 4>;
	using Mat4x1d = Matrix<double, 4, 1>;

#pragma region DEFAULT_MATRIX_IMPLEMENTATIONS

	static Mat4x4d newIdentityMatrix() {
		return {{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		}};
	}

	static Mat4x4d newProjectionMatrix(const double w, const double h, const double fov) {

		constexpr double near = 0.1;
		constexpr double far = 1000;
		const double ar = w / h;
		const double fRad = 1 / tan(fov * 0.5 / 180 * PI);

		Mat4x4d m{};

		m[0][0] = ar * fRad;
		m[1][1] = fRad;
		m[2][2] = far / (far - near);
		m[3][2] = (-far * near) / (far - near);
		m[2][3] = 1;
		m[3][3] = 0;

		return m;
	}

	static Mat4x4d newRotateX(const double t) {
		return {{
			1, 0,      0,       0,
			0, cos(t), -sin(t), 0,
			0, sin(t), cos(t),  0,
			0, 0,      0,       1
		}};
	};

	static Mat4x4d newRotateY(const double t) {
		return {{
			cos(t),  0, sin(t), 0,
			0,       1, 0,      0,
			-sin(t), 0, cos(t), 0,
			0,       0, 0,      1
		}};
	};

	static Mat4x4d newRotateZ(const double t) {
		return {{
			cos(t), -sin(t), 0, 0,
			sin(t), cos(t),  0, 0,
			0,      0,       1, 0,
			0,      0,       0, 1
		}};
	};

	static Mat4x4d newRotateXYZ(const Vec3d& v) {
		return newRotateX(v.x) * newRotateY(v.y) * newRotateZ(v.z);
	}

	static Mat4x4d newTranslationMatrix(const Vec3d& v) {
		return {{
			1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z,
			0, 0, 0, 1
		}};
	}

	static Mat4x4d newScalingMatrix(const Vec3d& v) {
		return {{
			v.x, 0,   0,   0,
			0,   v.y, 0,   0,
			0,   0,   v.z, 0,
			0,   0,   0,   1
		}};
	}

#pragma endregion

}
