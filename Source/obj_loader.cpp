#include "obj_loader.h"
#include <iostream>
#include <string>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string.h>
using namespace glm;
namespace Aegis {
	namespace obj_loading {

		static unsigned countWords(std::string str) {
			auto copy = std::stringstream(str);
			std::string _; 
			unsigned count = 0;
			while (copy >> _) {
				count++;
			}
			return count;
		}


		OBJReader::OBJReader(const char* path)
		{
			file = std::ifstream(path);
			if (file.fail()) {
				char buf[512];
				#ifdef _WIN32
				strerror_s(buf, 512, errno);
				#elif defined(__GNUC__)
				strerror_r(errno, buf, 512);
				#endif
				std::cout << "File open failed: " << buf << '\n';
			}
		}
		Mesh OBJReader::GetMeshData()
		{
			Mesh ret;
			std::vector<vec3> positions;
			std::vector<vec3> norms;
			std::vector<vec2> uvs;
			std::vector<unsigned> indecies;

			while (true) {
				

				std::string line;
				std::getline(file, line);
				//std::cout << line << "\n";

				if (line[0] == '#') {
					if (file.eof())
						break;
					continue;
				}

				std::stringstream stream(line);
				std::string token;
				stream >> token;
				if (!token.compare("mtllib")) {
					// dont do shit cause it doesnt matter to us
				}
				else if (!token.compare("v")) {
					vec3 pos;
					stream >> pos.x >> pos.y >> pos.z;
					positions.push_back(pos);
				}
				else if (!token.compare("vt")) {
					vec2 uv;
					stream >> uv.x >> uv.y;
					uvs.push_back(uv);
				}
				else if (!token.compare("vn")) {
					vec3 norm;
					stream >> norm.x >> norm.y >> norm.z;
					norms.push_back(norm);
				}
				else if (!token.compare("f")) {
					unsigned count = countWords(stream.str())-1;
					unsigned currentIndex = ret.GetVertCount();
					if (count == 3) {
						
						for (unsigned i = 0; i < count; i++) {
							VertexData dat;

							// indexes supplied by the obj
							unsigned vert;
							unsigned uv;
							unsigned normal;

							stream >> vert;
							stream.ignore(1);
							if (stream.peek() != '/')
								stream >> uv;
							stream.ignore(1);
							if (stream.peek() != ' ' || stream.peek() != '\n')
								stream >> normal;


							if (positions.size() > 0)
								dat.SetPosition(positions[vert - 1]);
							else
								dat.SetPosition(vec3());
							if (norms.size() > 0)
								dat.SetNormal(norms[normal - 1]);
							else
								dat.SetNormal(vec3());
							if (uvs.size() > 0)
								dat.SetUV(uvs[uv - 1]);
							else
								dat.SetUV(vec2());

							ret.AddVertex(dat);

						}
						indecies.push_back(currentIndex + 0);
						indecies.push_back(currentIndex + 1);
						indecies.push_back(currentIndex + 2);
					}
					else if (count == 4) {
						
						for (unsigned i = 0; i < count; i++) {
							VertexData dat;
							
							// indexes supplied by the obj
							unsigned vert = 0;
							unsigned uv = 0;
							unsigned normal = 0;

							stream >> vert;
							stream.ignore(1);
							if(stream.peek() != '/')
								stream >> uv;
							stream.ignore(1);
							if(stream.peek() != ' ' || stream.peek() != '\n')
								stream >> normal;
							

							if (positions.size() > 0)
								dat.SetPosition(positions[vert - 1]);
							else
								dat.SetPosition(vec3());
							if (norms.size() > 0)
								dat.SetNormal(norms[normal - 1]);
							else
								dat.SetNormal(vec3());
							if (uvs.size() > 0)
								dat.SetUV(uvs[uv - 1]);
							else
								dat.SetUV(vec2());

							//std::cout << "(" << uvs[uv - 1].x << ' ' << uvs[uv - 1].y << ")\n";

							ret.AddVertex(dat);
							

						}
						indecies.push_back(currentIndex + 3);
						//std::cout << '(' << uvs[currentIndex + 3].x << ' ' << uvs[currentIndex + 3].y << ")\n";
						indecies.push_back(currentIndex + 0);
						indecies.push_back(currentIndex + 2);

						indecies.push_back(currentIndex + 0);
						indecies.push_back(currentIndex + 1);
						indecies.push_back(currentIndex + 2);					
						
					}
				}


				if (file.eof()) {
					break;
				}
								
			}

			
			/*bool sameNormal = positions.size() > norms.size();

			for (int i = 0; i < positions.size(); i++) {
				vec3 normal = sameNormal ? norms[0] : norms[i];
				
				VertexData dat(positions[i], { 0,0,0 }, normal, uvs.size() ? uvs[i] : vec2());
				ret.AddVertex(dat);
			}*/


			ret.EndMeshIndexed(indecies.data(), (unsigned int)indecies.size());
			return ret;
			
		}
		void OBJReader::GetMeshData(Mesh* mesh)
		{
			std::vector<vec3> positions;
			std::vector<vec3> norms;
			std::vector<vec2> uvs;
			std::vector<unsigned> indecies;

			while (true) {


				std::string line;
				std::getline(file, line);
				//std::cout << line << "\n";

				if (line[0] == '#') {
					if (file.eof())
						break;
					continue;
				}

				std::stringstream stream(line);
				std::string token;
				stream >> token;
				if (!token.compare("mtllib")) {
					// dont do shit cause it doesnt matter to us
				}
				else if (!token.compare("v")) {
					vec3 pos;
					stream >> pos.x >> pos.y >> pos.z;
					positions.push_back(pos);
				}
				else if (!token.compare("vt")) {
					vec2 uv;
					stream >> uv.x >> uv.y;
					uvs.push_back(uv);
				}
				else if (!token.compare("vn")) {
					vec3 norm;
					stream >> norm.x >> norm.y >> norm.z;
					norms.push_back(norm);
				}
				else if (!token.compare("f")) {
					unsigned count = countWords(stream.str()) - 1;
					unsigned currentIndex = mesh->GetVertCount();
					if (count == 3) {

						for (unsigned i = 0; i < count; i++) {
							VertexData dat;

							// indexes supplied by the obj
							unsigned vert;
							unsigned uv;
							unsigned normal;

							stream >> vert;
							stream.ignore(1);
							if (stream.peek() != '/')
								stream >> uv;
							stream.ignore(1);
							if (stream.peek() != ' ' || stream.peek() != '\n')
								stream >> normal;


							if (positions.size() > 0)
								dat.SetPosition(positions[vert - 1]);
							else
								dat.SetPosition(vec3());
							if (norms.size() > 0)
								dat.SetNormal(norms[normal - 1]);
							else
								dat.SetNormal(vec3());
							if (uvs.size() > 0)
								dat.SetUV(uvs[uv - 1]);
							else
								dat.SetUV(vec2());

							mesh->AddVertex(dat);

						}
						indecies.push_back(currentIndex + 0);
						indecies.push_back(currentIndex + 1);
						indecies.push_back(currentIndex + 2);
					}
					else if (count == 4) {

						for (unsigned i = 0; i < count; i++) {
							VertexData dat;

							// indexes supplied by the obj
							unsigned vert = 0;
							unsigned uv = 0;
							unsigned normal = 0;

							stream >> vert;
							stream.ignore(1);
							if (stream.peek() != '/')
								stream >> uv;
							stream.ignore(1);
							if (stream.peek() != ' ' || stream.peek() != '\n')
								stream >> normal;


							if (positions.size() > 0)
								dat.SetPosition(positions[vert - 1]);
							else
								dat.SetPosition(vec3());
							if (norms.size() > 0)
								dat.SetNormal(norms[normal - 1]);
							else
								dat.SetNormal(vec3());
							if (uvs.size() > 0)
								dat.SetUV(uvs[uv - 1]);
							else
								dat.SetUV(vec2());

							//std::cout << "(" << uvs[uv - 1].x << ' ' << uvs[uv - 1].y << ")\n";

							mesh->AddVertex(dat);


						}
						indecies.push_back(currentIndex + 3);
						//std::cout << '(' << uvs[currentIndex + 3].x << ' ' << uvs[currentIndex + 3].y << ")\n";
						indecies.push_back(currentIndex + 0);
						indecies.push_back(currentIndex + 2);

						indecies.push_back(currentIndex + 0);
						indecies.push_back(currentIndex + 1);
						indecies.push_back(currentIndex + 2);

					}
				}


				if (file.eof()) {
					break;
				}

			}


			/*bool sameNormal = positions.size() > norms.size();

			for (int i = 0; i < positions.size(); i++) {
				vec3 normal = sameNormal ? norms[0] : norms[i];

				VertexData dat(positions[i], { 0,0,0 }, normal, uvs.size() ? uvs[i] : vec2());
				mesh->AddVertex(dat);
			}*/


			mesh->EndMeshIndexed(indecies.data(), (unsigned)indecies.size());
			
		}
		OBJReader::~OBJReader()
		{
			file.close();
		}
	}
}