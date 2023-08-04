#include <glad/glad.h>
#include <iostream>
#include "ShaderSource.h"
#include <fstream>
#include <sstream>

static bool checkShaderCompile(int shaderID) {
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "Shader compilation error : \n" << infoLog << std::endl;
	}
	return success;
}

static void filetostring(const char* path, std::string* ret) {
	std::ifstream file;
	file.open(path, std::ios::in);

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string full = buffer.str();

	*ret = full;
	return;

}


namespace Aegis {
	ShaderSource::ShaderSource(const char* vertPath, const char* fragPath)
	{
		std::string readvert = "";
		std::string readfrag = "";

		filetostring(vertPath, &readvert);
		filetostring(fragPath, &readfrag);

		const char* vertdat = readvert.c_str();
		
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertdat, NULL);
		glCompileShader(vertShader);

		if (!checkShaderCompile(vertShader)) {
			glDeleteShader(vertShader);

			vertShader = -1;
			fragShader = -1;

			return;
		}

		const char* fragdat = readfrag.c_str();

		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragdat, NULL);
		glCompileShader(fragShader);
		
		if (!checkShaderCompile(fragShader)) {
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			vertShader = -1;
			fragShader = -1;

			return;
		}


	}
	ShaderSource::~ShaderSource()
	{
		if (vertShader != -1) {
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);
		}
	}
}