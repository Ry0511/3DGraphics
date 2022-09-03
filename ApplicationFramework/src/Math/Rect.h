#pragma once

namespace GMath {

	template<typename T> struct Rect {
		mutable T x, y, w, h;

		constexpr Rect() : x(), y(), w(), h() {};

		constexpr Rect(const T x, const T y, const T w, const T h)
			: x(x), y(y), w(w), h(h)
		{};

	};

	typedef Rect<int> Recti;
	typedef Rect<float> Rectf;
	typedef Rect<double> Rectd;

}
