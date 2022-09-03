#pragma once

#include <math.h>
#include <string>
#include <format>

namespace GMath {

	template<typename T> struct Vec3 {
		mutable T x, y, z;

		T sum() const { return x + y + z; };
		T magnitude() const { return (T)sqrt((x * x) + (y * y) + (z * z)); };
		T dotProduct(const Vec3<T>& o) const { return (x * o.x) + (y * o.y) + (z * o.z); };

		Vec3<T> normalise() const {
			const T m = this->magnitude();
			return Vec3{x / m, y / m, z / m};
		};

		Vec3<T> add(const Vec3<T>& o) const { return {x + o.x, y + o.y, z + o.z}; };
		Vec3<T> add(const T v) const { return {x + v, y + v, z + v}; };
		Vec3<T> operator+(const Vec3<T>& o) const { return add(o); };
		Vec3<T> operator+(const T v) const { return add(v); };

		Vec3<T> sub(const Vec3<T>& o) const { return {x - o.x, y - o.y, z - o.z}; };
		Vec3<T> sub(const T v) const { return {x - v, y - v, z - v}; };
		Vec3<T> operator-(const Vec3<T>& o) const { return sub(o); };
		Vec3<T> operator-(const T v) const { return sub(v); };

		Vec3<T> div(const Vec3<T>& o) const { return {x / o.x, y / o.y, z / o.z}; };
		Vec3<T> div(const T v) const { return {x / v, y / v, z / v}; };
		Vec3<T> operator/(const Vec3<T>& o) const { return div(o); };
		Vec3<T> operator/(const T v) const { return div(v); };

		Vec3<T> crossProduct(const Vec3<T>& o) const {
			return {
				y * o.z - z * o.y,
				z * o.x - x * o.z,
				x * o.y - y * o.x
			};
		};

		Vec3<T> toScreenSpace(const int w, const int h) const {
			return {
				x * 0.5 * ((T)w),
				y * 0.5 * ((T)h),
				z
			};
		}

		std::string toString() const {
			return std::format("Vec3({0}, {1}, {2})", x, y, z);
		}

	};

	using Vec3i = Vec3<int>;
	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
}
