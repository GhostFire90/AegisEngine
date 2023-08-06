#pragma once


#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#endif // _MSC_VER


#ifdef AEGIS_DLL_BUILD
#define AEGIS_API EXPORT
#else
#define AEGIS_API IMPORT
#endif // !AEGIS_DLL_BUILD



namespace Aegis {
	namespace obj_loading {
		class OBJReader;
	}
	/// <summary>
	/// Vertex data works as a struct that stores the
	/// Position, normal, color, and uv of the vertex
	/// essentially its a 14 float array in memory
	/// </summary>
	class VertexData {
	public:
		/// <summary>
		/// Constructor for vertex data
		/// </summary>
		/// <param name="pos">position of the vertex in 3d, required</param>
		/// <param name="color">vertex color, default is black</param>
		/// <param name="normal">Perpendicular vector to the vertex's face, default is 0,0,0</param>
		/// <param name="uv">the texture coordinate ofthe vertex, defualt 0,0</param>
		VertexData(glm::vec3 pos, glm::vec3 color = {0,0,0}, glm::vec3 normal = {0,0,0}, glm::vec2 uv = {0,0});

		/// <summary>
		/// Default constructor, initializes all members to 0
		/// </summary>
		VertexData();

		/// <returns>The position of the vertex</returns>
		glm::vec3 GetPosition();
		/// <returns>The vertex color, rgb</returns>
		glm::vec3 GetColor();
		/// <returns>The normal vector of the vertex</returns>
		glm::vec3 GetNormal();
		/// <returns>The texture coordinate of the vertex</returns>
		glm::vec2 GetUV();

		/// <summary>
		/// Setter for the position of the vertex
		/// </summary>
		/// <param name="pos">The position to place the vertex at</param>
		void SetPosition(glm::vec3 pos);
		/// <summary>
		/// Setter for the vertex color
		/// </summary>
		/// <param name="col">The color to set to the vertex</param>
		void SetColor(glm::vec3 col);
		/// <summary>
		/// Setter for the normal vector
		/// </summary>
		/// <param name="normal">vector perpendicular to the vertex's face</param>
		void SetNormal(glm::vec3 normal);
		/// <summary>
		/// Setter for the UV/Texture Coordinate of the vertex
		/// </summary>
		/// <param name="UV">The texture coordinate of the vertex</param>
		void SetUV(glm::vec2 UV);

	private:
		glm::vec3 position, color, normal;
		glm::vec2 uv;
	};

	class AEGIS_API Mesh {
	public:
		Mesh();
		Mesh(const char* path);
		~Mesh();

		
		void AddVertex(glm::vec3 pos, glm::vec3 color, glm::vec3 normal, glm::vec2 uv);
		
		void Render();
		void Render(unsigned int renderType);
		void EndMesh();
		void EndMeshIndexed(const unsigned int* indecies, unsigned count);
		
		unsigned int GetVertCount();

		static Mesh ReadFromFile(const char* path);
		static void ReadFromFile(Mesh* mesh, const char* path);
		friend class obj_loading::OBJReader;
	private:

		const VertexData* GetData();
		
		void AddVertex(VertexData vert);

		std::vector<VertexData>* verts;
		std::vector<unsigned int>* indecies;
		bool finished, indexed;
		unsigned int VBO, VAO, EBO, indexCount;
		
	};
}
