#pragma once

namespace GMath {

	template<typename T> struct Vec2 {
		mutable T x, y;

		// TODO: Define immutable operations
	};

	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;

}
