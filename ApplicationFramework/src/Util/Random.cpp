#include "Random.h"

namespace Util {

	std::uniform_int_distribution<int> Random::newIntUniform(int min, int max) {
		return std::uniform_int_distribution<int>{min, max};
	}

	std::uniform_real_distribution<double> Random::newRealUniform(double min, double max) {
		return std::uniform_real_distribution<double>{min, max};
	}

	int Random::getIntegral(const std::uniform_int_distribution<int>& dist) {
		return dist(m_Engine);
	}

	double Random::getReal(const std::uniform_real_distribution<double>& dist) {
		return dist(m_Engine);
	}

}