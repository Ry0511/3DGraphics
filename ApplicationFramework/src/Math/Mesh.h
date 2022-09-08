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

		static Mesh newSphereMesh(const size_t sectorCount, const size_t stackCount, const double radius) {
			std::vector<Vec3d> vertices;
			vertices.reserve(stackCount * sectorCount);

			// Generate the Vertices of the Sphere
			const double sectorStep = 2 * GMath::PI / sectorCount;
			const double stackStep = GMath::PI / stackCount;
			double stackAngle = 0, sectorAngle = 0;

			for (size_t i = 0; i <= stackCount; ++i) {

				stackAngle = GMath::PI / 2 - i * stackStep;
				const double xy = radius * cos(stackAngle);
				const double z = radius * sin(stackAngle);

				for (size_t j = 0; j <= sectorCount; ++j) {
					sectorAngle = j * sectorStep;

					const double x = xy * cos(sectorAngle);
					const double y = xy * sin(sectorAngle);
					vertices.emplace_back(x, y, z);
				}
			}

			// Generate the Indices of the vertices
			std::vector<GMath::Triangle> tris;
			tris.reserve((stackCount * sectorCount) / 3);

			for (size_t i = 0; i < stackCount; ++i) {
				size_t k1 = i * (sectorCount + 1);
				size_t k2 = k1 + sectorCount + 1;

				for (size_t j = 0; j < sectorCount; ++j, ++k1, ++k2) {

					if (i != 0) {
						tris.emplace_back(GMath::Triangle{vertices[k1], vertices[k2], vertices[k1 + 1]});
					}

					if (i != (stackCount - 1)) {
						tris.emplace_back(GMath::Triangle{vertices[k1 + 1], vertices[k2], vertices[k2 + 1]});
					}
				}
			}

			return Mesh{tris};
		}
	}
}
