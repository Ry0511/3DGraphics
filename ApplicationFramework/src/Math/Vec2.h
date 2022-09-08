#pragma once

#include <algorithm>
#include <format>

namespace GMath {

	template<typename T> struct Vec2 {
		mutable T x, y;

		Vec2<T> add(const Vec2<T>& o) const { return {x + o.x, y + o.y}; };
		Vec2<T> operator+(const Vec2<T>& o) const { return add(o); };

		Vec2<T> sub(const Vec2<T>& o) const { return {x - o.x, y - o.y}; };
		Vec2<T> operator-(const Vec2<T>& o) const { return sub(o); };

		Vec2<T> mul(const Vec2<T>& o) const { return {x * o.x, y * o.y}; };
		Vec2<T> operator*(const Vec2<T>& o) const { return mul(o); };

		Vec2<T> div(const Vec2<T>& o) const { return {x / o.x, y / o.y}; };
		Vec2<T> operator/(const Vec2<T>& o) const { return div(o); };

		Vec2<T> clamp(T min, T max) const { return {std::clamp(x, min, max), std::clamp(y, min, max)}; };

		template<typename E> operator Vec2<E>() const { return {(E)x, (E)y}; };

		std::string toString() const {
			return std::format("({0}, {1})", x, y);
		}
	};

	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;

}
