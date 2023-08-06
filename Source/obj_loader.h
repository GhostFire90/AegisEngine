#pragma once

#include <fstream>
#include "Mesh.h"
#include <vector>

namespace Aegis {
	namespace obj_loading{
		class OBJReader {
		public:
			OBJReader(const char* path);
			Mesh GetMeshData();
			void GetMeshData(Mesh* mesh);
			~OBJReader();
		private:
			std::ifstream file;

		};
	}
}