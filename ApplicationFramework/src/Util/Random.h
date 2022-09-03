#pragma once

#include <random>
#include <stdint.h>

namespace Util {
	class Random {

	private:
		std::default_random_engine m_Engine{};

	public:
		constexpr Random() = default;

	public:
		std::uniform_int_distribution<int> newIntUniform(int min, int max);
		std::uniform_real_distribution<double> newRealUniform(double min, double max);

		int getIntegral(const std::uniform_int_distribution<int>& dist);
		double getReal(const std::uniform_real_distribution<double>& dist);

	};
}

