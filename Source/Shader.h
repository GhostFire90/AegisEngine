#pragma once
#include <glm/glm.hpp>

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
	class ShaderSource;
	class AEGIS_API Shader {
	public:
		//Shader(const char* vertexShader, const char* fragShader);
		Shader(const ShaderSource& source);
		//Shader(const Shader& source);
		~Shader();
		void Use();

		void SetBool(const char* name, bool val);
		void SetInt(const char* name, int val);
		void SetFloat(const char* name, int val);

		void SetMat4(const char* name, glm::mat4 val);

		void SetVec2(const char* name, glm::vec2 val);
		void SetVec3(const char* name, glm::vec3 val);
		void SetVec4(const char* name, glm::vec4 val);

		friend class Material;
	private:
		int program;		
	};
}