#pragma once

#include "Triangle.h"
#include <vector>

namespace GMath {

	struct Mesh {
		std::vector<Triangle> xs;
	};

	namespace SampleMesh {
		static const Mesh CUBE{{
			{0, 0, 0,    0, 1, 0,    1, 1, 0},
			{0, 0, 0,    1, 1, 0,    1, 0, 0},

			{1, 0, 0,    1, 1, 0,    1, 1, 1},
			{1, 0, 0,    1, 1, 1,    1, 0, 1},

			{1, 0, 1,    1, 1, 1,    0, 1, 1},
			{1, 0, 1,    0, 1, 1,    0, 0, 1},

			{0, 0, 1,    0, 1, 1,    0, 1, 0},
			{0, 0, 1,    0, 1, 0,    0, 0, 0},

			{0, 1, 0,    0, 1, 1,    1, 1, 1},
			{0, 1, 0,    1, 1, 1,    1, 1, 0},

			{1, 0, 1,    0, 0, 1,    0, 0, 0},
			{1, 0, 1,    0, 0, 0,    1, 0, 0}
		}};
	}
}
