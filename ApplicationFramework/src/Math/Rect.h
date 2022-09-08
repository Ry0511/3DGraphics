#pragma once

namespace GMath {

	template<typename T> struct Rect {
		mutable T x, y, w, h;

		constexpr Rect() : x(), y(), w(), h() {};

		constexpr Rect(const T x, const T y, const T w, const T h)
			: x(x), y(y), w(w), h(h)
		{};

	};

	using Recti = Rect<int>;
	using Rectf = Rect<float>;
	using Rectd = Rect<double>;

}
