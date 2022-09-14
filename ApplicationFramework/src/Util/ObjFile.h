#pragma once

#include "../Math/Vec3.h"
#include "../Math/Triangle.h"
#include "../Math/Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace Util {

	using namespace GMath;

	class ObjFile {

	private:
		const std::string m_Filename;
		std::vector<Vec3d> m_Vertices{};
		std::vector<Vec3i> m_Indices{};

	public:
		ObjFile(const std::string& file);
		ObjFile(const ObjFile& x) = delete;

	public:
		const std::string& getFilename() const;
		const std::vector<Vec3d>& getVertices() const;
		const std::vector<Vec3i>& getIndices() const;

		std::vector<Triangle> getTriangleMesh() const;
	};
}

