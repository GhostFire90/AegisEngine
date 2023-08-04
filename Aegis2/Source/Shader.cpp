#include <glad/glad.h>
#include "Shader.h"
#include <iostream>
#include "ShaderSource.h"
#include <glm/gtc/type_ptr.hpp>



static bool checkShaderLink(int programID) {
	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "Shader program link failure:\n " << infoLog << std::endl;
	}
	return success;
}


namespace Aegis {
	/*Shader::Shader(const char* _vertexShader, const char* _fragShader) : fragShader(-1), vertexShader(-1), program(0)
	{
		std::string readvert = "";
		std::string readfrag = "";

		paths[0] = _vertexShader;
		paths[1] = _fragShader;
		 
		

		const char* vert_dat = readvert.c_str();
		const char* frag_dat = readfrag.c_str();

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vert_dat, NULL);
		glCompileShader(vertexShader);

		if (!checkShaderCompile(vertexShader)) {
			glDeleteShader(vertexShader);

			vertexShader = -1;
			fragShader = -1;

			return;
		}

		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &frag_dat, NULL);
		glCompileShader(fragShader);

		if (!checkShaderCompile(fragShader)) {
			glDeleteShader(vertexShader);
			glDeleteShader(fragShader);

			vertexShader = -1;
			fragShader = -1;

			return;
		}

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);
		if (!checkShaderLink(program)) {
			glDeleteProgram(program);
			program = -1;

		}


		glDeleteShader(vertexShader);
		glDeleteShader(fragShader); 
	}
	Shader::Shader(const Shader& source)
	{
		std::string readvert = "";
		std::string readfrag = "";

		paths[0] = source.paths[0];
		paths[1] = source.paths[1];

		filetostring(paths[0], &readvert);
		filetostring(paths[1], &readfrag);

		const char* vert_dat = readvert.c_str();
		const char* frag_dat = readfrag.c_str();

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vert_dat, NULL);
		glCompileShader(vertexShader);

		if (!checkShaderCompile(vertexShader)) {
			glDeleteShader(vertexShader);

			vertexShader = -1;
			fragShader = -1;

			return;
		}

		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &frag_dat, NULL);
		glCompileShader(fragShader);

		if (!checkShaderCompile(fragShader)) {
			glDeleteShader(vertexShader);
			glDeleteShader(fragShader);

			vertexShader = -1;
			fragShader = -1;

			return;
		}

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);
		if (!checkShaderLink(program)) {
			glDeleteProgram(program);
			program = -1;

		}


		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
	}*/
	Shader::Shader(const ShaderSource& source)
	{
		program = glCreateProgram();
		glAttachShader(program, source.vertShader);
		glAttachShader(program, source.fragShader);
		glLinkProgram(program);
		if (!checkShaderLink(program)) {
			glDeleteProgram(program);
			program = -1;
		}
	}
	Shader::~Shader()
	{
		glDeleteProgram(program);
	}
	void Shader::Use()
	{
		glUseProgram(program);
	}

	void Shader::SetBool(const char* name, bool val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniform1i(uniform, val);
	}

	void Shader::SetInt(const char* name, int val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniform1i(uniform, val);
	}

	void Shader::SetFloat(const char* name, int val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniform1f(uniform, (GLfloat)val);
	}

	void Shader::SetMat4(const char* name, glm::mat4 val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniformMatrix4fv(uniform, 1, false, glm::value_ptr(val));
	}

	void Shader::SetVec2(const char* name, glm::vec2 val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniform2fv(uniform, 1, glm::value_ptr(val));
	}

	void Shader::SetVec3(const char* name, glm::vec3 val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniform3fv(uniform, 1, glm::value_ptr(val));
	}

	void Shader::SetVec4(const char* name, glm::vec4 val)
	{
		int uniform = glGetUniformLocation(program, name);
		glUniform4fv(uniform, 1, glm::value_ptr(val));
	}
	
}