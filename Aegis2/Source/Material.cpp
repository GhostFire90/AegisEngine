#include <glad/glad.h>
#include <glfw3.h>
#include "Material.h"
#include "ShaderSource.h"
#include "Shader.h"
#include <iostream>
#include "Texture.h"

namespace Aegis {
	Material::Material(const char* _name, const ShaderSource& shader) : source(shader), name(_name), shader(nullptr), uniforms(nullptr), textures(), uniformCount(0), uniformTypes(nullptr)
	{
	}
	Material::Material(const Material& other) : source(other.source), name(other.name), textures()
	{
		shader = new Shader(source);
		uniformTypes = new std::map<std::string*, unsigned int>();
		
		for (int i = 0; i < 16; i++) {
			textures[i] = other.textures[i];
		}


		GLint _uniformCount;

		const GLsizei bufsize = 512; // name buffer size
		GLchar uname[bufsize];		 // uniform name will be stored here
		GLsizei length;				 // actual length of the name will be stored here

		GLint size;					 // size of the datatype
		GLenum type;					 // data type

		glGetProgramiv(shader->program, GL_ACTIVE_UNIFORMS, &_uniformCount);

		uniforms = new std::string*[_uniformCount];

		uniformCount = _uniformCount;

		for (int i = 0; i < _uniformCount; i++) {
			glGetActiveUniform(shader->program, i, bufsize, &length, &size, &type, uname);
			uniforms[i] = new std::string(uname);
			uniformTypes->insert(std::make_pair(uniforms[i], type));
			//std::cout << i << ": " << uniforms[i] << " " << type << '\n';
			
		}

	}

	Material::~Material()
	{
		if (shader != nullptr) {
			delete shader;
			for (unsigned i = 0; i < uniformCount; i++) {
				delete uniforms[i];
			}
			delete[] uniforms;
			delete uniformTypes;
		}
	}

	Material* Material::Instantiate() const
	{
		return new Material(*this);
	}
	Shader* Material::GetShader()
	{
		return shader;
	}
	void Material::SetTexture(const Texture* tex, unsigned int id)
	{
		textures[id] = tex;
	}
	void Material::Use()
	{
		shader->Use();
		for (int i = 0; i < 16; i++) {
			if (textures[i]) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textures[i]->id);
			}
		}		
	}
}