#include <glad/glad.h>
#include "Mesh.h"
#include "obj_loader.h"


namespace Aegis {
	VertexData::VertexData(glm::vec3 pos, glm::vec3 _color, glm::vec3 _normal, glm::vec2 _uv) : 
		position(pos), color(_color), normal(_normal), uv(_uv)
	{
	}
	VertexData::VertexData() :
		position(0), color(0), normal(0), uv(0)
	{
	}
	glm::vec3 VertexData::GetPosition()
	{
		return this->position;
	}
	glm::vec3 VertexData::GetColor()
	{
		return this->color;
	}
	glm::vec3 VertexData::GetNormal()
	{
		return this->normal;
	}
	glm::vec2 VertexData::GetUV()
	{
		return this->uv;
	}

	void VertexData::SetPosition(glm::vec3 pos)
	{
		position = pos;
	}

	void VertexData::SetColor(glm::vec3 col)
	{
		color = col;
	}

	void VertexData::SetNormal(glm::vec3 normal)
	{
		this->normal = normal;
	}

	void VertexData::SetUV(glm::vec2 UV)
	{
		this->uv = UV;
	}


	Mesh::Mesh() : finished(false), indexed(false), EBO(0), indexCount(0)
	{
		indecies = new std::vector<unsigned int>();
		verts = new std::vector<VertexData>();
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
	}
	Mesh::Mesh(const char* path) : finished(false), indexed(false), EBO(0), indexCount(0)
	{
		indecies = new std::vector<unsigned int>();
		verts = new std::vector<VertexData>();
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
	    Mesh::ReadFromFile(this, path);		
	}
	Mesh::~Mesh()
	{
		delete indecies;
		delete verts;
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &VAO);
	}
	void Mesh::AddVertex(VertexData vert)
	{
		if(!finished)
			verts->push_back(vert);
	}
	void Mesh::AddVertex(glm::vec3 pos, glm::vec3 color, glm::vec3 normal, glm::vec2 uv)
	{
		return AddVertex(VertexData(pos, color, normal, uv));
	}
	void Mesh::Render()
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		if (!indexed) {
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verts->size());
		}
		else {
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		}
		
	}
	void Mesh::Render(unsigned int renderType)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		if (!indexed) {
			glDrawArrays(renderType, 0, (GLsizei)verts->size());
		}
		else {
			glDrawElements(renderType, indexCount, GL_UNSIGNED_INT, indecies->data());
		}
	}
	void Mesh::EndMesh()
	{
		auto arr = verts->data();
		int totalBytes = sizeof(VertexData) * (int)verts->size();
		
		glBindVertexArray(VAO);
		

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, totalBytes, arr, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)24);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)36);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		finished = true;
	}
	void Mesh::EndMeshIndexed(const unsigned int* indecies, unsigned count)
	{
		EndMesh();
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indecies, GL_STATIC_DRAW);
		for (unsigned i = 0; i < count; i++) {
			this->indecies->push_back(indecies[i]);
		}
		indexed = true;
		indexCount = count;

	}
	const VertexData* Mesh::GetData()
	{
		return verts->data();
	}
	unsigned int Mesh::GetVertCount()
	{
		return (unsigned int)verts->size();
	}
	Mesh Mesh::ReadFromFile(const char* path)
	{
		obj_loading::OBJReader reader(path);
		return reader.GetMeshData();
	}
	void Mesh::ReadFromFile(Mesh* mesh, const char* path)
	{
		obj_loading::OBJReader reader(path);
		reader.GetMeshData(mesh);
	}
}