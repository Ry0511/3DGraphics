#include "ObjFile.h"

namespace Util {

	//////////////////////////////////////////////////
	// Constructors
	//////////////////////////////////////////////////

	ObjFile::ObjFile(const std::string& file) : m_Filename(file) {
		std::fstream f(file);

		if (!f.is_open()) throw "File not found!";

		while (!f.eof()) {
			std::string line;
			std::getline(f, line);

			// Vertex
			if (line.length() > 0) {

				std::stringstream buf;
				buf << line.substr(1);

				if (line[0] == 'v') {
					double xs[3]{};
					buf >> xs[0] >> xs[1] >> xs[2];
					m_Vertices.emplace_back(xs[0], xs[1], xs[2]);

					// Face
				} else if (line[0] == 'f') {
					int xs[3]{};
					buf >> xs[0] >> xs[1] >> xs[2];
					m_Indices.emplace_back(xs[0],xs[1],xs[2]);
				}
			}
		}
	}

	//////////////////////////////////////////////////
	// Getters
	//////////////////////////////////////////////////

	const std::string& ObjFile::getFilename() const {
		return m_Filename;
	}

	const std::vector<GMath::Vec3d>& ObjFile::getVertices() const {
		return m_Vertices;
	}

	const std::vector<Vec3i>& ObjFile::getIndices() const {
		return m_Indices;
	}

	std::vector<GMath::Triangle> ObjFile::getTriangleMesh() const {
		std::vector<Triangle> buffer{};
		buffer.reserve(m_Indices.size());
		for (const Vec3i& i : m_Indices) {
			buffer.push_back({
				m_Vertices.at(--i.x),
				m_Vertices.at(--i.y),
				m_Vertices.at(--i.z)
			});
		}

		return buffer;
	}

}